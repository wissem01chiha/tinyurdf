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
      /// @brief default constructor.
      JointParser();

      /// @brief constructor with an XML element.
      /// @param config_ a pointer to the XML element representing the joint.
      JointParser(tinyxml2::XMLElement* config_);

      /// @brief copy constructor.
      /// @param rhs The `JointParser` instance to copy.
      JointParser(const JointParser& rhs);

      /// @brief parses the joint and fills member variables.
      /// @return `true` if parsing is successful, `false` otherwise.
      /// @note the fuction exsit at the first parsing error, default 
      /// values settigns are only suported for joint limts
      /// @todo extend default vars assign when xml childs are missings 
      bool parse();

      /// @brief returns a pointer to the parsed `urdf::Joint` object.
      /// @return A pointer to the parsed joint, or `nullptr` if parsing failed.
      urdf::Joint<T>* getJoint() const;

  private:
      /// @brief parses the dynamics section of the joint.
      bool parseDynamics(tinyxml2::XMLElement* xml);

      /// @brief parses the limits section of the joint.
      bool parseLimits(tinyxml2::XMLElement* xml);

      /// @brief parses the safety section of the joint.
      bool parseSafety(tinyxml2::XMLElement* xml);

      /// @brief parses the calibration section of the joint.
      bool parseCalibration(tinyxml2::XMLElement* xml);

      /// @brief parses the mimic section of the joint.
      bool parseMimic(tinyxml2::XMLElement* xml);

      /// @brief parses the type of the joint.
      bool parseType(tinyxml2::XMLElement* xml);

      /// @brief parses the name of the joint.
      bool parseName(tinyxml2::XMLElement* xml);

      /// @brief parses the parent and child tags in the joint.
      bool parseParentChildLinks();

      /// @brief iterates over the joint origin tags.
      /// fills `joint->parents_to_joint_origin_transform`.
      /// checks that parent names match `joint->parent_links_name` and
      /// `joint->child_links_name`.
      /// if an unrecognized parent or element is found, abort with an error.
      bool parseOrigins();

      /// @brief parses the joint axis.
      /// Fills `joint->axis` attribute.
      bool parseAxis(tinyxml2::XMLElement* xml);

      /// @brief the XML element representing the joint configuration.
      tinyxml2::XMLElement* config;

      /// @brief the parsed joint data structure.
      std::unique_ptr<urdf::Joint<T>> joint = nullptr;
    };
}; // namespace urdf 
#endif // JOINT_PARSER_H