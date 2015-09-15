/**
 * @file
 * Contains the implementation of the countOnes function.
 */
#include <iostream>
unsigned countOnes(unsigned input) {
	unsigned sum1 = (input & 0x55555555) + ((input & 0xAAAAAAAA) >> 1);
	unsigned sum2 = (sum1 & 0x33333333) + ((sum1 & 0xCCCCCCCC) >> 2);
	unsigned sum3 = (sum2 & 0x0F0F0F0F) + ((sum2 & 0xF0F0F0F0) >> 4);
	unsigned sum4 = (sum3 & 0x00FF00FF) + ((sum3 & 0xFF00FF00) >> 8);
	return (sum4 & 0xFFFF) + (sum4 >> 16);
}
