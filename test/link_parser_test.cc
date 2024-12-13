#include <gtest/gtest.h>
#include "link_parser.h"

TEST(LinkParserTest, ConstrutorTest){

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError eResult = doc.LoadFile("../exemples/.urdf/link.urdf");
    if (eResult != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error loading XML file: " << doc.ErrorStr() << std::endl;
    }
    tinyxml2::XMLElement* config = doc.FirstChildElement("link");
    

    tinyurdf::LinkParser<> parser(config);
    ASSERT_TRUE(parser.parse());

    urdf::Link<>* link = parser.getLink();

    std::string link_name_expected = std::string("my_link");
    ASSERT_STREQ(link->name.c_str(),link_name_expected.c_str());
    
    ASSERT_DOUBLE_EQ(link->inertial->ixx, 100);
    ASSERT_DOUBLE_EQ(link->inertial->ixy, 0);

    std::string material_name_expected = std::string("Cyan");
    ASSERT_STREQ(link->visual->material_name.c_str(), material_name_expected.c_str());

    std::string material_texture_expected = std::string("file1.STL");
    EXPECT_TRUE(link->visual->material != nullptr );
    ASSERT_DOUBLE_EQ(link->material->density, 1.0);
    ASSERT_STREQ(link->visual->material->texture_filename.c_str(), material_texture_expected.c_str());
};
