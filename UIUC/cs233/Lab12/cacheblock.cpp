#include "cacheblock.h"
#include <math.h>

uint32_t Cache::Block::get_address() const {
  //  uint32_t numBits = (int)(log2(_cache_config.get_block_size()) + 0.5);
  uint32_t num_block_offset_bits = _cache_config.get_num_block_offset_bits();
  uint32_t num_index_bits = _cache_config.get_num_index_bits();
  
  
  
  return (_tag << (num_block_offset_bits+num_index_bits)) +
         (_index << (num_block_offset_bits));
}
