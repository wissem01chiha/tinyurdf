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

namespace tinyurdf {

  template< typename T = double >
  class LinkParser
  {
    public:
      LinkParser();

      bool parse();

      /// @brief Returns a pointer to the parsed `urdf::Link` object.
      /// @return A pointer to the parsed link, or `nullptr` if parsing failed.
      urdf::Link<T>* getLink() const;

    private:
      /// @brief The XML element representing the link configuration.
      tinyxml2::XMLElement*          config;

      /// @brief The parsed link data structure.
      std::unique_ptr<urdf::Link<T>> link;
  };

}; // namespace tinyurdf 
#endif // LINK_PARSER_H







/**
 * <link name="my_link">
   2    <inertial>
   3      <origin xyz="0 0 0.5" rpy="0 0 0"/>
   4      <mass value="1"/>
   5      <inertia ixx="100"  ixy="0"  ixz="0" iyy="100" iyz="0" izz="100" />
   6    </inertial>
   7 
   8    <visual>
   9      <origin xyz="0 0 0" rpy="0 0 0" />
  10      <geometry>
  11        <box size="1 1 1" />
  12      </geometry>
  13      <material name="Cyan">
  14        <color rgba="0 1.0 1.0 1.0"/>
  15      </material>
  16    </visual>
  17 
  18    <collision>
  19      <origin xyz="0 0 0" rpy="0 0 0"/>
  20      <geometry>
  21        <cylinder radius="1" length="0.5"/>
  22      </geometry>
  23    </collision>
  24  </link>
 */

 /**
  * <material name="Cyan">
          <color rgba="0 1.0 1.0 1.0"/>
          <texture filename="textures/robot_texture.png"/>
          <density value = "1.2">
    </material>
  */

 /**
  * Material(tinyxml2::XMLElement* xml){
        name = std::string(xml->Attribute("name"));
        tinyxml2::XMLElement* colorElement = xml->FirstChildElement("color");
        const char* str_vector = colorElement->Attribute("rgba");
        std::string string_vector(str_vector);
        color = Color<T>(string_vector);

        tinyxml2::XMLElement* textureElement = xml->FirstChildElement("texture");
        texture_filename = std::string(textureElement->Attribute("filename"));

        tinyxml2::XMLElement* densityElement = xml->FirstChildElement("density");
        const char* density_str = densityElement->Attribute("value");
        if(density_str) { str2num<T>(density_str, density);}
    };
  */

 /*
 Mesh(tinyxml2::XMLElement* xml){
        texture_filename = std::string(xml->Attribute("filename"));
        const char* scale_str = xml->Attribute("scale");
        str2vec<T>(scale_str, scale);
      };*/
      /*Cylinder(tinyxml2::XMLElement* xml){
        const char* radius_str = xml->Attribute("radius");
        const char* length_str = xml->Attribute("length");
        str2num<T>(radius_str, radius);
        str2num<T>(length_str, length);
      };*/
      /*Box(tinyxml2::XMLElement* xml){
        const char* dim_str = xml->Attribute("size");
        str2vec<T>(dim_str, dim);
      };*/

      /*Sphere(tinyxml2::XMLElement* xml){
        const char* radius_str = xml->Attribute("radius");
        str2num<T>(radius_str, radius);
    };*/