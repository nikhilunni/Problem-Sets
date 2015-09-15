/** @file server.c */

//#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <queue.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "queue.h"
#include "libs/libhttp.h"
#include "libjsonparse.h"
#include "datastore_control.h"


#define MAX_SIZE 4096

/* Allows up to 10 MB requests */
#define MAX_RES_LEN (10 * 1024 * 1024)

const char *HTTP_200_STRING = "OK";
const char *HTTP_404_STRING = "Not Found";
const char *HTTP_501_STRING = "Not Implemented";
struct addrinfo *result;
int sock_fd;
pthread_mutex_t mutex;
queue_t pthread_queue;
queue_t fd_queue;
void * conn_handler(void * arr);
char * strdupe(const char * s);
void handler(int sig);
void thread_join(void * thread, void * irrel);
void fd_close(void * fd, void * irrel);
/**
 * Processes the request line of the HTTP header.
 * 
 * @param request The request line of the HTTP header.  This should be
 *                the first line of an HTTP request header and must
 *                NOT include the HTTP line terminator ("\r\n").
 *
 * @return The filename of the requested document or NULL if the
 *         request is not supported by the server.  If a filename
 *         is returned, the string must be free'd by a call to free().
 */
char* process_http_header_request(const char *request)
{
	// Ensure our request type is correct...
	if (strncmp(request, "POST ", 5) != 0)
		return NULL;

	// Ensure the function was called properly...
	assert( strstr(request, "\r") == NULL );
	assert( strstr(request, "\n") == NULL );

	// Find the length, minus "GET "(4) and " HTTP/1.1"(9)...
	int len = strlen(request) - 5 - 9;

	// Copy the filename portion to our new string...
	char *filename = malloc(len + 1);
	strncpy(filename, request + 5, len);
	filename[len] = '\0';

	if (strstr(filename, ".."))
	{
		free(filename);
		return NULL;
	}

	return filename;
}


int main(int argc, char **argv)
{
    if (argc < 2)
    {
	fprintf(stderr, "Usage: ./server PORT\n");
	exit(0);
    }
    int port = atoi(argv[1]);
    if (port <= 0 || port >= 65536)
    {
	fprintf(stderr, "Illegal port number.\n");
	return 1;
    }
	
    int s;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct addrinfo hints;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    s = getaddrinfo(NULL, argv[1], &hints, &result);
    if (s)
    {
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
	exit(1);
    }
    
    if (bind(sock_fd, result->ai_addr, result->ai_addrlen))
    {
	perror("bind failure");
	exit(1);
    }

    if (listen(sock_fd, 10))
    {
	perror("listen failure");
	exit(1);
    }

    signal(SIGINT, handler);
    pthread_mutex_init(&mutex,NULL);
    queue_init(&pthread_queue);
    queue_init(&fd_queue);
    load();
    printf("listening on port %s\n",argv[1]);fflush(stdout);
    
    
    while (1)
    {
	
	int client_fd = accept(sock_fd, NULL, NULL);
	if (client_fd == -1)
	{
	    perror("accept failure");
	}
	else
	{
	    pthread_mutex_lock(&mutex);
	    
	    pthread_t conn;
	    int * pass_fd = malloc(sizeof(int));
	    *pass_fd = client_fd;
	    pthread_create(&conn,NULL,conn_handler,(void *)pass_fd); 
	    queue_enqueue(&pthread_queue, (void *)conn);
	    queue_enqueue(&fd_queue, (void *)( (unsigned long) client_fd));
	    
	}
	pthread_mutex_unlock(&mutex);
	
    }
    return 0;
}

void * conn_handler(void * arr)
{
    int client_fd = *((int*)arr);
    int keep_alive = 1;
    while (keep_alive)
    {


	http_t req;
	if (http_read(&req,client_fd) == -1)
	{
	    http_free(&req);
	    break;
	}
	const char * rh = http_get_status(&req);
	char * uri = process_http_header_request(rh);
	const char * conn_type = http_get_header(&req, "Connection");
	if (conn_type)
	{
	    if (strcasecmp("keep-alive",conn_type))
		keep_alive = 0;
	    //free(conn_type);
	}
	else
	{
	    keep_alive = 0;
	}
	char * output = NULL;
	if (uri)
	{
	    size_t size;
	    const char * body = http_get_body(&req,&size);
            jsonreq_t request;
            request.key = NULL;
            request.value = NULL;
            parsereq(body,&request);

            jsonres_t response = process_request(uri,request);

	    
            generateres(&output,&response,uri);
            if (request.key) free(request.key);
            if (request.value) free(request.value);
            //if (request) free(request);
	    free(uri);
	}
	char * ret_str = "";
        asprintf(&ret_str,"HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: %zu\r\n\r\n",strlen(output));
	send(client_fd,ret_str,strlen(ret_str),0);
	send(client_fd,output,strlen(output),0);
	if (output) free(output);
        if (ret_str) free(ret_str);
	http_free(&req);
    }
    free(arr);
    close(client_fd);
    return NULL;
}

char * strdupe(const char * s)
{
  size_t length = strlen(s) + 1;
  char *ret = malloc(length);
  return memcpy(ret, s, length);
}
void handler(int sig)
{
    sig++;
    pthread_mutex_lock(&mutex);
    queue_iterate(&fd_queue, fd_close, NULL);
    shutdown(sock_fd,2);
    close(sock_fd);
    queue_iterate(&pthread_queue, thread_join, NULL);
    queue_destroy(&pthread_queue);
    queue_destroy(&fd_queue);
    pthread_mutex_unlock(&mutex);
    
    
    pthread_mutex_destroy(&mutex);
    free(result);
    save();
    exit(0);
}


void thread_join(void * thread, void * irrel)
{
    irrel++;
    pthread_join((pthread_t)thread, NULL);
}

void fd_close(void * fd, void * irrel)
{
    irrel++;
    shutdown((int)((unsigned long)fd),2);
    close((int)((unsigned long)fd));
}
