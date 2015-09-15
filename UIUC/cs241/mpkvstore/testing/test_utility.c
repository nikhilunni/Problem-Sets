#include "datastore_control.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "test_utility.h"

void fail(int i)
{
    printf("test-%d: FAIL\n",i);
    system("rm -rf data");
    exit(0);
}

void success(int i)
{
    printf("test-%d: SUCCESS\n",i);
    system("rm -rf data/*");
}

int ADD(const char * key, const char * value, const char * success)
{
    jsonreq_t input;
    input.key = strdup(key);
    input.value = strdup(value);
    jsonres_t output = process_request("/add", input);
    free(input.key);
    free(input.value);
    if (strcmp(output.success,success)){
	return 0;
    }
    return 1;
}

int STD_ADD(int i, const char * success)
{
    char str[BUFFER_LEN];
    sprintf(str, "%d", i);
    return ADD(str,str,success);
}

int UPDATE(const char * key, const char * value, int rev, const char * success)
{
    jsonreq_t input;
    input.key = strdup(key);
    input.value = strdup(value);
    input.rev = rev;
    jsonres_t output = process_request("/update", input);
    free(input.key),free(input.value);
    if (strcmp(output.success,success))
	return 0;
    if (!strcmp(success,"true"))
	if (output.rev != (rev + 1))
	    return 0;
    return 1;
}

int STD_UPDATE(int i, int j, int k, const char * success)
{
    char str1[BUFFER_LEN];
    char str2[BUFFER_LEN];
    sprintf(str1, "%d", i);
    sprintf(str2, "%d", j);
    return UPDATE(str1, str2, k, success);
}


int GET(const char * key, const char * value, int rev, const char * success)
{
    jsonreq_t input;
    input.key = strdup(key);
    jsonres_t output = process_request("/get", input);
    free(input.key);
    
    if (strcmp(output.success,success))
    {
	if(output.value!=NULL)
	    free(output.value);	
	return 0;
    }
    
    if(!strcmp(success,"true"))
    {
	if (strcmp(output.value,value)){
	    free(output.value);
	    return 0;
	}
	
	if (rev != -1){
	    if (output.rev != rev){
		if(output.value != NULL)
		    free(output.value);
		return 0;
	    }
	}
    }
    
    if(output.value!=NULL){
	free(output.value);
    }
    return 1;
}

int STD_GET(int i, int j, int k, const char * success)
{
    char str1[BUFFER_LEN];
    char str2[BUFFER_LEN];
    sprintf(str1, "%d", i);
    sprintf(str2, "%d", j);
    return GET(str1, str2, k, success);
}

int DELETE(const char * key, const char * success)
{
    jsonreq_t input;
    input.key = strdup(key);
    jsonres_t output = process_request("/delete", input);
    free(input.key);
    if (strcmp(output.success,success))
	return 0;
    return 1;
}

int STD_DELETE(int i, const char * success)
{
    char str[BUFFER_LEN];
    sprintf(str, "%d", i);
    return DELETE(str, success);
}
