#include "world.hpp"

namespace urdf
{
  template <typename T>
  World<T>::World()
  {

  }

  template <typename T>
  void World<T>::clear()
  {
  }

  template <typename T>
  World<T>::World(tinyxml2::XMLElement *xml)
  {
    tinyxml2::XMLElement * world_xml = xml->GetDocument()->NewElement("world");
    world_xml->SetAttribute("name", world.name.c_str());
    // to be implemented
    // exportModels(*world.models, world_xml);
    xml->LinkEndChild(world_xml);
  }

} // namespace urdf
