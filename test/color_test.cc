#include <gtest/gtest.h>
#include "color.h"

namespace urdf {

TEST(ColorTest, DefaultConstructor) {
    Color<> color;  

    EXPECT_EQ(color.r, 0.0);
    EXPECT_EQ(color.g, 0.0);
    EXPECT_EQ(color.b, 0.0);
    EXPECT_EQ(color.a, 1.0);
}

TEST(ColorTest, SafeConstructor) {
    Color<> color(0.58, 1.0, 0.7, 1.0);  

    EXPECT_EQ(color.r, 0.58);
    EXPECT_EQ(color.g, 1.0);
    EXPECT_EQ(color.b, 0.7);
    EXPECT_EQ(color.a, 1.0);
}

TEST(ColorTest, StringConstructor) {
    std::string color_str = "0.5 0.6 0.7 1.0";
    Color<> color(color_str); 

    EXPECT_EQ(color.r, 0.5);
    EXPECT_EQ(color.g, 0.6);
    EXPECT_EQ(color.b, 0.7);
    EXPECT_EQ(color.a, 1.0);
}

TEST(ColorTest, ClearFunction) {
    Color<> color("0.2 0.3 0.4 0.5");  

    color.clear();  

    EXPECT_EQ(color.r, 0.0);
    EXPECT_EQ(color.g, 0.0);
    EXPECT_EQ(color.b, 0.0);
    EXPECT_EQ(color.a, 1.0);
}

TEST(ColorTest, InvalidStringConstructor) {
    std::string invalid_color_str = "0.5 0.5 0.5";  
    Color<> color(invalid_color_str);

    EXPECT_NE(color.r, 0.5);
    EXPECT_NE(color.g, 0.5);
    EXPECT_NE(color.b, 0.5);
    EXPECT_NE(color.a, 1.0);

}

};  // namespace urdf