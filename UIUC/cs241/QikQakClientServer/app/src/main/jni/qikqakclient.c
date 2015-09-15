#include <jni.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <android/log.h>

// To include this in other projects:
// Add
//  <uses-permission android:name="android.permission.INTERNET" />
// in your AndroidManifest.xml outside of the application tag

#define LOG_TAG ("SOCKET-AWESOMENESS")

#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)

int socket_fd = -1;

void log_error_and_close_fd(char* mesg) {

  if(socket_fd >0 ) close(socket_fd);
  socket_fd = -1;

  LOGE("%s failed:%s",mesg, strerror(errno));
}


//    public native void sendMessage(String message);

JNIEXPORT void JNICALL Java_edu_illinios_cs241_clientserver_MainActivity_sendMessage
  (JNIEnv * env, jobject thiz, jstring j_mesg) {

   if(socket_fd <0) {
     LOGD("sendMessage() ignored because socket_fd<0");
     return;
   }

   const char *mesg = (*env)->GetStringUTFChars(env, j_mesg, 0);

   int len = write(socket_fd, mesg, strlen(mesg));

   LOGD("write(%s) return %d", mesg, len);

   if(len == -1) LOGE("write():%s", strerror(errno));

   (*env)->ReleaseStringUTFChars(env, j_mesg, mesg);
  }


void connect_to_server(struct addrinfo *ai) {

  LOGD("socket()...");

  socket_fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
  if(socket_fd == -1) { log_error_and_close_fd( "socket()"); return; }

  // Connect will block until the stream is ready

  LOGD("connect()...");
  if( connect(socket_fd,ai->ai_addr, ai->ai_addrlen ) ) {
      log_error_and_close_fd("connect()");
      return;
  }

  LOGD("write(Hi)... to socket_fd %d", socket_fd);

  #define WELCOME ("Android(" __DATE__ " " __TIME__ ")")
  int len = write(socket_fd,WELCOME,strlen(WELCOME));

  if(len != strlen(WELCOME))  {
    log_error_and_close_fd("write()");
    return;
  }


  LOGD("Connect succeeded");
}

JNIEXPORT jbyteArray JNICALL Java_edu_illinios_cs241_clientserver_MainActivity_readNextMessage(JNIEnv* env, jobject thiz) {

  char buffer[1024];
  int len = read(socket_fd,buffer,sizeof(buffer)-1);

  if(len <1 || socket_fd == -1) {
    LOGE("readNextMessage() returning NULL (fd=%d, len=%d)", socket_fd, len);
    return NULL;
  }

  jbyteArray bytes = (*env)->NewByteArray(env,len);
  (*env)->SetByteArrayRegion(env, bytes, 0, len, buffer);

  buffer[len]='\0';
  LOGD("readNextMessage: %s", buffer);

  return bytes;

}


// public native void closeTCPConnection();
JNIEXPORT void JNICALL Java_edu_illinios_cs241_clientserver_MainActivity_closeConnection
  (JNIEnv * env, jobject thiz) {

     if(socket_fd>0) {
       LOGD("close()");
       close(socket);
     }
     socket_fd = -1;

}

// public native void connectToServer(String node, String service);

JNIEXPORT jboolean JNICALL Java_edu_illinios_cs241_clientserver_MainActivity_connectToServer
  (JNIEnv * env, jobject thiz, jstring j_addr, jstring j_service) {

  if(j_addr == NULL || j_service == NULL) {
     Java_edu_illinios_cs241_clientserver_MainActivity_closeConnection(env,thiz);
     return 0;
  }

  const char *addr = (*env)->GetStringUTFChars(env, j_addr, 0);
  const char *service = (*env)->GetStringUTFChars(env, j_service, 0);


  struct addrinfo hints, *ai = NULL;
  memset(&hints,0,sizeof(hints));

  hints.ai_family= AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  LOGD("getaddrinfo(%s, %s,...)",addr,service);

  int errcode = getaddrinfo(addr, service, &hints, &ai);

  if(errcode) {
     char *err_mesg = gai_strerror(errcode);
     LOGE("getaddrinfo():%s",err_mesg );
  } else {
     connect_to_server(ai);
  }

  if(ai) freeaddrinfo(ai);

  (*env)->ReleaseStringUTFChars(env, j_addr, addr);
  (*env)->ReleaseStringUTFChars(env, j_service, service);

  return socket_fd != -1  ;
 }
