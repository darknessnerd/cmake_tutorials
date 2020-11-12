#include <string>
#include "src/include/Reverse.h"

#include <gtest/gtest.h>

class ReverseTests : public ::testing::Test
{
};

TEST_F(ReverseTests, simple )
{
    std::string toRev = "Hello";

    Reverse rev;
    std::string res = rev.reverse(toRev);

    EXPECT_EQ(res, "olleH" );

}

TEST_F(ReverseTests, empty )
{
    std::string toRev;

    Reverse rev;
    std::string res = rev.reverse(toRev);

    EXPECT_EQ(res, "" );
}
