#include <gtest/gtest.h>
#include "urdf_utilities.h"

TEST(Str2VecTest, ValidInputSinglePrecision){

    std::string str = "1.0 2.0 3.0"; 
    std::istringstream stream(str); 
    math::Vec3<float> vec;
    str2vec(stream, vec);
    EXPECT_FLOAT_EQ(vec(0), 1.0f);  
    EXPECT_FLOAT_EQ(vec(1), 2.0f);  
    EXPECT_FLOAT_EQ(vec(2), 3.0f);  
};

TEST(Str2VecTest, ValidInputDoublePrecision) {

    std::string str = "1.0 2.0 3.0"; 
    std::istringstream stream(str); 
    math::Vec3<double> vec;   
    str2vec(stream, vec);  

    EXPECT_DOUBLE_EQ(vec(0), 1.0);  
    EXPECT_DOUBLE_EQ(vec(1), 2.0);  
    EXPECT_DOUBLE_EQ(vec(2), 3.0);  
};

TEST(Str2VecTest, ValidInputDoublePrecisionWithCString) {

    const char* str = "1.0 2.0 3.0";
    std::istringstream stream(str);
    math::Vec3<double> vec;      
    str2vec(stream, vec);           

    EXPECT_DOUBLE_EQ(vec(0), 1.0);
    EXPECT_DOUBLE_EQ(vec(1), 2.0);
    EXPECT_DOUBLE_EQ(vec(2), 3.0);
};

TEST(Str2NumTest, ConvertStringToDouble) {
    
    const char* input = "3.14159";
    double result;
    str2num<double>(input, result);   

    EXPECT_DOUBLE_EQ(result, 3.14159);   
};

TEST(SplitTest, SimpleSplit) {

    std::string input = "1.2";
    std::vector<std::string> result;
    
    urdf::split(input, result, ".");

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "1");
    EXPECT_EQ(result[1], "2");
};