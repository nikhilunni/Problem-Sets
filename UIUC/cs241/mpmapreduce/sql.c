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

#include "sql.h"
#include "libmapreduce.h"


/** 
* WHERE CONDITION: 
* returns 1 for all rows
*
**/		
int where_all(const char* row){

    (void)row;
    return 1;
}

/** 
* WHERE CONDITION: 
* returns 1 for rows whose 4rd column (i.e., 3rd index) is greater than 4000
*
**/	
int where_test1(const char* row){
    
    int num_cells = 0;
    char** cells = tokenize(row, ' ', &num_cells);
    int retval = atoi(cells[3]) > 4000;

    int i = 0;
    for( ; i < num_cells; i++){
        free(cells[i]);
    }
    free(cells);
    return retval;
}

/** 
* 
* Function used to obtain input data in a data_t struct.
* 
**/
data_t* getData(){
    // ID (int) | Name (string) | State (string) | Income (int)
    char **values= malloc(7*sizeof(char*));
    values[0] = "1 Yvette CA 1234\n2 Samuel CA 2345\n3 Tobias CA 3456\n4 Caleb CA 4567\n";
    values[1] = "5 Kato CA 6543\n6 Madison MA 8765\n7 Mikayla CA 4321\n8 Darius DE 1111\n";
    values[2] = "9 Mari OH 6666\n10 Brenda PA 4444\n11 Veda GA 3333\n12 Hermione WA 9999\n";
    values[3] = "13 Nikhil CA 4999\n";
    values[4] = "14 Ron PA 4\n";
    values[5] = "15 Ken IL 5312\n16 Roger CA 1000000\n";
    values[6] = NULL;

    data_t* data = malloc(sizeof(data_t));
    data->num_columns = 4;
    data->values = values;
    return data;
}

/**
* 
* Function return the query struct based on test case selected.
*	
*/
query_t* getQuery(int num_columns, int TESTCASE){
    switch(TESTCASE){
        case 1: return buildQuery1(num_columns);
        case 2: return buildQuery2(num_columns);
        case 3: return buildQuery3(num_columns);
        case 4: return buildQuery4(num_columns);
        case 5: return buildQuery5(num_columns);
        case 6: return buildQuery6(num_columns);
        case 7: return buildQuery7(num_columns);
        default: 
            printf("%s\n", "Only testcases 1 through 5 are available. Running test case #1");
            break;
    }
    return buildQuery1(num_columns);
}

/** 
 * SQL:
 * SELECT * (from Input)
 * 
 * Description:
 * This query uses SELECT statement to extract 
 * all rows of the Input table. 
 * 
 * 
**/

query_t* buildQuery1(int num_columns) {
    
    query_t* selectAll = malloc(sizeof(query_t));
    selectAll->selected_columns = malloc(sizeof(int)*(num_columns + 1));

    int i = 0;
    for( ; i < num_columns; i++){
        selectAll->selected_columns[i] = i;
    }
    selectAll->selected_columns[i] = -1;

    selectAll->where_condition = where_all;
    selectAll->group_by_column = -1;
    return selectAll;
}

/**
 * SQL: 
 * SELECT $1, $3 (from Input) 
 * 
 * Description:
 * This query uses the SELECT statement to extract all the $1 and $3
 * rows of the Input table. 
 * 
 **/

query_t* buildQuery2(int num_columns) {
    (void) num_columns;

    int num_cols_selected = 2;
    query_t* select1and2 = malloc(sizeof(query_t));
    select1and2->selected_columns = malloc(sizeof(int)*(num_cols_selected + 1));
    select1and2->selected_columns[0] = 1;
    select1and2->selected_columns[1] = 3;
    select1and2->selected_columns[2] = -1;

    select1and2->where_condition = where_all;
    select1and2->group_by_column = -1;

    return select1and2;
}


/**
 * SQL: 
 * SELECT * (from Input) WHERE $3 > 4000
 * 
 * Description:
 * This query uses the SELECT statement and a custom WHERE 
 * condition to filter out all rows where their $3 (INCOME)
 * is greater than 4000.
 *
 * 
 **/
query_t* buildQuery3(int num_columns) {

    query_t* select3 = buildQuery1(num_columns);
    select3->where_condition = where_test1;
    return select3;
}


/**
 * SQL: 
 * SELECT MAX($3) GROUP BY $2
 *
 * Description: 
 * This query uses the MAX aggregation function.
 * This particular query is grouping by the $3 (STATE) and 
 * aggregating over $2 (INCOME),returning the MAX income in every State.
 * 
 **/
query_t* buildQuery4(int num_columns) {

    query_t* q4 = buildQuery1(num_columns);
    q4->group_by_column = 2;        
    q4->func = MAX;                 
    q4->aggregate_func_column = 3; // $3 (Income)
    q4->where_condition = where_test1;

    return q4;
}

/**
 * SQL: 
 * SELECT TOP3($3) GROUP BY $2
 *	
 * Description: 
 * This query uses a user-defined aggregation function called TOP3.
 * This particular query is grouping by the $3 (STATE) and aggregating
 * over $2 (INCOME) and will return the top 3 incomes in every State.
 * 
 **/
query_t* buildQuery5(int num_columns) {

    query_t* q5 = buildQuery4(num_columns);
    q5->func = TOP3;   
    q5->where_condition = where_test1;
    return q5;
}

/**
 * SQL: 
 * SELECT COUNT($3) GROUP BY $2 WHERE $3 > 4000
 *	
 * Description: 
 * This query uses a user-defined aggregation function called COUNT.
 * This particular query is grouping by the $3 (STATE) and aggregating
 * over $2 (INCOME) and will return the count of every State.
 * 
 **/
query_t* buildQuery6(int num_columns) {
  query_t* q6 = buildQuery4(num_columns);
  q6->func = COUNT;
  q6->where_condition = where_test1;
  return q6;
}

/**
 * SQL: 
 * SELECT COUNT($3) GROUP BY $2
 *	
 * Description: 
 * This query uses a user-defined aggregation function called COUNT.
 * This particular query is grouping by the $3 (STATE) and aggregating
 * over $2 (INCOME) and will return the count of every State.
 * 
 **/
query_t* buildQuery7(int num_columns) {
  query_t* q7 = buildQuery4(num_columns);
  q7->func = SUM;
  return q7;
}


/* 
    Splits a string into an array. Will set the number of tokens to the given int ptr.
    Returned array must be free'd.
    example
        intput: @row "1 hello world"
                @delim ' '
        output: ["1", "hello", "world"]
 */ 
char** tokenize(const char* row, char delim, int * num_tokens){
    // count number of delims
    int len = strlen(row);
    int i = 0, count = 0;
    for( ; i < len - 1; i++){
        if(row[i] == delim){
            count++;
        }
    }
    *num_tokens = count + 1;
    char** cells = malloc((*num_tokens)*sizeof(char*));
    for( i = 0 ; i < *num_tokens; i++){
        char* tmp = strchr(row, delim);
        if(tmp == NULL){
            cells[i] = strdup(row);
        }else {
            cells[i] = malloc(sizeof(char)*((tmp - row) + 1));
            strncpy(cells[i], row, tmp - row);
            cells[i][(tmp-row)] = '\0';
            row = tmp + 1;
        }
    }
    return cells;
}

void printQueryResults(mapreduce_t *mr, int test_case){
    int i;
    char buff[3];
    //query#3
    char* keys[10] = {"4", "5", "6", "7", "9", "10", "12", "13", "15", "16"} ;
    char* keysNotAllowed[6] = {"1", "2", "3", "8", "11", "14"} ;
    //query#4,5
    char* keys2[8] = {"MA", "OH", "CA", "DE", "IL", "PA", "GA", "WA"};

    switch(test_case){
        default:
        case 1:
        case 2:
            for(i = 1; i < 17; i++){
                sprintf(buff, "%d", i);
                printf("%s: %s\n", buff, mapreduce_get_value(mr, buff));
            }
            break;
        case 3:
            for(i = 0; i < 10; i++){
                printf("%s: %s\n", keys[i], mapreduce_get_value(mr, keys[i]));
            }
            for(i = 0; i < 6; i++) {
                const char* val =  mapreduce_get_value(mr, keysNotAllowed[i]);
                if(val){
                    printf("%d key is not allowed but exists in the result.\n", i);
                }
            }
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            for(i = 0; i < 8; i++){
                printf("%s: %s\n", keys2[i], mapreduce_get_value(mr, keys2[i]) );
            }
            break;
    }
}

