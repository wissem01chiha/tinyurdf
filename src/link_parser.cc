#include "link_parser.h"

namespace tinyurdf 
{
    template <typename T>
    LinkParser<T>::LinkParser()
    {
      link = std::make_unique<urdf::Link<T>>();
    }

    template <typename T>
    LinkParser<T>::LinkParser(const tinyxml2::XMLElement *config_)
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
      return link.get;
    }

    template <typename T>
    bool LinkParser<T>::parseName(tinyxml2::XMLElement *xml)
    {
      const char *name = xml->Attribute("name");
      if(name == nullptr){
        LOG_F(EROOR, "unnamed link found !");
        return false;
      }
      link->name  = std::string(name);
      return true;
    }

    template <typename T>
    bool LinkParser<T>::parseGeometry(tinyxml2::XMLElement *xml)
    {
      if(xml == nullptr ){
        LOG_F(ERROR, " Link Parser : link (%s) has no geometry elment", link->name.c_str());
        return false;
      }
      const char* type_str = xml->Attribute("type");
      if(type_str == nullptr ){

        LOG_F(ERROR, "Link Parser : link (%s) has no geometry type.", link->name.c_str());
        return false;
      }else
      {
        if (type_str == "box")
        {
          const char* size_str = xml->Attribute("size");
          if(size_str==nullptr){

            LOG_F(ERROR, "link parser : geometry box has no size attribute");
            return false;
          }
        }
        
      }
      
      return true;
    }

    template <typename T>
    bool LinkParser<T>::parseVisual(tinyxml2::XMLElement *xml)
    {
      if(xml == nullptr ){
        LOG_F(ERROR, " Link Parser : link (%s) has no visual elment", link->name.c_str());
        return false;
      }
      return false;
    }

    template <typename T>
    bool LinkParser<T>::parseInertial(tinyxml2::XMLElement *xml)
    {
        return false;
    }

    template <typename T>
    bool LinkParser<T>::parseMaterial(tinyxml2::XMLElement *xml)
    {
        return false;
    }

    template <typename T>
    bool LinkParser<T>::parse()
    {
        return false;
    }
};// namespace tinyurdf 

template class tinyurdf::LinkParser<double>;
template class tinyurdf::LinkParser<float>;
template class tinyurdf::LinkParser<long double>;
