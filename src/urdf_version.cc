#include "urdf_version.h"

namespace urdf {

  template <typename T>
  URDFVersion<T>::URDFVersion(const char *attr)
  {
      if (attr == nullptr)
      {
        major_ = static_cast<T>(1);
        minor_ = static_cast<T>(0);
        return;
      }
      std::vector<std::string> split_vector;
      std::string delimiter = ".";
      urdf::split(std::string(attr), split_vector, delimiter );
      if (split_vector.size() == 2)
      {
        major_ = strToUnsigned(split_vector[0].c_str());
        minor_ = strToUnsigned(split_vector[1].c_str());
      }
      else
      {
        LOG_F(ERROR,"The version attribute should be in the form 'x.y'");
        LOG_F(WARNING, "defaulting to version '1.0' ");
        major_ = static_cast<T>(1);
        minor_ = static_cast<T>(0);
        return;
      }
      split_vector.clear();
      split_vector.shrink_to_fit();
  }

  template <typename T>
  URDFVersion<T>::URDFVersion(const URDFVersion<T> &rhs)
  {
    this->minor_ = rhs.minor_;
    this->major_ = rhs.major_;
  }

  template <typename T>
  URDFVersion<T>::~URDFVersion()
  {
  }

  template <typename T>
  bool URDFVersion<T>::equal(T maj, T min)
  {
    return this->major_ == maj && this->minor_ == min;
  }

  template <typename T>
  T URDFVersion<T>::getMajor() const
  {
    return major_;
  }

  template <typename T>
  T URDFVersion<T>::getMinor() const
  {
    return minor_;
  }

  template <typename T>
  T URDFVersion<T>::strToUnsigned(const char *str)
  {
      {
      if (str[0] == '\0')
      {
        LOG_F(ERROR,"One of the fields of the version attribute is blank");
      }
      char *end = const_cast<char *>(str);
      T value = strtol(str, &end, 10);

      if (end == str)
      {
        LOG_F(ERROR,"Version attribute is not an integer");
      }
      if (*end != '\0')
      {
        LOG_F(ERROR,"Extra characters after the version number");
      }
      if (value < 0)
      {
        LOG_F(ERROR,"Version number must be positive");
      }
      return value;
    }
  }
}; // namespace urdf

template class urdf::URDFVersion<double>;
template class urdf::URDFVersion<float>;
template class urdf::URDFVersion<long double>;
