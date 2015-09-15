#include <gtest/gtest.h>
#include "utils.h"

TEST(Utils, Extract) {
  CacheConfig config(524288, 256, 8);
  unsigned address = 0xdeadbeef;

  EXPECT_EQ(0xef, extract_block_offset(address, config));
  EXPECT_EQ(0xbe, extract_index(address, config));
  EXPECT_EQ(0xdead, extract_tag(address, config));
}
