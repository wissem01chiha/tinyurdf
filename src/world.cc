#include "world.h"

namespace urdf
{
  template <typename T>
  World<T>::World()
  {
    name = std::make_unique<std::string>();
  }

  template <typename T>
  void World<T>::clear()
  {
    models.clear();
    name = std::string("");
  }

  template <typename T>
  World<T>::World(tinyxml2::XMLElement *xml)
  {
    if(xml == nullptr ){
      LOG_F(ERROR, "Invalid world xml pointer ");
      return;
    }
    const char* name_str = xml->Attribute("name");
    if(name_str == nullptr ){
      LOG_F(ERROR, "unnamed world found ");
      return;
    }else
    {
      name = std::make_unique<std::string>();
      clear();
      this->name = std::string(name_str);
    }
  }

} // namespace urdf