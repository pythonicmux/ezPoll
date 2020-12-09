#include <gtest/gtest.h>
#include <ezPoll.hpp>

TEST(gtestInit, BasicEzTest1) {
    EXPECT_EQ(1,1);
}

TEST(gtestInit, BasicEzTest2) {
    EXPECT_NE(ezPoll::t,1);
}
