/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/** 
 * Calculates the nth Fibonacci number where the zeroth is defined to be 
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
	if(n == 0)
		return 0;
	if(n == 1)
		return 1;
    return fib(n-1) + fib(n-2);
}

/** 
 * Calculates the nth Fibonacci number where the zeroth is defined to be 
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */

map<unsigned long, unsigned long> memo;

unsigned long memoized_fib(unsigned long n)
{
    if(n == 0)
		return 0;
	if(n == 1)
		return 1;
	unsigned long fib1 = (memo.count(n-1) > 0 ? memo.at(n-1) : memoized_fib(n-1));
	unsigned long fib2 = (memo.count(n-2) > 0 ? memo.at(n-2) : memoized_fib(n-2));
	memo[n] = (fib1+fib2);
	return fib1 + fib2;
}
