/** @file datastore.h */
#ifndef __DS_H__
#define __DS_H__
#define INIT_CAPACITY 512
#define CAPACITY_MULTIPLIER 10
#define NUM_LOCKS 16

#include <pthread.h>
//#include "datastore_control.h"

typedef struct _kvpair_t 
{
  char *key;
  char *val;
  unsigned long rev;
  struct _kvpair_t *next;
  struct _kvpair_t *prev;
} kvpair_t;

typedef struct _datastore_t
{
  int capacity;
  int num_elems;
  int file_size;
  kvpair_t **table;
  pthread_mutex_t locks[NUM_LOCKS]; //Striped locking
} datastore_t;

#ifndef __JSONRES__
#define __JSONRES__
typedef struct _jsonres_t
{
  char *success;
  char *value;
  unsigned long rev;
} jsonres_t;
#endif

void datastore_init(datastore_t **d);
void datastore_load(datastore_t **d);
void datastore_destroy(datastore_t **d);
jsonres_t datastore_add(datastore_t *d, char *key, char *val);
jsonres_t datastore_update(datastore_t *d, char *key, char *val, unsigned long rev);
jsonres_t datastore_get(datastore_t *d, char *key);
jsonres_t datastore_delete(datastore_t *d, char *key);

#endif
