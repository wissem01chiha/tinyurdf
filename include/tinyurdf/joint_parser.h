#ifndef JOINT_PARSER_H
#define JOINT_PARSER_H

#include <memory>
#include <string>
#include <vector>
#include <tinyxml2/tinyxml2.h>
#include <loguru/loguru.hpp>
#include "urdf_utilities.h"
#include "pose.h"
#include "joint.h"

namespace tinyurdf {

  template <typename T = double >
  class JointParser
  {
  public:
      /// @brief Default constructor.
      JointParser();

      /// @brief Constructor with an XML element.
      /// @param config_ A pointer to the XML element representing the joint.
      JointParser(tinyxml2::XMLElement* config_);

      /// @brief Copy constructor.
      /// @param rhs The `JointParser` instance to copy.
      JointParser(const JointParser& rhs);

      /// @brief Parses the joint and fills member variables.
      /// @return `true` if parsing is successful, `false` otherwise.
      bool parse();

      /// @brief Returns a pointer to the parsed `urdf::Joint` object.
      /// @return A pointer to the parsed joint, or `nullptr` if parsing failed.
      urdf::Joint<T>* getJoint() const;

  private:
      /// @brief Parses the dynamics section of the joint.
      bool parseDynamics(tinyxml2::XMLElement* xml);

      /// @brief Parses the limits section of the joint.
      bool parseLimits(tinyxml2::XMLElement* xml);

      /// @brief Parses the safety section of the joint.
      bool parseSafety(tinyxml2::XMLElement* xml);

      /// @brief Parses the calibration section of the joint.
      bool parseCalibration(tinyxml2::XMLElement* xml);

      /// @brief Parses the mimic section of the joint.
      bool parseMimic(tinyxml2::XMLElement* xml);

      /// @brief Parses the type of the joint.
      bool parseType(tinyxml2::XMLElement* xml);

      /// @brief Parses the name of the joint.
      bool parseName(tinyxml2::XMLElement* xml);

      /// @brief Parses the parent and child tags in the joint.
      bool parseParentChildLinks();

      /// @brief Iterates over the joint origin tags.
      /// Fills `joint->parents_to_joint_origin_transform`.
      /// Checks that parent names match `joint->parent_links_name` and
      /// `joint->child_links_name`.
      /// If an unrecognized parent or element is found, abort with an error.
      bool parseOrigins();

      /// @brief Parses the joint axis.
      /// Fills `joint->axis` attribute.
      bool parseAxis(tinyxml2::XMLElement* xml);

      /// @brief The XML element representing the joint configuration.
      tinyxml2::XMLElement* config;

      /// @brief The parsed joint data structure.
      std::unique_ptr<urdf::Joint<T>> joint;
    };
}; // namespace urdf 
#endif // JOINT_PARSER_H