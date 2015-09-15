/* The 'real' hello world program that is ready to say hello to the world; a simple webserver.
This server uses blocking I/O and is single-process and single threaded;
If client connection hangs or is very slow then all waiting connections will wait.
*/
#include <sys/socket.h>   
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <dirent.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// where is the content?
#define FILEBASE "webcontent" 
// Example use:
// ./webserver 8080
// Then open, http://localhost:8080/hello.html
// If the port number is missing, an unused port number is used.

int serve(FILE* f);
int create_server_socket(const char* port); 
const char* to_mimetype(const char*path);
int serve_dir(FILE*f, const char*path);
int serve_file(FILE*f, const char*path, size_t size);

int write_error(FILE*f, int status, char* mesg) {
    printf("%d %s\n", status, mesg);
    return fprintf(f,"HTTP/1.1 %d %s\r\nConnection: close\r\n\r\n%s\r\n", status, mesg,mesg);
}

int main(int argc, char**argv) {

    int sock_fd = create_server_socket(argc > 1? argv[1] : "0");

    printf("Accepting Clients...\n");
    while(1) {
        int client_fd = ?
        if(client_fd ==-1)
            break;                                     
            
        // wrap the client file descriptor into a FILE     
        FILE* f = fdopen(client_fd,"a+");

        serve(f);
        fclose(f);
    }              
    
    close(sock_fd);
    return 0;
}


int serve(FILE *f) {
    char line[4096];
    char*ok = fgets(line,sizeof(line)-1, f);
    if(! ok) return write_error(f,400,"Bad Request"); 
    
    char method[16]="", url[2048]="",protocol[16]="";
    // Parse the line buffer. Hint not fscanf
    int parsed = sscanf (line, "%15s %2047s %15s\r\n", method, url, protocol);
    printf("Parsed %d %s %s %s\n", parsed, method,url,protocol);

    // Check 3 arguments were parsed
    if(parsed!=3 ) return write_error(f,400,"Bad Request");

    int protocol_notsup = strcmp("HTTP/1.0", protocol) &&  strcmp("HTTP/1.1", protocol) ;
    if(protocol_notsup) return write_error(f,505,"HTTP Version not supported");

    int is_get_method = 0 == strcmp("GET", method);
    if(!is_get_method)  return write_error(f,501,"Not Implemented" );

    char path[strlen(FILEBASE) + strlen(url) + 2];   // "/" and \0 termination
    sprintf(path,"%s/%s", FILEBASE, url);
    // Todo real path check

    printf("stat-ing file %s\n", path);
    struct stat s;
    if( 0 != ? ) {
        printf("stat failed:%s\n",strerror(errno));
        return write_error(f, 404, "Not Found - could not stat()");
    }
    //is it a directory?
    if(? ) return serve_dir(f, path);
    
    // assume it is regular file    
    return serve_file(f, path, s.st_size);
}




int ends_with(const char*path, const char*ext) { 
  if(!path || !ext) return 0;
    int pathlen = strlen(path);
    int extlen= strlen(ext);
    return pathlen > extlen && 0== strcmp(path+ (pathlen-extlen), ext);
}


int create_server_socket(const char* port) {

  struct addrinfo hints, *result;
  memset(&hints, 0, sizeof(?));
  hints.ai_family = AF_INET;
  hints.ai_socktype = ?; // Want TCP stream
  hints.ai_flags = ?;  // server socket


  int s = getaddrinfo(NULL, port, &hints, &result);
  if (s != 0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
      exit(1);
  }        
  // family, socket type, protocol
  int sock_fd = socket(result->ai_family, result->ai_socktype,result->ai_protocol);
  
  int optval = 1;   // reuse port 
  ?(sock_fd, SOL_SOCKET, ?, &optval, sizeof(optval));

  if (bind(sock_fd, ?, ? ) != 0) {
      perror("bind()");
      exit(1);
  }

  if (listen(sock_fd, 10) != 0) {
      perror("listen()");
      exit(1);
  }

  int portnum = -1;
  struct sockaddr_in *result_addr = (struct sockaddr_in *) result->ai_addr; 
  struct sockaddr_in sin;
  socklen_t len = sizeof(sin);
  if (getsockname(sock_fd, (struct sockaddr *)&sin, &len) != -1)
    portnum =  ?(sin.sin_port); // endian conventions: convert network to host short 
    
  printf("Listening on file descriptor %d, port %d\n", sock_fd,portnum);
  printf("Examples:\nhttp://localhost:%d/hello.html\nand when you have directory listing working,\nhttp://localhost:%d\n",portnum,portnum);  
  return sock_fd;
}


const char* to_mimetype(const char*path) {
    if(ends_with(path,".jpg")) return "image/jpeg";
    if(ends_with(path,".png")) return "image/png";
    if(ends_with(path,".gif")) return ?;

    if(ends_with(path,".html")) return ?;
    if(ends_with(path,".txt") || ends_with(path,".c") ) return "text/plain";
    return "application/octet-stream"; // Default = just some binary data
}

int serve_dir(FILE*f, const char*path) {
    DIR *dir;
    struct dirent *dp;
    fprintf(f,"HTTP/1.1 200 OK\r\nConnection: closer\nContent-Type: %s\r\n\r\n","text/html"); 
    

    fprintf(f,"<html><body>");
    
    fprintf(f,"<li>Todo:opendir/readdir/closedir etc list files in path here\n");
    
    fprintf(f,"</body></html>");
        
    return 0; 
}

int serve_file(FILE*f, const char*path, size_t size) {

  // serve the file :
  printf("Opening %s\n", path);
  // Open a new file descriptor for reading the file at 'path' O_RDONLY
  
  int file_fd = ?;
  if(file_fd == -1) {
      printf("Failed to open file:%s\n", strerror(errno));
      return write_error(f, 404, "Not Found - could not open())");  
  }
  // mmap the file into memory
  void*ptr = mmap ?

  if(ptr!= (void*)-1) {
      // Serve the file 
      // Convert path file-extension ".html" ".png" etc into mimetype
      const char*mimetype= to_mimetype(path);
      
      fprintf(f,"HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: %lu\r\nContent-Type: %s\r\n\r\n",?;
      fwrite

      munmap
  } else {
      printf("mmap failed:%s",strerror(errno));
      write_error(f, 404, "Not Found - could not mmap())");
  }

  close(file_fd);
  return 0;  
}

