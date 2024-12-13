#include <gtest/gtest.h>
#include "joint_parser.h"

TEST(JointParserTest, ConstrutorTest){

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError eResult = doc.LoadFile("../exemples/.urdf/joint.urdf");
    if (eResult != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error loading XML file: " << doc.ErrorStr() << std::endl;
    }
    tinyxml2::XMLElement* config = doc.FirstChildElement("joint");
    

    tinyurdf::JointParser<> parser(config);
    ASSERT_TRUE(parser.parse());
};
