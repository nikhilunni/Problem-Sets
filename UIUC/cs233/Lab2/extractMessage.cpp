/**
 * @file
 * Contains the implementation of the extractMessage function.
 */

#include <iostream> // might be useful for debugging
#include "extractMessage.h"

using namespace std;

string extractMessage(const bmp & image) {
	int HUGE_BUFFER = 9999999;
	string message(HUGE_BUFFER,0);
	int counter = 0;
	int width = image.width(), height = image.height();
	char cur = 0;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++, counter++) {
			short pos = counter % 8;
			int idx = counter / 8;

			if(pos == 0) {
				cur = 0;
			}

			const pixel* p = image(j,i);
			int g = p->green;
			cur = cur | ((g&1) << (8-pos-1));
			if(pos == 7) {
				message.at(idx) = cur;
				if(message[idx] == 0)
					return message;
			} 
		}
	}
	// TODO: write your code here
	// http://en.cppreference.com/w/cpp/string/basic_string#Operations might be of use
	// because image is a const reference, any pixel you get needs to be stored in a const pointer
	// i.e. you need to do
	// const pixel * p = image(x, y);
	// just doing
	// pixel * p = image(x, y);
	// would give a compilation error

	return message;
}
