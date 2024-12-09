#include <gtest/gtest.h>
#include <tinyxml2/tinyxml2.h>
#include <Eigen/Geometry>
#include "pose.h"

TEST(PoseTest, ConstructorFromXmlElement) {
    
    const char* xmlString = R"(
        <origin xyz="1.0 2.0 3.0" rpy="0.1 0.2 0.3" />
    )";
    tinyxml2::XMLDocument doc;
    ASSERT_EQ(doc.Parse(xmlString), tinyxml2::XML_SUCCESS);
    tinyxml2::XMLElement* element = doc.FirstChildElement("origin");

    urdf::Pose<double> pose(element);

    math::Vec3<double> expectedPosition(1.0, 2.0, 3.0);
    double roll = 0.1, pitch = 0.2, yaw = 0.3;
    Eigen::AngleAxis<double> rollAngle(roll, Eigen::Vector3d::UnitX());
    Eigen::AngleAxis<double> pitchAngle(pitch, Eigen::Vector3d::UnitY());
    Eigen::AngleAxis<double> yawAngle(yaw, Eigen::Vector3d::UnitZ());
    math::Rot3<double> expectedRotation = yawAngle * pitchAngle * rollAngle;

    EXPECT_EQ(pose.position, expectedPosition);
    EXPECT_EQ(pose.rotation, expectedRotation);
};

