// Original file by Lawrence Angrave 2015
// Changes to this file will be ignored when your project is graded

/** Open a file for writing the result. If the outfile is NULL then stdout is used instead 
 * param outfile the name of the output file.
 */
FILE* open_outfile(const char * outfile);

/**
 * read data from a file and save into an int array
 * @param infile path to the input file, the file MUST contain ONE Integer each line
 * @param data the array to save the number read from the file
 * @return the number of integer read from the input file
 */
int read_file(const char * infile, int ** data);

/**
 * direct the output to the output file
 * @param outfile path to the output file
 * @param data the integer array to be sorted
 * @param nitems number of element in the data array
 */
void print_result(const char * outfile, int * data, int nitems);


/**
 * count unique elements in the data array within a range
 * @param data the integer array
 * @param start the start of the counted range
 * @param end_exclusive the end of the counted range
 *
 */
int count_unique(int* data, int start, int end_exclusive);

/**
 * print statistic about the array to the stdout
 * It calls the count_unique.
 *
 */
void print_stat(int* data, int start, int end_exclusive);

/**
 * Merge two sorted adjacent lists into a single sorted list
 * The two lists are [start,mid) and [mid,end)   i.e. end-points are exclusive
 * This function requires temporary access to a scratch space which must be
 * at least (end-start) sized.
 * Before returning the sorted values are copied back into the data array
 * Entries in the data array before 'start' and from 'end' onwards are untouched.
 * @param data pointer to the data array to be sorted
 * @param scratch temporary space required to merge two adjacent sub-arrays together
 * @param start starting index of the first sub-array
 * @param mid starting index of the second array (first sub-array at mid-1)
 * @param end ending index (exclusive) of the second array
 */
void simple_merge(int * data, int * scratch, int start, int mid, int end);





// The following functions should really have their own .h file because they are not actually part of mpsortutil.c 

/**
 * Example single threaded code that sorts nitems integers data[0] .. data[nitems-1].
 * @param data pointer to the data (must be a valid pointer)
 * @param nitems number of entries in the data array (must be non-negative)
 */
 void baseline_nonthreaded_mergesort(int* data,int nitems);

/**
 * Multi-threaded mergesort implementation that uses a thread pool to pull tasks from a work queue 
 * @param data pointer to the data (must be a valid pointer)
 * @param nitems number of entries in the data array (must be non-negative)
*/
void my_threaded_mergesort(int* data,int nitems);

/**
 * Perform a mult-threaded streaming sort 
 */
void streaming_sort();


/**
 * Stream-based fast sort. The stream sort may be faster because you can start processing the data
 * before it has been fully read.
*/
void stream_init();


/**
 * Additional data has arrived and is ready to be processed in the buffer. 
 * This function may be called multiple times (between stream_init() and stream_en()d).
 * The buffer is re-used for new data, you will need to copy / process the data before returning from this method.
 * @param buffer pointer to the buffer. The buffer contents is only valid for the duration of the call.
 * @param count the number of items in the buffer (256 >= count > 0). This may be less than 256 for the last segment.
*/

void stream_data(int* buffer, int count);

/**
 * All data has been delivered. Your implementation should now finish writing out sorted data and verbose info.
* The output stream will be closed for you after this call returns
*/
void stream_end();

