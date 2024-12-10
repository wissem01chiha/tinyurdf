#include <gtest/gtest.h>
#include "joint.h"

TEST(JointTest, DefaultConstructor) {
    
    urdf::Joint<> joint;
    joint.name = "TestJoint";
    joint.type = urdf::Joint<>::Type::REVOLUTE;
    joint.axis = math::Vec3<>(1.0,0.0,0.0);
    joint.child_links_name.push_back("child_link");
    joint.parent_links_name.push_back("parent_link");

    EXPECT_EQ(joint.name, "TestJoint");
    EXPECT_EQ(joint.type, urdf::Joint<>::Type::REVOLUTE);
    EXPECT_EQ(joint.axis[0], 1.0);
    EXPECT_EQ(joint.axis[1], 0.0);
    EXPECT_EQ(joint.axis[2], 0.0);
    EXPECT_EQ(joint.child_links_name.size(), 1);
    EXPECT_EQ(joint.child_links_name[0], "child_link");
    EXPECT_EQ(joint.parent_links_name.size(), 1);
    EXPECT_EQ(joint.parent_links_name[0], "parent_link");
    
    EXPECT_NE(joint.dynamics, nullptr);
    EXPECT_NE(joint.limits, nullptr);
    EXPECT_NE(joint.safety, nullptr);
    EXPECT_NE(joint.calibration, nullptr);
    EXPECT_NE(joint.mimic, nullptr);
};