/** @file libjsonparse.h */

#ifndef _JSON_PARSE_H_
#define _JSON_PARSE_H_

#include "datastore_control.h"

int parsereq(const char * reqstr, jsonreq_t * jsonreq);
int generateres(char ** resstr, jsonres_t * jsonres, char * uri);
int istoken_str(const char * token);

#endif
