/* 
 * CS 241
 * The University of Illinois
 *
 */

#ifndef _SQL_H_
#define _SQL_H_
#include "libmapreduce.h"

typedef enum {MAX, TOP3, COUNT, SUM} AGGREGATE_FUNCTION;

typedef struct _query_t
{
    int* selected_columns;  /* indeces of the columns to select.
                            last element of the array will be -1 */
    int (*where_condition)(const char*); /* checks the where condition.
                                        return 1 or 0 given a row */
    int group_by_column; /* which column to group by.
                            -1 if there's no aggregation */
    int aggregate_func_column; /* argument to the aggregate function */
    AGGREGATE_FUNCTION func; /* aggregate function to use in conjunction 
                                with group by */
} query_t;


typedef struct _data_t
{
    int num_columns; /* number of columns in table */
    char** values;  /* table's rows split up for map-reduce.
                    each row ends with a new line character ('\n').
                    each column of a row is split by a space (' ') */

} data_t;

char** tokenize(const char* row, char delim, int * num_tokens);

data_t* getData();
query_t* getQuery(int columns, int testcase);

void printQueryResults(mapreduce_t *mr, int test_case);

// sample queries, replace which one is used in getQuery()
query_t* buildQuery1(int num_columns);
query_t* buildQuery2(int num_columns);
query_t* buildQuery3(int num_columns);
query_t* buildQuery4(int num_columns);
query_t* buildQuery5(int num_columns);
query_t* buildQuery6(int num_columns);
query_t* buildQuery7(int num_columns);

#endif
