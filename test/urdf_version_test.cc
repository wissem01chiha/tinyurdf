#include <gtest/gtest.h>
#include "urdf_version.h"

TEST(URDFVersionTest, ConstructorAndGetters) {

    const char* version_string = "1.2"; 

    urdf::URDFVersion<> version(version_string);  

    EXPECT_EQ(version.getMajor(), 1);
    EXPECT_EQ(version.getMinor(), 2);
}

TEST(URDFVersionTest, EqualFunction) {

    const char* version_string1 = "2.5";
    const char* version_string2 = "2.5";
    const char* version_string3 = "2.6";

    urdf::URDFVersion<> version(version_string1); 
    urdf::URDFVersion<> version2(version_string2);
    urdf::URDFVersion<> version3(version_string3);

    EXPECT_TRUE(version.equal(2, 5));  
    EXPECT_TRUE(version2.equal(2, 5)); 
    EXPECT_FALSE(version3.equal(2, 5));
}

TEST(URDFVersionTest, CopyConstructor) {

    const char* version_string = "3.4";

    urdf::URDFVersion<> version(version_string);  

    urdf::URDFVersion<> copied_version(version);  

    EXPECT_EQ(copied_version.getMajor(), 3);
    EXPECT_EQ(copied_version.getMinor(), 4);
}

TEST(URDFVersionTest, Destructor) {

    const char* version_string = "1.1";
    urdf::URDFVersion<> version(version_string);  

}

TEST(URDFVersionTest, InvalidVersionString) {

    const char* invalid_version_string = "1"; 
    urdf::URDFVersion<> version(invalid_version_string);  
    EXPECT_EQ(version.getMajor(),1); 
    EXPECT_EQ(version.getMinor(),0);  
};