#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "transpose.h"

// will be useful
// remember that you shouldn't go over SIZE
using std::min;

// modify this function to add tiling
void 
transpose_tiled(int** src, int** dest) { 
  int TILE_WIDTH = 8;
  for (int i = 0 ; i < SIZE ; i+= TILE_WIDTH) { 
    for (int j = 0 ; j < SIZE ; j+= TILE_WIDTH) {
      for(int x = i; x < min(i+TILE_WIDTH,SIZE); x++) {
	for(int y = j; y < min(j+TILE_WIDTH,SIZE); y++) {
	  dest[x][y] = src[y][x];
	}
      }
    } 
  }
}	
