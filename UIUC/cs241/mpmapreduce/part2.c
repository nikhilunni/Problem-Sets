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
#include "sql.h"

query_t* QUERY; // current query to run


char* max_func(char** all_rows, int num_rows, int* totalLen) {
  int i,j, num_tokens;
  *totalLen = 0;
  for(i = 0; i < num_rows; i++)
    *totalLen += strlen(all_rows[i]) + 3; //Upper-bound = entire_row + strlen(": ") + strlen("\n")
  char** rowOut = calloc(2 * num_rows, sizeof(char*) ); //i = key, i+1 = value
  char* out = malloc(*totalLen);
  out[0] = '\0';
  
  for(i = 0; i < num_rows; i++) {
    if(QUERY->where_condition(all_rows[i])) { //If this row should be included...
      char** tokenized_row = tokenize(all_rows[i], ' ', &num_tokens);

      //Find first row of NULL or of the same string as the group column string
      for(j = 0; rowOut[j] != NULL && strcmp(rowOut[j], tokenized_row[QUERY->group_by_column]) != 0; j += 2) {}

      if(rowOut[j] == NULL || atoi(rowOut[j+1]) < atoi(tokenized_row[QUERY->aggregate_func_column])) {
	rowOut[j] = realloc(rowOut[j], strlen(tokenized_row[QUERY->group_by_column]) );
	strcpy(rowOut[j], tokenized_row[QUERY->group_by_column]);

	rowOut[j+1] = realloc(rowOut[j+1], strlen(tokenized_row[QUERY->aggregate_func_column]) );
	strcpy(rowOut[j+1], tokenized_row[QUERY->aggregate_func_column]);
      }

      for(j = 0; j < num_tokens; j++)
	free(tokenized_row[j]);
      free(tokenized_row);
    }
  }
  for(i = 0; rowOut[i] != NULL; i += 2) {
    strcat(out, rowOut[i]); free(rowOut[i]);
    strcat(out, ": ");
    strcat(out, rowOut[i+1]); free(rowOut[i+1]);
    strcat(out, "\n");
  }
  free(rowOut);
  return out;
}

char* top3_func(char** all_rows, int num_rows, int* totalLen) {
  int i,j,k,l, num_tokens;
  *totalLen = 0;
  for(i = 0; i < num_rows; i++)
    *totalLen += strlen(all_rows[i]) + 3; //Upper-bound = entire_row + strlen(": ") + strlen("\n")
  char** rowOut = calloc(4 * (num_rows+1), sizeof(char*) ); //i = key, i+1 = value1, i+2 = value2, i+3 = value3
  char* out = malloc(*totalLen);
  out[0] = '\0';
  
  for(i = 0; i < num_rows; i++) {
    if(QUERY->where_condition(all_rows[i])) { //If this row should be included...
      char** tokenized_row = tokenize(all_rows[i], ' ', &num_tokens);

      //Find first row of NULL or of the same string as the group column string
      for(j = 0; rowOut[j] != NULL && strcmp(rowOut[j], tokenized_row[QUERY->group_by_column]) != 0; j += 4) {}
      if(rowOut[j] == NULL) {
	rowOut[j] = malloc(strlen(tokenized_row[QUERY->group_by_column]) );
	strcpy(rowOut[j], tokenized_row[QUERY->group_by_column]);

	rowOut[j+1] = malloc(strlen(tokenized_row[QUERY->aggregate_func_column]) );
	strcpy(rowOut[j+1], tokenized_row[QUERY->aggregate_func_column]);
      } else {
	//Find smallest element, or NULL if there are remaining slots
	for(k = j+1; rowOut[k] != NULL && atoi(rowOut[k]) > atoi(tokenized_row[QUERY->aggregate_func_column]); k++) {}

	//Shift all elements over by 1
	for(l = j+3; l > k; l--) {
	  if(rowOut[l-1] != NULL) {
	    rowOut[l] = realloc(rowOut[l], strlen(rowOut[l-1])); 
	    strcpy(rowOut[l], rowOut[l-1]);
	  }
	}
      

	//Copy over new element to our freed up slot
	rowOut[k] = realloc(rowOut[k], strlen(tokenized_row[QUERY->aggregate_func_column]));
	strcpy(rowOut[k], tokenized_row[QUERY->aggregate_func_column]);
      }

      for(j = 0; j < num_tokens; j++)
	free(tokenized_row[j]);
      free(tokenized_row);
    }
  }
  for(i = 0; i < num_rows*4 && rowOut[i] != NULL; i += 4) {
    strcat(out, rowOut[i]); free(rowOut[i]);
    strcat(out, ": ");
    for(j = i+1; j <= i+3 && rowOut[j] != NULL; j++) {
      strcat(out, rowOut[j]);
      if(j < i+3 && rowOut[j+1] != NULL)
	strcat(out, " ");
      free(rowOut[j]);
    }
    strcat(out, "\n");
  }
  free(rowOut);
  return out;
}


char* count_func(char** all_rows, int num_rows, int* totalLen) {
  int i,j, num_tokens;
  *totalLen = 0;
  for(i = 0; i < num_rows; i++)
    *totalLen += strlen(all_rows[i]) + 3; //Upper-bound = entire_row + strlen(": ") + strlen("\n")
  char** rowOut = calloc(2 * num_rows, sizeof(char*) ); //i = key, i+1 = value
  char* out = malloc(*totalLen);
  out[0] = '\0';
  
  for(i = 0; i < num_rows; i++) {
    if(QUERY->where_condition(all_rows[i])) { //If this row should be included...
      char** tokenized_row = tokenize(all_rows[i], ' ', &num_tokens);

      //Find first row of NULL or of the same string as the group column string
      for(j = 0; rowOut[j] != NULL && strcmp(rowOut[j], tokenized_row[QUERY->group_by_column]) != 0; j += 2) {}

      if(rowOut[j] == NULL) {
	rowOut[j] = malloc(strlen(tokenized_row[QUERY->group_by_column]) );
	strcpy(rowOut[j], tokenized_row[QUERY->group_by_column]);

	rowOut[j+1] = malloc(20);
	sprintf(rowOut[j+1], "%d", 1);
      } else {
	sprintf(rowOut[j+1], "%d", atoi(rowOut[j+1]) + 1);
      }

      for(j = 0; j < num_tokens; j++)
	free(tokenized_row[j]);
      free(tokenized_row);
    }
  }
  for(i = 0; rowOut[i] != NULL; i += 2) {
    strcat(out, rowOut[i]); free(rowOut[i]);
    strcat(out, ": ");
    strcat(out, rowOut[i+1]); free(rowOut[i+1]);
    strcat(out, "\n");
  }
  free(rowOut);
  return out;
}
char* sum_func(char** all_rows, int num_rows, int* totalLen) {
  int i,j, num_tokens;
  *totalLen = 0;
  for(i = 0; i < num_rows; i++)
    *totalLen += strlen(all_rows[i]) + 3; //Upper-bound = entire_row + strlen(": ") + strlen("\n")
  char** rowOut = calloc(2 * num_rows, sizeof(char*) ); //i = key, i+1 = value
  char* out = malloc(*totalLen);
  out[0] = '\0';
  
  for(i = 0; i < num_rows; i++) {
    if(QUERY->where_condition(all_rows[i])) { //If this row should be included...
      char** tokenized_row = tokenize(all_rows[i], ' ', &num_tokens);

      //Find first row of NULL or of the same string as the group column string
      for(j = 0; rowOut[j] != NULL && strcmp(rowOut[j], tokenized_row[QUERY->group_by_column]) != 0; j += 2) {}

      if(rowOut[j] == NULL) {
	rowOut[j] = malloc(strlen(tokenized_row[QUERY->group_by_column]) );
	strcpy(rowOut[j], tokenized_row[QUERY->group_by_column]);

	rowOut[j+1] = malloc(20);
	sprintf(rowOut[j+1], "%d", atoi(tokenized_row[QUERY->aggregate_func_column]));
      } else {
	sprintf(rowOut[j+1], "%d", atoi(rowOut[j+1]) + atoi(tokenized_row[QUERY->aggregate_func_column]));
      }

      for(j = 0; j < num_tokens; j++)
	free(tokenized_row[j]);
      free(tokenized_row);
    }
  }
  for(i = 0; rowOut[i] != NULL; i += 2) {
    strcat(out, rowOut[i]); free(rowOut[i]);
    strcat(out, ": ");
    strcat(out, rowOut[i+1]); free(rowOut[i+1]);
    strcat(out, "\n");
  }
  free(rowOut);
  return out;
}

char* default_func(char** all_rows, int num_rows, int* totalLen) {
  int i, j, num_tokens;
  *totalLen = 0;
  for(j = 0; j < num_rows; j++)
    *totalLen += strlen(all_rows[j]) + 4*num_rows;
  char *out = calloc(*totalLen, 1);
  out[0] = '\0';
  for(i = 0; i < num_rows; i++) {
    if(QUERY->where_condition(all_rows[i])) { //If this row should be included...
      char** tokenized_row = tokenize(all_rows[i], ' ', &num_tokens);
      int k = 0, len = 0;
      for(k = 0 ; QUERY->selected_columns[k] != -1; k++)
	len += strlen(tokenized_row[QUERY->selected_columns[k]]) + 1;
      char *rowOut = malloc(strlen(tokenized_row[0]) + 2 + len); //2 = strlen(": ")
      rowOut[0] = '\0';
      strcat(rowOut, tokenized_row[0]); strcat(rowOut, ": ");
      for(k = 0; QUERY->selected_columns[k] != -1; k++) {
	strcat(rowOut, tokenized_row[QUERY->selected_columns[k]]);
	if(QUERY->selected_columns[k+1] != -1)
	  strcat(rowOut, " ");
      }
      strcat(out, rowOut);
      strcat(out, "\n");
      for(k = 0; k < num_tokens; k++)
	free(tokenized_row[k]);
      free(tokenized_row);
      free(rowOut);
    }
  }
  return out;
}

void map(int fd, const char *data)
{
  int num_rows;
  int totalLen; 
  char** all_rows = tokenize(data, '\n', &num_rows);
  char* out;
  if(QUERY->group_by_column != -1) {
    switch(QUERY->func) {
    case(MAX):
      out = max_func(all_rows, num_rows, &totalLen); break;
    case(TOP3):
      out = top3_func(all_rows, num_rows, &totalLen); break;
    case(COUNT):
      out = count_func(all_rows, num_rows, &totalLen); break;
    case(SUM):
      out = sum_func(all_rows, num_rows, &totalLen); break;
    }
  } else { //DEFAULT CASE
    out = default_func(all_rows, num_rows, &totalLen);
  }
  strcat(out, "\n");
  write(fd, out, totalLen+1);

  free(out);
  int i;
  for(i = 0; i < num_rows; i++)
    free(all_rows[i]);
  free(all_rows);
}


const char *reduce_max(const char *value1, const char *value2) {
  int strlen1 = strlen(value1), strlen2 = strlen(value2);
  char *out;
  if(atoi(value1) > atoi(value2)) {
    out = malloc(strlen1);
    strcpy(out, value1);
  } else {
    out = malloc(strlen2);
    strcpy(out, value2);
  }
  return out;  

}
int compare_func(const void* a, const void* b) {return *((int*)b) - *((int*)a);}

const char *reduce_top3(const char *value1, const char *value2) {
  int count1,count2, i,j, elems[6];
  char** value1_elems = tokenize(value1, ' ', &count1);
  char** value2_elems = tokenize(value2, ' ', &count2);

  for(i = 0; i < count1; i++)
    elems[i] = atoi(value1_elems[i]);
  for( ; i < count1+count2; i++)
    elems[i] = atoi(value2_elems[i-count1]);
  for(j = i; j < 6; j++)
    elems[j] = -1;

  qsort(elems, 6, sizeof(int), compare_func);
  
  int length = strlen(value1) + strlen(value2);
  char *out = malloc(length); out[0] = '\0';

  char buffer[20];
  for(j = 0; j < count1+count2 && j < 3; j++) {
    sprintf(buffer, "%d", elems[j]);
    strcat(out, buffer);
    if(j < count1+count2-1 && j < 2)
      strcat(out, " ");
  }
  
  for(i = 0; i < count1; i++)
    free(value1_elems[i]);
  free(value1_elems);
  for(i = 0; i < count2; i++)
    free(value2_elems[i]);
  free(value2_elems);

  return out;
  
}
const char *reduce_count(const char *value1, const char *value2) {
  char *out = malloc(20);
  sprintf(out, "%d", atoi(value1) + atoi(value2));
  return out;
}
const char *reduce_sum(const char *value1, const char *value2) {
  return reduce_count(value1, value2);
}

const char *reduce(const char *value1, const char *value2)
{
  const char *out;
  switch(QUERY->func) {
    case(MAX):
      out = reduce_max(value1, value2); break;
    case(TOP3):
      out = reduce_top3(value1, value2); break;
    case(COUNT):
      out = reduce_count(value1, value2); break;
    case(SUM):
      out = reduce_sum(value1, value2); break;
  }
  return out;
}


