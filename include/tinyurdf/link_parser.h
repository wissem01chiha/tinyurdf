#ifndef LINK_PARSER_H
#define LINK_PARSER_H

#include <memory>
#include <string>
#include <vector>
#include <tinyxml2/tinyxml2.h>
#include <loguru/loguru.hpp>
#include "urdf_utilities.h"
#include "pose.h"
#include "link.h"
#include "joint.h"

namespace tinyurdf {

  template< typename T = double >
  class LinkParser
  {
    public:
      /// @brief default constructor 
      LinkParser();

      /// @brief 
      bool parse();

      /// @brief returns a pointer to the parsed `urdf::Link` object.
      /// @return A pointer to the parsed link, or `nullptr` if 
      /// parsing failed.
      urdf::Link<T>* getLink() const;

    private:
      /// @brief parse the link name 
      bool parseName(); 

      /// @brief parse link geomtery
      bool parseGeometry(tinyxml2::XMLElement* xml);

      /// @brief parse link visual 
      bool parseVisual(tinyxml2::XMLElement* xml);

      bool parseInertial(tinyxml2::XMLElement* xml);
      
      bool parseMaterial(tinyxml2::XMLElement* xml);
      
      /// @brief the XML element representing the link configuration.
      tinyxml2::XMLElement*          config;

      /// @brief the parsed link data structure.
      std::unique_ptr<urdf::Link<T>> link;
  };
}; // namespace tinyurdf
#endif // LINK_PARSER_H