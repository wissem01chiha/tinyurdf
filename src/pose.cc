#include "pose.h"

namespace urdf {

    template <typename T>
    Pose<T>::Pose()
    {
      position = math::Vec3<T>::Zero();
      rotation = math::Rot3<T>::Identity();
    }

    template <typename T>
    Pose<T>::Pose(const Pose<T> &rhs)
    {
      this->position = rhs.position; 
      this->rotation = rhs.rotation;
    }

    template <typename T>
    Pose<T>::Pose(Pose<T> &&rhs) noexcept
    {
      this->position = std::move(rhs.position);
      this->rotation = std::move(rhs.rotation);
    }

    template <typename T>
    Pose<T> &Pose<T>::operator=(const Pose<T> &rhs)
    {
      if (this != &rhs) {
        position = rhs.position;
        rotation = rhs.rotation;
      }
      return *this;
    }

    template <typename T>
    Pose<T> &Pose<T>::operator=(Pose<T> &&rhs) noexcept
    {
      if (this != &rhs) {
        position = std::move(rhs.position);
        rotation = std::move(rhs.rotation);
      }
      return *this;
    }

    template <typename T>
    Pose<T>::Pose(tinyxml2::XMLElement *xml)
    {
      clear();
      if (xml) 
      {
        const char *xyz_str = xml->Attribute("xyz");
        const char *rpy_str = xml->Attribute("rpy");
        if (xyz_str) 
        {
          std::istringstream stream(xyz_str);
          str2vec<T>(stream, position);
        }
        if (rpy_str) 
        {
          std::istringstream stream(rpy_str);
          str2rot<T>(stream, rotation);
        }
      }
    }

  template <typename T>
  void Pose<T>::clear()
  {
    position.setZero();
    rotation = math::Rot3<T>::Identity();
  }

}; // namespace urdf

template class  urdf::Pose<double>;
template class  urdf::Pose<float>;
template class  urdf::Pose<long double>;