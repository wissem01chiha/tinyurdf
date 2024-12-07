#ifndef URDF_PARSER_UTIL_HPP
#define URDF_PARSER_UTIL_HPP

#include <stdexcept>
#include <tinyxml2/tinyxml2.h>
#include <loguru/loguru.hpp>
#include "urdf_version.hpp"
#include "pose.hpp"
#include "joint.hpp"

namespace tinyurdf {

  template<typename T>
  bool parsePoseInternal(urdf::Pose<T> &pose, tinyxml2::XMLElement * xml)
  {
    pose.clear();
    if (xml){
      try {
        pose = urdf::Pose<T>(xml);
      }
      catch (const std::exception &e) {
        LOG_F(ERROR, e.what());
      return false;
      }
      return true;
  }};

}; // namespace tinyurdf
#endif // URDF_PARSER_UTIL_HPP