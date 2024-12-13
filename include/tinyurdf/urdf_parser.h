#ifndef URDF_PARSER_H
#define URDF_PARSER_H

#include <filesystem>
#include <fstream>

#include <loguru/loguru.hpp>
#include <tinyxml2/tinyxml2.h>
#include <args/args.hxx>

#include "urdf_version.h"
#include "link_parser.h"
#include "joint_parser.h"
#include "world_parser.h"
#include "sensor_parser.h"
#include "world_parser.h"

namespace tinyurdf {

  template<typename T = double >
  class URDFParser
  {
    public:
      /// @brief default construtor 
      URDFParser();

      /// @brief init with a file path 
      URDFParser(const std::string &path_);

      /// @brief main parsing function
      void parse();

      /// @brief get a pointer to the parsed model
      /// @note 
      std::shared_ptr<urdf::Model<T>>* getModel();

      /// @brief write the parser log to an external file 
      /// for debug 
      void log(const std::string &path);

    private:
      /// @brief parse the xml file version
      /// if not found or the version is below a specif one, return an error 
      /// stop the engine only XML 1.0 is supported !
      bool parseVersion();

      std::shared_ptr<urdf::Model<T>> model = nullptr;

      std::shared_ptr<urdf::World<T>> world = nullptr;

      tinyxml2::XMLDocument           doc;
      urdf::URDFVersion               version;
  };
}; // namespace tinyurdf
#endif // URDF_PARSER_H