#include "lib.h"

#if USE_GTEST == 1
#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions) {
  EXPECT_GT(version(), 0);
}
#else

#define BOOST_TEST_MODULE test_version

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version) {
	BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_SUITE_END()
#endif

