
#include <gtest/gtest.h>
#include "GoGuLib.hpp"

TEST(MathTest, AddNumbers) {
    int a = 2;
    int b = 3;
    EXPECT_EQ(a + b, 5);
}

TEST(StringTest, ContainsChar) {
    std::string s = "Hello";
    EXPECT_TRUE(s.find('e') != std::string::npos);
}
