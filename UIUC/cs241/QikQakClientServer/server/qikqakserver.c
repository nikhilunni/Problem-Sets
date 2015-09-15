/* A simple multi-threaded TCP "Chat" Server by L. Angrave 2015*/
/* This simplistic code is for teaching purposes and is a long way from what might be considered
   a robust, scalable server.  */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
// gcc qikqakserver.c -std=gnu99 -pthread -o qikqak -w

#define HISTORY (5)
#define MESG_SIZE (100)

// Note the UIUC Firewall & routers may choose to drop packets to specific ports e.g. port 241
// Some testing found that packets to port 123 were allowed and also port 123 is currently
// unused by any service on the VM

#define PORT "123"

char chat_log[HISTORY][MESG_SIZE];
int chat_head;

// We will start a thread for each client
// We use the C99 type 'intptr_t:integer type capable of holding a pointer"
// to avoid the warning about casting the small integer to a void* representation

void* process_client(void* arg) {
    int client_fd = (intptr_t) arg;
    pthread_detach(pthread_self()); // no join() required

    while(1) {

        char buffer[MESG_SIZE];
        int len = read(client_fd, buffer, MESG_SIZE-1);
        if(len <1) break;  // Error or client closed the connection, so time to close this specific client connection

// Basic pattern of many servers: First we process the input request  (in this demo we just store the bytes)


        // Discard newlines and other ASCII control characters
        int j=0;
        for(int i=0; i<len; i++)
            if(buffer[i] >= 32 ) buffer[j++] = buffer[i];
            
        if(j >0) {
          buffer[j] = '\0'; // Turn the data into a nul byte terminated C string    
        
          chat_head = (chat_head + 1) % HISTORY;
          strcpy( chat_log[chat_head], buffer);

          printf("Read %d chars:%s\n", len, chat_log[chat_head]);
          } else puts("Ignoring empty request");

// ... Then we construct a response (in this demo, we concatenate the recent requests together into 'output')
  

        // Build a single large output buffer and attempt to send it as one big packet
        // Allow space for additional characters in formatted string below
        char output[ HISTORY * (MESG_SIZE+10)];

        *output = '\0';
        for(int i=0; i< HISTORY; i++) {
            int j = (chat_head -i + HISTORY) % HISTORY;
            int len = strlen(chat_log[j]);
            if(! len) continue; //skip blank entries

            int total = strlen( output );
            sprintf(output + total,"\"%s\" ", chat_log[j]);
        }

// Now send those bytes back to the client
        write(client_fd, output, strlen(output));
    }
    close(client_fd);
    return NULL;
}

int main(int argc, char** argv)
{
    int rc, sock_fd;

    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    rc = getaddrinfo(NULL, PORT, &hints, &result);
    if (rc != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rc));
        exit(1);
    }  
    
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1) {
      perror("socket");
      exit(1);
    }         
    
    int optval = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    if ( bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0 ) {
        perror("bind()");
        exit(1);
    }

    if ( listen(sock_fd, 10) != 0 ) {
        perror("listen()");
        exit(1);
    }

    struct sockaddr_in * result_addr = (struct sockaddr_in*) result->ai_addr;
    printf("Listening on file descriptor %d, port %d\n", sock_fd, ntohs(result_addr->sin_port));

    while(1) {
        puts("Waiting for connection...\n");

        int client_fd = accept(sock_fd, NULL, NULL);

        if(client_fd == -1) {
            perror("accept");
            sleep(1);
            continue; // Wait for next client to connect
        }
        printf("Connection made: client_fd=%d\n", client_fd);

        pthread_t tid;
        int ok = pthread_create(&tid,NULL, process_client, (void*) (intptr_t) client_fd);
        if(ok != 0) {
           puts("Could not create thread - time to quit");
        };
    }
    puts("Exiting");
    close(sock_fd);
    return 0;
}
