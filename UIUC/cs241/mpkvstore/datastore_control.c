/** @file datastore_control.c */

#include <stdio.h>
#include <stdlib.h>

#include "datastore_control.h"
#include "datastore.h"

datastore_t *d;

void init()
{
  datastore_init(&d);
}

void load()
{
  datastore_load(&d);
}

void save()
{
  datastore_destroy(&d);
}

void print()
{
  printTable(d);
}

jsonres_t process_request(const char * uri, jsonreq_t request)
{
    jsonres_t response;
    if (uri)
    {
      switch(uri[1]) {
      case 'a':
	response = datastore_add(d, request.key, request.value); break;
      case 'u':
	response = datastore_update(d, request.key, request.value, request.rev); break;
      case 'g':
	response = datastore_get(d, request.key); break;
      case 'd':
	response = datastore_delete(d, request.key); break;
	/**
      case 'e':
	save(); response.success = "KEY ALREADY EXISTS"; break;
	**/
      }
    }
    return response;


}
