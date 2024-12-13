#include "link_parser.h"

namespace tinyurdf 
{
    template <typename T>
    LinkParser<T>::LinkParser()
    {
      link = std::make_unique<urdf::Link<T>>();
    }
 
    template <typename T>
    LinkParser<T>::LinkParser(tinyxml2::XMLElement *config_)
    {
      if(config_ == nullptr){
        LOG_F(ERROR, "Invalid Initilisation : pointer null");
      }
      config = config_;
      link = std::make_unique<urdf::Link<T>>();
    }

    template <typename T>
    urdf::Link<T> *LinkParser<T>::getLink() const
    {
      return link.get();
    }

    template <typename T>
    bool LinkParser<T>::parseName(tinyxml2::XMLElement *xml)
    {
      const char *name = xml->Attribute("name");
      if(name == nullptr){
        LOG_F(ERROR, "unnamed link found !");
        return false;
      }
      link->name  = std::string(name);
      return true;
    }

  template <typename T>
  bool LinkParser<T>::parseGeometry(tinyxml2::XMLElement *xml, urdf::Geometry<T>& geometry)
  {
    if (xml == nullptr) 
    {
      LOG_F(ERROR, "Link Parser: link (%s) visual geometry not found", link->name.c_str());
      return false;
    } else 
    {
      const char* type_str = xml->Attribute("type");
      if (type_str == nullptr) 
      {
        LOG_F(ERROR, "Link Parser: link (%s) has no geometry type.", link->name.c_str());
        return false;
      }

      if (std::strcmp(type_str, "box") == 0 || std::strcmp(type_str, "Box") == 0) 
      {
        urdf::Box<T> box;
        const char* size_str = xml->Attribute("size");
        if (size_str == nullptr) {
            LOG_F(ERROR, "Link parser: link (%s) geometry box has no size", link->name.c_str());
            return false;
        } else {
            std::istringstream stream(size_str);
            str2vec<T>(stream, box.dim);
        }
        geometry = box; 

      } else if (std::strcmp(type_str, "cylinder") == 0 || std::strcmp(type_str, "Cylinder") == 0) 
      {
        urdf::Cylinder<T> cylinder;
        const char* length_str = xml->Attribute("length");
        const char* radius_str = xml->Attribute("radius");
        if (length_str == nullptr || radius_str == nullptr) {
            LOG_F(ERROR, "Link Parser: link (%s) has missing geometry vars", link->name.c_str());
            return false;
        } else {
            str2num<T>(length_str, cylinder.length);
            str2num<T>(radius_str, cylinder.radius);
        }
        geometry = cylinder; 

      } else if (std::strcmp(type_str, "sphere") == 0 || std::strcmp(type_str, "Sphere") == 0) 
      {
        urdf::Sphere<T> sphere;
        const char* radius_str = xml->Attribute("radius");
        if (radius_str == nullptr) {
            LOG_F(ERROR, "Link Parser: link (%s) has missing geometry vars", link->name.c_str());
            return false;
        } else {
            str2num<T>(radius_str, sphere.radius);
        }
        geometry = sphere; 

      } else if (std::strcmp(type_str, "mesh") == 0 || std::strcmp(type_str, "Mesh") == 0)
      {
        urdf::Mesh<T> mesh;
        const char* mesh_str = xml->Attribute("filename");
        if (mesh_str == nullptr) {
            LOG_F(ERROR, "Link Parser: link (%s) missing mesh file", link->name.c_str());
            return false;
        } else {
          mesh.texture_filename = std::string(mesh_str);
        }
        const char* scale_str = xml->Attribute("scale");
        if (scale_str == nullptr) {
          LOG_F(WARNING, "Mesh scale in link (%s) not found, using default 1 1 1", link->name.c_str());
        } else {
          std::istringstream stream(scale_str);
          str2vec<T>(stream, mesh.scale); 
        }
        geometry = mesh; 

      }else {
        LOG_F(ERROR, "Link Parser: link (%s) has unknown geometry type", link->name.c_str());
        return false;
      }
    }
    return true;
  }

    template <typename T>
    bool LinkParser<T>::parseMaterial(tinyxml2::XMLElement *xml)
    {
      if(xml==nullptr){
        LOG_F(ERROR, "Link Parser : link (%s) has no assign material", link->name.c_str());
        return false;
      }else
      {
        link->material = std::make_shared<urdf::Material<T>>();
        link->visual->material = std::make_shared<urdf::Material<T>>();
        
        link->material->clear();
        link->visual->material->clear();

        const char* name_str = xml->Attribute("name");
        if(name_str == nullptr){

          LOG_F(ERROR, "Link Parser link (%s) has unammed material ", link->name.c_str());
          return false;
        }else
        {
          link->material->name = std::string(name_str);
          link->visual->material_name =  std::string(name_str);
        }
        tinyxml2::XMLElement* texture_filename_xml = xml->FirstChildElement("texture");
        const char* filename_str = texture_filename_xml->Attribute("filename");
        if (filename_str==nullptr)
        {
          LOG_F(INFO, "link (%s) material has no texture filename", link->name.c_str());
        }else
        {
          link->material->texture_filename = std::string(filename_str);
          link->visual->material->texture_filename = std::string(filename_str);
        }
        tinyxml2::XMLElement* color_xml = xml->FirstChildElement("color");
        if(color_xml==nullptr){

          LOG_F(WARNING, "link (%s) material has no color, using default", link->name.c_str());
        }else
        {
          std::string color_string_vector = std::string(color_xml->Attribute("rgba"));
          link->material->color = urdf::Color<T>(color_string_vector);
          link->visual->material->color = urdf::Color<T>(color_string_vector);
        }
        tinyxml2::XMLElement* density_xml = xml->FirstChildElement("density");
        if(density_xml==nullptr){

          LOG_F(ERROR, "link (%s) material has no density ", link->name.c_str());
          return false;
        }else
        {
          const char* density_str = density_xml->Attribute("value");
          str2num<T>(density_str, link->material->density);
          str2num<T>(density_str, link->visual->material->density);
        }
        return true;
      }
    }

    template <typename T>
    bool LinkParser<T>::parseVisual(tinyxml2::XMLElement *xml)
    {
      if(xml == nullptr ){
        LOG_F(ERROR, " Link Parser : link (%s) has no visual elment", link->name.c_str());
        return false;
      }
      link->visual = std::make_shared<urdf::Visual<T>>();
      link->visual->clear();

      tinyxml2::XMLElement *geometry_xml = xml->FirstChildElement("geometry");

      link->visual->geometry = std::make_shared<urdf::Geometry<T>>();
      if(!parseGeometry(geometry_xml,*link->visual->geometry)){
        return false;
      }else
      {
        tinyxml2::XMLElement *origin_xml = xml->FirstChildElement("origin");
        if(origin_xml ==nullptr){

          LOG_F(ERROR, "Link Parser : link (%s) visual origin not found", link->name.c_str());
          return false;
        }else
        {
          link->visual->origin = urdf::Pose<T>(origin_xml);
        }
        tinyxml2::XMLElement *material_xml = xml->FirstChildElement("material");
        if (material_xml==nullptr)
        {
          LOG_F(WARNING, "Link Parser : Link (%s) has no material, use default", link->name.c_str());
        }else
        {
          return parseMaterial(material_xml);
        }
      }
      return true;
    }

    template <typename T>
    bool LinkParser<T>::parseInertial(tinyxml2::XMLElement *xml)
    {
      if(xml== nullptr){

        LOG_F(ERROR, "Link Parser : link (%s) has no inertia", link->name.c_str());
        return false;
      }else
      {
        link-> inertial = std::make_shared<urdf::Inertial<T>>();
        link->inertial->clear();
        tinyxml2::XMLElement *origin_xml = xml->FirstChildElement("origin");
        if (origin_xml ==nullptr)
        {
          LOG_F(ERROR, "Link Parser : link (%s) has no inertia origin ", link->name.c_str());
          return false;
        }else
        {
          link->inertial->origin = urdf::Pose<T>(origin_xml);
        }
        tinyxml2::XMLElement *mass_xml = xml->FirstChildElement("mass");
        if (mass_xml ==nullptr)
        {
          LOG_F(ERROR, "Link Parser : link (%s) has no inertia mass ", link->name.c_str());
          return false;
        }else
        {
          const char* mass_str = mass_xml->Attribute("value");
          str2num<T>(mass_str, link->inertial->mass);
        }
        tinyxml2::XMLElement *inertia_xml = xml->FirstChildElement("inertia");
        if (inertia_xml ==nullptr)
        {
          LOG_F(ERROR, "Link Parser : link (%s) has no inertia tensor", link->name.c_str());
          return false;
        }else
        {
         const char* ixx_str = inertia_xml->Attribute("ixx");
         const char* ixy_str = inertia_xml->Attribute("ixy");
         const char* ixz_str = inertia_xml->Attribute("ixz");
         const char* iyy_str = inertia_xml->Attribute("iyy");
         const char* iyz_str = inertia_xml->Attribute("iyz");
         const char* izz_str = inertia_xml->Attribute("izz");
         if(ixx_str== nullptr || ixy_str== nullptr || ixz_str ==nullptr || iyy_str == nullptr || 
         iyz_str == nullptr || izz_str ==nullptr){
          LOG_F(ERROR, "Link Parser : link (%s) inertia has missing values", link->name.c_str());
          return false;
         }
         T ixx, ixy , ixz, iyy, iyz, izz;
         str2num<T>(ixx_str, ixx);
         str2num<T>(ixy_str, ixy);
         str2num<T>(ixz_str, ixz);
         str2num<T>(iyy_str, iyy);
         str2num<T>(iyz_str, iyz);
         str2num<T>(izz_str, izz);
         link->inertial->ixx = ixx;
         link->inertial->ixy = ixy;
         link->inertial->ixz = ixz;
         link->inertial->iyy = iyy;
         link->inertial->iyz = iyz;
         link->inertial->izz = izz;
        }
      }
      return true;
    }

    template <typename T>
    bool LinkParser<T>::parseCollision(tinyxml2::XMLElement *xml)
    {
      if(xml == nullptr ){
        LOG_F(ERROR, " Link Parser : link (%s) has no collision elment", link->name.c_str());
        return false;
      }
      link->collision = std::make_shared<urdf::Collision<T>>();
      link->collision->clear();

      tinyxml2::XMLElement *origin_xml = xml->FirstChildElement("origin");
      if(origin_xml ==nullptr)
      {
        LOG_F(ERROR, "Link Parser : link (%s) collison origin not found", link->name.c_str());
        return false;
      }else
      {
        link->collision->origin = urdf::Pose<T>(origin_xml);
      }
      tinyxml2::XMLElement *geomtry_xml = xml->FirstChildElement("geometry");
      if (!parseGeometry(geomtry_xml, *link->visual->geometry))
      {
        return false;
      }
      return true;
    }

    template <typename T>
    bool LinkParser<T>::parse()
    {
      if(this->link == nullptr) 
      { 
        LOG_F(ERROR, "Link Parser Point to non valid link class object");
        return false;
      }
      else
      {
        this->link->clear();
      }
      if (!parseName(config))
      {
        return false;
      } 
      tinyxml2::XMLElement *xml_inertial = config->FirstChildElement("inertial");
      if (!parseInertial(xml_inertial))
      {
        return false;
      }
      tinyxml2::XMLElement *xml_visual = config->FirstChildElement("visual");
      if (!parseVisual(xml_visual))
      {
        return false;
      }
      tinyxml2::XMLElement *xml_collision = config->FirstChildElement("collision");
      if(!parseCollision(xml_collision)){
        return false;
      }
        return true;
      }
};// namespace tinyurdf 

template class tinyurdf::LinkParser<double>;
template class tinyurdf::LinkParser<float>;
template class tinyurdf::LinkParser<long double>;
