#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <android/log.h>
#include <sys/types.h>

#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,"Webcam",__VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"Webcam",__VA_ARGS__)

static int sock_fd;
static JavaVM *jvm;       /* denotes a Java VM */
static  JNIEnv *env;       /* pointer to native method interface */
static jobject myactivity;

int write_binary(FILE*f, char*mimetype, size_t len, void* data) {
    fprintf(f,"HTTP/1.1 200 OK\r\nConnection: close\r\n\Content-Length: %d\r\nContent-Type: %s\r\n\r\n", len,mimetype);
    // Hint man fwrite (the FILE equivalent of write)
    ?
    return 1;
}
int write_text(FILE*f, char* mimetype, char*content) {
    LOGD("Writing %s %s",mimetype, content);
    int len = strlen(content);
    return fprintf(f,"HTTP/1.1 200 OK\r\nConnection: close\r\n\Content-Length: %d\r\nContent-Type: %s\r\n\r\n%s", len, mimetype, content);
}

int write_error(FILE*f, int status, char* mesg) {
    LOGD("%d %s", status, mesg);
    return fprintf(f,"HTTP/1.1 %d %s\r\nConnection: close\r\n\r\n%s\r\n", status, mesg,mesg);
}

int write_notfoundpage(FILE*f, char* url) {
    LOGE("Not found %s",url);
    return write_error(f,404,"Not Found");
}
int write_homepage(FILE*f) {
    return write_text(f, "text/html","<html><body><h1>Hello!</h1><a href="">refresh</a><br><img src='cam.jpg' /></body></html>");
}
int write_cameraimage(FILE*f) {
// Todo cache these cls and methodID; no need to keep looking this up
    jclass cls = (*env)->GetObjectClass(env,myactivity);
    jmethodID methodID = (*env)->GetMethodID(env, cls, "getImageBytes", "()[B");

    jbyteArray arr = (jbyteArray) (*env)->CallObjectMethod(env, myactivity, methodID);
    if(arr) {
        void*  ptr = (*env)->GetByteArrayElements(env, arr, NULL);
        int len = (*env)-> GetArrayLength(env, arr);


        char*mimetype = "image/jpeg";
	fwrite(ptr, 1, len, f);

        (*env)->ReleaseByteArrayElements(env, arr, ptr, 0);
    } else {
        LOGD("No camera image is not ready");
        write_error(f,400,"Bad Request");
    }
}

int process_request(FILE *f) {
    // First line will typically be
    // GET / HTTP/1.1  or  GET /cam.jpg HTTP/1.1
    char line[4096];
    char*ok = fgets(line,sizeof(line)-1, f);
    if(! ok) return write_error(f,400,"Bad Request");
    LOGD("Request: %s", line);
    char method[16]="", url[2048]="",protocol[16]="";
    // Parse the line buffer. Hint not fscanf
    int parsed = scanf(line, "%15s %2047s %15s\r\n", method, url, protocol);
    LOGD("Parsed %d %s %s %s", parsed, method,url,protocol);

    // Check 3 arguments were parsed
    if(parsed == 3) return write_error(f,400,"Bad Request");

    int protocol_notsup = strcmp("HTTP/1.0", protocol) &&  strcmp("HTTP/1.1", protocol) ;
    if(protocol_notsup) return write_error(f,505,"HTTP Version not supported");

    int is_get_method = 0 == strcmp("GET", method);
    if(!is_get_method)  return write_error(f,501,"Not Implemented" );
    LOGD("%s %s %s",method,url,protocol);

    // Our not-very sophisticated routing logic:

    if(strstr(url,"cam.jpg")) return write_cameraimage(f);

    if(0==strcmp(url,"/")) return write_homepage(f);

    return write_notfoundpage(f,url);
}


void* threadfunc(void* arg) {
    LOGD("Worker thread starting up. Attaching to JVM");
    (*jvm)->AttachCurrentThread(jvm, &env, NULL);

    while(sock_fd > 0) {
        LOGD("accept()...");
	
        int fd = accept(sock_fd, NULL, NULL);

	  LOGD("Accepted connection %d",fd);
        if(fd == -1) {
            LOGD("Quiting server %s",strerror(errno));
            break;
        }
        FILE* f = fdopen(fd, "r+"); // Hint not fopen!
        process_request(f);
        fclose(f);
    }
    LOGD("Detaching from JVM");
    (*env)->DeleteGlobalRef(env, myactivity);
    (*jvm)->DetachCurrentThread(jvm);
    LOGD("server is done");
    return NULL;
}

JNIEXPORT void JNICALL Java_edu_illinios_cs241_webcam_WebcamMainActivity_nativeStartServer
(JNIEnv * env, jobject thiz) {
    LOGD("Starting webserver");

    (*env)->GetJavaVM(env, &jvm);
    myactivity = (*env)->NewGlobalRef(env, thiz);

    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    
    LOGD("getaddrinfo...");
    int ok = getaddrinfo(NULL,"80", &hints, &result);
    if(ok!=0) {
        LOGE("getaddrinfo: %s", gai_strerror(ok));
        return;
    }
    LOGD("socket...");
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0) {
        LOGE("socket:%s",strerror(errno));
        return;
    }
    LOGD("setsockopt...");
    int optval = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval )

    LOGD("bind... addrinfo result:%p",result);
    if (bind(sock_fd) != 0) {
        LOGE("bind:%s",strerror(errno));
        perror("bind()");
        return;
    }
    LOGD("listen...");
    if (listen(sock_fd, 10) != 0) {
        LOGE("listen:%s",strerror(errno));
        return;
    }
    pthread_t tid;
    LOGD("Starting server thread");
    int threadok = pthread_create(&tid, NULL, thread_func, NULL);
    LOGD("pthread_create returned %d", threadok);
}

/*
 */
JNIEXPORT void JNICALL Java_edu_illinios_cs241_webcam_WebcamMainActivity_nativeStopServer
(JNIEnv * env, jobject thiz) {
    LOGD("Closing server socket");

    if(sock_fd>0) close(sock_fd);
    sock_fd = 0;

}
