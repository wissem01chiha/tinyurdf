#ifndef LINK_PARSER_H
#define LINK_PARSER_H

#include <memory>
#include <string>
#include <vector>
#include <sstream> 
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
      LinkParser(tinyxml2::XMLElement* config_);

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
      /// @code{.xml} <link name="link_1" /> @endcode
      bool parseName(tinyxml2::XMLElement *xml); 

      /// @brief helper function for parsing geomtery
      /// xml elment of link 
      /// @code{.xml} <geometry type = "cylinder" radius="1" length="0.5" /> @endcode
      bool parseGeometry(tinyxml2::XMLElement *xml);

      /// @brief parse the link material, a link material elment is given by
      /// the tag:
      /// ...
      /// @code{.xml}
      /// <material name="Cyan">
      ///    <texture filename ="file_1" />
      ///    <color rgba = "0 1.0 1.0 1.0" />
      ///    <density value = "1.2" />
      /// </material>
      /// ...
      /// @endcode
      /// @todo add support for checking if the texture filenme exsits or not.
      bool parseMaterial(tinyxml2::XMLElement* xml);

      /// @brief parse link visual element
      ///
      /// a link visual tag is given by tag :
      /// @code{.xml}
      /// ...
      /// <visual>
      ///    <origin xyz ="0 0 0" rpy = "0 0 0" />
      ///    <geometry type = "box" size="1 1 1"/>
      ///    <material name="Cyan">
      ///    ....
      ///    </material>
      /// </visual>
      /// ...
      ///@endcode
      bool parseVisual(tinyxml2::XMLElement* xml);

      /// @brief parses the link inertia and fill the mmeber variables
      /// @note this methode do not use inertia safe constructor, so physcial
      /// consistansy will not be checked !
      /// no optional elments in inertia tag.
      /// @code{.xml}
      /// ...
      /// <inertial>
      ///   <origin xyz="0 0 0.5" rpy="0 0 0"/>
      ///   <mass value="5"/>
      ///   <inertia ixx="100"  ixy="0"  ixz="0" iyy="100" iyz="0" izz="100" />
      /// </inertial>
      /// ...
      /// @endcode
      bool parseInertial(tinyxml2::XMLElement* xml);

      /// @brief parse the link collision element
      /// an exemple of collison shape of alink is 
      /// @code{.xml}
      /// ...
      /// <collision>
      ///   <origin xyz="0 0 0" rpy = "0 0 0"/>
      ///   <geometry type = "cylinder" radius="1" length="0.5" />
      /// </collision>
      /// ...
      /// @endcode
      bool parseCollision(tinyxml2::XMLElement* xml);
      
      /// @brief the XML element representing the link configuration.
      tinyxml2::XMLElement*          config = nullptr;

      /// @brief the parsed link data structure.
      std::unique_ptr<urdf::Link<T>> link = nullptr;
  };
}; // namespace tinyurdf
#endif // LINK_PARSER_H