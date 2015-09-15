/* 
 * CS 241
 * The University of Illinois
 */

#ifndef _PART2_H_
#define _PART2_H_

#include "sql.h"

extern query_t* QUERY; // current query to run

void map(int fd, const char *data);
const char *reduce(const char *value1, const char *value2);

#endif
