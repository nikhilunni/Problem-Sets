#include "utils.h"

uint32_t extract_tag(uint32_t address, const CacheConfig& cache_config) {
  uint32_t tagBits = cache_config.get_num_tag_bits();  
  return address >> (32-tagBits);
}

uint32_t extract_index(uint32_t address, const CacheConfig& cache_config) {
  uint32_t indexBits = cache_config.get_num_index_bits();
  uint32_t blockOffsetBits = cache_config.get_num_block_offset_bits();
  uint32_t tagMask = (1 <<(blockOffsetBits+indexBits)) - 1;
  return (address&tagMask) >> blockOffsetBits;
}

uint32_t extract_block_offset(uint32_t address, const CacheConfig& cache_config) {
  uint32_t blockOffsetBits = cache_config.get_num_block_offset_bits();
  uint32_t mask = (1<<blockOffsetBits)-1;
  return (address&mask);
}
