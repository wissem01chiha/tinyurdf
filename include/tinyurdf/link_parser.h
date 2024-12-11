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

      /// @brief default constructor 
      LinkParser(const tinyxml2::XMLElement* config_);

      /// @brief parse the joint and fill the memeber vars
      /// @return 'true' if sucessfull , 'false' otherwise
      /// @note stops at the first error
      bool parse();

      /// @brief returns a pointer to the parsed `urdf::Link` object.
      /// @return A pointer to the parsed link, or `nullptr` if 
      /// parsing failed.
      urdf::Link<T>* getLink() const;

    private:
      /// @brief parse the link name 
      bool parseName(tinyxml2::XMLElement *xml); 

      ///@brief parse the link material 
      bool parseMaterial(tinyxml2::XMLElement* xml);

      /// @brief parse link geomtery
      /// a link geomtry definition is given strictly by the
      /// tag format :
      /// @code{.xml}
      /// <geometry type ="box" size="1 1 1" />
      /// @endcode
      /// in typical urdf file we found 
      /// @code{.xml}
      /// <geometry>
      ///      <box size="1 1 1" />
      /// </geometry>
      ///@endcode
      bool parseGeometry(tinyxml2::XMLElement* xml);

      /// @brief parse link visual 
      /// a link visual tag is given by tag :
      /// @code{.xml}
      /// <visual>
      ///    <origin xyz="0 0 0" rpy="0 0 0" />
      ///     <geometry>
      ///      <box size="1 1 1" />
      ///   </geometry>
      ///    <material name="Cyan">
      ///      <color rgba="0 1.0 1.0 1.0"/>
      ///    </material>
      /// </visual>
      ///@endcode
      bool parseVisual(tinyxml2::XMLElement* xml);

      /// @brief parses the link inertia and fill the mmeber variables
      /// @note use inertia safe constructor !
      bool parseInertial(tinyxml2::XMLElement* xml);
      
      /// @brief the XML element representing the link configuration.
      tinyxml2::XMLElement*          config = nullptr;

      /// @brief the parsed link data structure.
      std::unique_ptr<urdf::Link<T>> link;
  };
}; // namespace tinyurdf
#endif // LINK_PARSER_H