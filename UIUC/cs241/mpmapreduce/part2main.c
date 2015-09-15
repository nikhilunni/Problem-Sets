/* 
 * CS 241
 * The University of Illinois
 */

#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "libmapreduce.h"
#include "libds/libds.h"

#include "part2.h"

int main(int argc, char *argv[])
{
    int TEST_CASE;
    if (argc > 1)
    {
        TEST_CASE = atoi(argv[1]);
    } else {
        printf("%s\n", "Please enter a valid test case between 1 and 5.\n\t./part2 <testcase>");
        return 0;
    }

    data_t* data = getData();
    int num_columns = data->num_columns; 
    char ** values = data->values;
    QUERY = getQuery(num_columns, TEST_CASE);

    /* run map reduce */
    mapreduce_t mr;
    mapreduce_init(&mr, map, reduce);
    mapreduce_map_all(&mr, (const char **)values);
    mapreduce_reduce_all(&mr);

    printQueryResults(&mr, TEST_CASE);
    mapreduce_destroy(&mr);

    free(data->values);
    free(data);
    free(QUERY->selected_columns);
    free(QUERY);
    return 0;
}