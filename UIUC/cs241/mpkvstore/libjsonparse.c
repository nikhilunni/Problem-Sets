/** @file libjsonparse.c */
#include <search.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "jsmn/jsmn.h"
#include "datastore_control.h"

int istoken_str(const char * token)
{
  if(token[-1]=='"')
    {
      return 1;
    }
  return 0;
}

int generateres(char ** resstr, jsonres_t * jsonres, char * uri)
{
  if (!strcmp(uri,"/get"))
    return asprintf(resstr, "{\"success\": \"%s\", \"value\": \"%s\", \"revision\":%lu}",jsonres->success, jsonres->value, jsonres->rev);

  return asprintf(resstr, "{\"success\": \"%s\"}",jsonres->success);
  //printf("The string here is %s",resstr);
  
  //return a;
}

int parsereq(const char* reqstr, jsonreq_t * jsonreq)
{ 
  if(jsonreq==NULL)
    {
      jsonreq = malloc(sizeof(jsonreq_t));
      jsonreq->key = NULL;
      jsonreq->value = NULL;
      jsonreq->rev = -1;
    }

  int r;
  jsmn_parser p;
  jsmntok_t tokens[10];
  
  jsmn_init(&p);
  //reqstr = "{\n \"key\": \"keyyy\", \n \"value\": \"ten\", \n \"revision\":554 , \n \"test\": 6679 \n }";
  r = jsmn_parse(&p, reqstr, strlen(reqstr), tokens, 9);
  //printf("The JSON string is: \n%s \n" ,reqstr);
  //printf("The number of json tokens are : %d \n", r);
  
  int i = 0;
  for(; i < r; i++)
  {
    int tokenstart = tokens[i].start;
    int tokenend = tokens[i].end;
    
    //printf("The %d ith token has the start index: %d and end index: %d \n",i,tokenstart,tokenend);
    if(i%2==1)
      {
	if(strncmp("revision", reqstr+tokenstart, (tokenend-tokenstart))==0)
	  {
	    i++;
	    tokenstart = tokens[i].start;
	    tokenend = tokens[i].end;

	    if(istoken_str(reqstr+tokenstart)==0)
	      {
		//This key's value is not a string
                
		char * rev = malloc(tokenend-tokenstart+1);
		strncpy(rev,reqstr+tokenstart,(tokenend-tokenstart));
		rev[tokenend-tokenstart] = '\0';
		jsonreq->rev = atoi(rev);
                free(rev);
  	      }
	    else
	      {
		return 1;
	      }
	  }
	else if(strncmp("key", reqstr+tokenstart, (tokenend-tokenstart))==0)
	  {
	    i++;
	    tokenstart = tokens[i].start;
	    tokenend = tokens[i].end;
	    
	    if(istoken_str(reqstr+tokenstart)==1)
	      {
		//This key's value is a string
		jsonreq->key = malloc(tokenend-tokenstart+1);
		strncpy(jsonreq->key,reqstr+tokenstart,(tokenend-tokenstart));
		jsonreq->key[tokenend-tokenstart] = '\0';
	      }
	    else
	      {
		return 1;
	      }
	  }
	else if(strncmp("value", reqstr+tokenstart, (tokenend-tokenstart))==0)
	  {  
	    i++;
	    tokenstart = tokens[i].start;
	    tokenend = tokens[i].end;
	      
	    if(istoken_str(reqstr+tokenstart)==1)
	      {
		//This key's value is a string
		jsonreq->value = malloc(tokenend-tokenstart+1);
	  	strncpy(jsonreq->value,reqstr+tokenstart,(tokenend-tokenstart));
		jsonreq->value[tokenend-tokenstart] = '\0';
	      }
	    else
	      {
		return 1;
	      }
	  }
      }
  }
  
  return 0;
}
