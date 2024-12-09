#ifndef POSE_H
#define POSE_H

#include <string>
#include <sstream> 
#include <tinyxml2/tinyxml2.h>
#include <loguru/loguru.hpp>
#include "urdf_utilities.h"

namespace urdf {

  template<typename T = double >
  class Pose
  {
  public:
    /// \brief default constructor
    Pose();

    /// \brief  copy constructor
    Pose(const Pose<T>& rhs);

    /// \brief  move constructor
    Pose(Pose<T>&& rhs) noexcept;

    /// \brief  copy assignment operator
    Pose<T>& operator=(const Pose<T>& rhs);

    /// \brief  move assignment operator
    Pose<T>& operator=(Pose<T>&& rhs) noexcept;

    /// \brief Construtor from an XML elment type 
    /// \example <origin xyz="0 1 0" rpy="0 0 0"/>
    Pose(tinyxml2::XMLElement* xml);

    /// \brief default destrcutor 
    ~Pose(){};

    /// \brief export a Pose object into an XML based
    /// @warning the rotation is exported as quertion 4 elms rep
    /// not rpy fixe that or make maroc define alterntives !!!
    bool export2xml(tinyxml2::XMLElement* xml);

    /// \brief rest memeber varaibles 
    void clear();

    math::Vec3<T>  position;
    math::Rot3<T>  rotation;
  };
}; //namespace urdf 
#endif // POSE_H
