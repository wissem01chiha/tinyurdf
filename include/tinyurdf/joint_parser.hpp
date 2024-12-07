#ifndef JOINT_PARSER_HPP
#define JOINT_PARSER_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <tinyxml2/tinyxml2.h>
#include <loguru/loguru.hpp>
#include "urdf_utilities.h"
#include "pose.hpp"
#include "joint.hpp"

namespace tinyurdf {

  template<typename T = double >
  class JointParser
  {
  public:
    /// \brief default constructor 
    JointParser();

    /// \brief constructor with an xml elment 
    JointParser(tinyxml2::XMLElement* config_);

    /// \brief  copy constructor 
    JointParser(const JointParser& rhs);

    /// \brief  destructor, release memory
    ~JointParser();

    /// \brief parse the joint and fill  variables, false if fail
    bool parse();

    /// \brief export the data to an xml, for writing out 
    bool export2xml(tinyxml2::XMLElement* xml);

  private:
    bool parseJointDynamics(tinyxml2::XMLElement* xml);
    bool parseJointLimits(tinyxml2::XMLElement* xml);
    bool parseJointSafety(tinyxml2::XMLElement* xml);
    bool parseJointCalibration(tinyxml2::XMLElement* xml);
    bool parseJointMimic(tinyxml2::XMLElement* xml);

    bool exportPose(urdf::Pose<T> &pose);
    bool exportJointDynamics(tinyxml2::XMLElement* xml);
    bool exportJointLimits(tinyxml2::XMLElement* xml);
    bool exportJointSafety(tinyxml2::XMLElement* xml);
    bool exportJointCalibration(tinyxml2::XMLElement* xml);
    bool exportJointMimic(tinyxml2::XMLElement* xml);

    tinyxml2::XMLElement*          config;
    urdf::JointDynamics<T>*        jd;
    urdf::JointLimits<T>*          jl;
    urdf::JointSafety<T>*          js;
    urdf::JointCalibration<T>*     jc;
    urdf::JointMimic<T>*           jm;

    std::unique_ptr<urdf::Joint<T>>jt;
  };
}; // namespace tinyurdf
#endif // JOINT_PARSER_HPP