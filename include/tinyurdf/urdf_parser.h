#ifndef URDF_PARSER_H
#define URDF_PARSER_H

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
      URDFParser(const std::string &path);

      /// @brief main parsing function
      /// log the time that we had to spend on parsing the file! 
      void parse();

      /// @brief get a pointer to the parsed model
      /// @note 
      std::shared_ptr<urdf::Model<T>>* getModel();

      /// @brief write the parser log to an external file 
      /// for debug 
      void log(const std::string &path);

    private:
      std::shared_ptr<urdf::Model<T>> model = nullptr;

      std::shared_ptr<urdf::World<T>> world = nullptr;

  };

}; // namespace tinyurdf
#endif // URDF_PARSER_H