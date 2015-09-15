extern "C" {
#include "datastore_control.h"
#include "test_utility.h"
}

#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

using namespace std;

int STRESS_NUMBER = 100;

char rand_char()
{
    return (char)( (rand() % 52) + 65);
}

/*
 * Test 3 thread function
 * 
 * Description:
 * Inserts and updates values based on the "start" arg being passed to it. 
 * If the arg is 0, it does even-valued inserts/updates/gets/deletes.
 * If the arg is 1, it does the same for odd values
 *
 */
void* thread_test3(void* arg){
    
    int start = *((int*)arg);
    int i;
    for(i=start; i<STRESS_NUMBER; i+=6){
	if (!STD_ADD_SUCCESS(i)){
	  printf("%d : failed add\n", start);
	    fail(3);
	}
    }
    printf("%d : passed add\n", start);
    for(i=start; i<STRESS_NUMBER; i+=6){
	if (!STD_UPDATE_SUCCESS(i, i+1, 1)){
	  printf("%d : failed update\n", start);
	    fail(3);
	}
    }
    printf("%d : passed update\n", start);
    for(i=start; i<STRESS_NUMBER; i+=6){
	if (!STD_GET_SUCCESS(i, i+1, 2)){
	  printf("%d : failed get\n", start);
	    fail(3);
	}
    }
    printf("%d : passed get\n", start);
    for(i=start; i<STRESS_NUMBER; i+=6){
	if (!STD_DELETE_SUCCESS(i)){
	  printf("%d : failed delete\n", start);
	    fail(3);
	}
    }

    printf("%d : failed delete\n", start);
    for(i=start; i<STRESS_NUMBER; i+=6){
	if (!STD_GET_FAILURE(i, i, 2)){
	  printf("%d : failed get_failure\n", start);
	    fail(3);
	}
    }
    printf("%d : passed get_failure\n", start);
}

/*
 * Test 1 function
 * 
 * Description:
 * Runs a series of inserts, updates, gets and deletes as 
 * well as a GET_FAILURE test, to ensure that the keys have
 * been properly deleted. Does a load() at the beginning and 
 * a save() at the end.
 *
 */

void test1()
{ 
    init();
    load();
    
    int i;
    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_ADD_SUCCESS(i)){
	    fail(1);
	}
    }
    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_UPDATE_SUCCESS(i, i+1, 1)){ 
	    fail(1);
	}
    }
    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_GET_SUCCESS(i, i+1, 2)){
	    fail(1);
	}
    }
    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_DELETE_SUCCESS(i)){
	    fail(1);
	}
    }   
    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_GET_FAILURE(i, i, 2)){
	    fail(1);
	}
    }
    save();				       
    success(1);
}

/*
 * Test 2 function
 * 
 * Description:
 * Runs the same series of tests at Test 1 but 
 * does a save() and a load() after each operation,
 * except for GET.
 *
 */

void test2()
{ 
    init();
    load();
    int i;
    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_ADD_SUCCESS(i)){
	    fail(2);
	}
    }
    save();
    load();

    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_UPDATE_SUCCESS(i, i+1, 1)){
	    fail(2);
	}
    }
   
    save();
    load();    

    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_GET_SUCCESS(i, i+1, 2)){
	    fail(2);
	}
    }
    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_DELETE_SUCCESS(i)){
	    fail(2);
	}
    }
    save();
    load();

    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_GET_FAILURE(i, i, 2)){
	    fail(2);
	}
    }
    save();
    success(2);
}

/*
 * Test 3 function
 * 
 * Description:
 * A multi-threaded test, that creates two threads that runs 
 * the thread_test3 function with two different arguments. It 
 * executes a load() at the beginning and a save() at the end
 *
 */

void test3()
{
    init();
    load();

    int e = 0;
    int o = 1;
    int l = 2;
    int r = 3;
    int f = 4;
    int a = 5;
    pthread_t * thread1 = (pthread_t *) malloc(sizeof(pthread_t));
    pthread_t * thread2 = (pthread_t *) malloc(sizeof(pthread_t));
    pthread_t * thread3 = (pthread_t *) malloc(sizeof(pthread_t));
    pthread_t * thread4 = (pthread_t *) malloc(sizeof(pthread_t));
    pthread_t * thread5 = (pthread_t *) malloc(sizeof(pthread_t));
    pthread_t * thread6 = (pthread_t *) malloc(sizeof(pthread_t));
    pthread_create(thread1, NULL, thread_test3, &e);
    pthread_create(thread2, NULL, thread_test3, &o);
    pthread_create(thread3, NULL, thread_test3, &l);
    pthread_create(thread4, NULL, thread_test3, &r);
    pthread_create(thread5, NULL, thread_test3, &f);
    pthread_create(thread6, NULL, thread_test3, &a);
    pthread_join(*thread1, NULL);
    pthread_join(*thread2, NULL);
    pthread_join(*thread3, NULL);
    pthread_join(*thread4, NULL);
    pthread_join(*thread5, NULL);
    pthread_join(*thread6, NULL);

    free(thread1);
    free(thread2);
    free(thread3);
    free(thread4);
    free(thread5);
    free(thread6);
    
    print();

    save();
    success(3);
}

/*
 * Test 4 function
 * 
 * Description:
 * Runs the same series of tests at Test 1 but the input
 * key and values are randomly generated strings of arbitrary
 * length. There is a save() at the beginning and a load() at 
 * the end.
 *
 */

void test4()
{
    srand(time(0));
    string data[STRESS_NUMBER];
       
    for(int j = 0; j < STRESS_NUMBER; j++){
	
	int len = 25 + ( std::rand() % 39 );
	string key;	

	for(int i = 0; i < len; i++){	 
	    key += rand_char();
	    if (i%7 == 0) 
		key[i] = toupper(key[i]); 
	}	
	data[j] = key;
    }
    
    init();
    load();
    int i;
    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_ADD2_SUCCESS(data[i].c_str(), data[i].c_str())){
	    fail(4);
	}
    }
    for(i=1; i<STRESS_NUMBER; i++){
	if (!STD_UPDATE2_SUCCESS(data[i].c_str(), data[i-1].c_str(), 1)){
	    fail(4);
	}
    }
    for(i=1; i<STRESS_NUMBER; i++){
	if (!STD_GET2_SUCCESS(data[i].c_str(), data[i-1].c_str(), 2)){
	    fail(4);
	}
    }
    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_DELETE2_SUCCESS(data[i].c_str())){
	    fail(4);
	}
    }
    for(i=0; i<STRESS_NUMBER; i++){
	if (!STD_GET2_FAILURE(data[i].c_str(), data[i].c_str(), 0)){
	    fail(4);
	}
    }
    save();
    success(4);
}

/*
 * Test 5 function
 * 
 * Description:
 * Runs the same series of tests at Test 4 with the 
 * input string keys and values. However, this test 
 * does the following followed by a save() and load() for each:
 * 
 *  1) Insert the first half of the keys
 *  2) Insert the second half of the keys
 *  3) Delete the first half of the keys 
 *  4) Update the second half of the keys
 *  5) Delete the second half of the keys
 * 
 *
 */

void test5()
{
    srand(time(0));
    string data[STRESS_NUMBER];
    
    for(int j = 0; j < STRESS_NUMBER; j++){
	
	int len = 25 + ( std::rand() % 39 );
	string key;
	
	for(int i = 0; i < len; i++){
	    key += rand_char();
	    if (i%7 == 0)
		key[i] = toupper(key[i]);
	}
	data[j] = key;
    }
    
    init();
    load();
    
    int i;
    for(i=0; i<STRESS_NUMBER/2; i++){
	if (!STD_ADD2_SUCCESS(data[i].c_str(), data[i].c_str())){      
	    fail(5);
	}
    } 
    save();
    load();
    
    for(i=STRESS_NUMBER/2; i < STRESS_NUMBER; i++){
	if (!STD_ADD2_SUCCESS(data[i].c_str(), data[i].c_str())){                          
	    fail(5);
	}	
    }
    
    for(i=0; i<STRESS_NUMBER/2; i++){
	if(!STD_DELETE2_SUCCESS(data[i].c_str())){
	    fail(5);
	}
    }
    save();
    load();
    
    for(i=(STRESS_NUMBER/2)+1; i<STRESS_NUMBER; i++){
        if (!STD_UPDATE2_SUCCESS(data[i].c_str(), data[i-1].c_str(), 1)){
            fail(5);
        }
    }
    save();
    load();
    
    for(i=(STRESS_NUMBER/2); i<STRESS_NUMBER; i++){
	if (!STD_DELETE2_SUCCESS(data[i].c_str())){
	    fail(5);
	}
    }
    save();
    success(5);
}

/*
 *  Main function of the tester
 *
 *  Run ./tester <test-num> on the commandline to run a specific test-case.
 * 
 *  If no argument is provided, the tester will run all tests. It will
 *  also print out the time taken to run them to give you a general idea 
 *  of how fast your implementation is. The the contents of the data folder
 *  is cleared after each test is completed through the success(i) function.  
 *
*/

int main(int argc, char **argv)
{ 
    
    mkdir("data",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    if(argc!=1){	
	switch(atoi(argv[1])){
	case 1:
	    test1();
	    break;
	case 2:
	    test2();
	    break;
	case 3:
	    test3();
	    break;
	case 4:
	    test4();
	    break;
	case 5:
	    test5();
	    break;
	default:
	    break;
	}
    }else{
	clock_t t;
	t = clock();
	test1();
	test2();
	test3();
	test4();
	test5();

	t = clock() - t;	
	cout << "You passed all test-cases!" << endl;
	printf("All test-cases took %f seconds \n",((float)t)/CLOCKS_PER_SEC);

    }    
    system("rm -rf data");
    return 0;
}

