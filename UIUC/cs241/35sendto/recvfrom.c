#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
// gcc -std=gnu99 recvfrom.c -o recvfrom

void quit(char* mesg) {
    perror(mesg);
    exit(1);
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: %s port\n", argv[0]);
        exit(1);
    }

    struct addrinfo hints, *result= 0;
    memset(&hints,0,sizeof(hints));
    // IP4 or 6 (AF_INET / AF_INET6) 
    // SOCK_DGRAM for UDP
    // What do you need for a server socket?
    hints.ai_family=;
    hints.ai_socktype=;
    hints.ai_flags=AI_?;

    char* hostname = NULL;
    char *portname = argv[1];

    int err=getaddrinfo(hostname,portname,&hints,&result);
    if(err) quit("getaddrinfo");
                  
    // Pull the family, socket type and protocol from the result  struct
    //
    int fd=socket( result->ai_family, 
    if (fd==-1) quit("socket");

    if (bind(fd,result->ai_addr,result->ai_addrlen)==-1)
        quit("bind");

    freeaddrinfo(result);

    char buffer[1024];
    

    /// What is the best type of sockaddr struct to use here?
    struct sockaddr_? source;
    socklen_t  source_len = sizeof(source);

    while(1) {
        printf("Listening on port %s\n", portname);

// TODO Will need to cast source pointer to (struct sockaddr*) 
        ssize_t bytes_recd=
        
        
        if (bytes_recd==-1) quit("recvfrom");
        if(bytes_recd == source_len)
            printf("Datagram > buffer - message truncated\n");

        // write the buffer contents to file descriptor 1:

 


        write(1, "\n",1);

        // Encrypt the message
        for(int i=0; i < bytes_recd; i++) {
            if( buffer[i] >= 64) buffer[i] ^= 1;
        }

        int flags = 0;
        // Send a datagram back to the client
        // Hint don't use 'result'
        size_t bytes_sent = 
        if(bytes_sent==-1) {
            quit("sendto");
        }

        if(bytes_sent == bytes_recd ) printf("Replied\n");
        else  quit("write");
    }
    close(fd);
    puts("\nFinished");
    return 0;
}


