#include "cacheconfig.h"
#include "utils.h"
#include <math.h>

CacheConfig::CacheConfig(uint32_t size, uint32_t block_size, uint32_t associativity)
: _size(size), _block_size(block_size), _associativity(associativity) {
  /**
   * TODO
   * Compute and set `_num_block_offset_bits`, `_num_index_bits`, `_num_tag_bits`.
  */ 
  uint32_t numBlocks = size / block_size;
  uint32_t indeces = numBlocks / associativity;
  uint32_t s = (int)(log2(indeces) + 0.5);
  uint32_t m = 32;
  uint32_t o = (int)(log2(block_size) + 0.5);
  _num_tag_bits = m-s-o;
  _num_index_bits = s;
  _num_block_offset_bits = o;
}
