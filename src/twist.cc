#include "twist.h"

namespace urdf
{
    template <typename T>
    Twist<T>::Twist()
    {
    }

  template <typename T>
  Twist<T>::Twist(tinyxml2::XMLElement *config)
  {
    this->clear();
    if (xml)
    {
      const char* linear_char = xml->Attribute("linear");
      if (linear_char != NULL)
      {
        try {
          twist.linear.init(linear_char);
        }
        catch (ParseError &e) {
          twist.linear.clear();
          LOG_F(ERROR, "Malformed linear string [%s]: %s", linear_char, e.what());
        }
      }

      const char* angular_char = xml->Attribute("angular");
      if (angular_char != NULL)
      {
        try {
          twist.angular.init(angular_char);
        }
        catch (ParseError &e) {
          twist.angular.clear();
          LOG_F(ERROR, "Malformed angular [%s]: %s", angular_char, e.what());
        }
      }
    }
  }

  template <typename T>
  void Twist<T>::clear()
  {
    this->linear.clear();
    this->angular.clear();
  };

}; // namespace urdf

template class urdf::Twist<double>;
template class urdf::Twist<float>;
template class urdf::Twist<long double>;

