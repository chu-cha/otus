#include <gtest/gtest.h>

#include "lib.h"

TEST(HelloTest, BasicAssertions) {
  EXPECT_GT(version(), 0);
}
