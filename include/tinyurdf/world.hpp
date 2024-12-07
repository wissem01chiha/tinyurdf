#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <tinyxml2/tinyxml2.h>
#include <loguru/loguru.hpp>
#include "model_interface.hpp"
#include "pose.hpp"
#include "twist.hpp"

namespace urdf {

  template<typename T = double >
  struct Entity
  {
    std::shared_ptr<ModelInterface<T>> model;
    Pose<T>     origin;
    Twist<T>    twist;
  };

  template<typename T = double >
  class World
  {
  public:
    /// \brief default constructor 
    World();

    /// \brief construct from xml elment
    World(tinyxml2::XMLElement* xml);

    /// \brief  rest member varibles
    void clear();

    /// \brief world name must be unique
    std::unique_ptr<std::string> name;

    /// \brief world models 
    std::vector<Entity<T>> models;
  };
} // namespace urdf
#endif //  WORLD_HPP