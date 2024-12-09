#include "urdf_version.h"

namespace urdf {

  template <typename T>
  URDFVersion<T>::URDFVersion(const char *attr)
  {
      static_assert(std::is_integral<T>::value, "Template parameter T must be an integral type");
      // If the passed in attribute is NULL, it means it wasn't specified in the
      // XML, so we just assume version 1.0.
      if (attr == nullptr)
      {
        major_ = 1;
        minor_ = 0;
        return;
      }
      // We only accept version strings of the type <major>.<minor>
      // make it accept <major>, <minor> or <major> <minor> spaced 
      std::vector<std::string> split;
      urdf::split_string(split, std::string(attr), ".");
      if (split.size() == 2)
      {
        major_ = strToUnsigned(split[0].c_str());
        minor_ = strToUnsigned(split[1].c_str());
      }
      else
      {
        throw std::runtime_error("The version attribute should be in the form 'x.y'");
      }
      split.clear();
      split.shrink_to_fit();
  }
  template <typename T>
  URDFVersion<T>::URDFVersion(const URDFVersion &rhs)
  {
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
        // This would get caught below, but we can make a nicer error message
        throw std::runtime_error("One of the fields of the version attribute is blank");
      }
      char *end = const_cast<char *>(str);
      T value = strtol(str, &end, 10);

      if (end == str)
      {
        // If the pointer didn't move at all, then we couldn't convert any of
        // the string to an integer.
        throw std::runtime_error("Version attribute is not an integer");
      }
      if (*end != '\0')
      {
        // Here, we didn't go all the way to the end of the string, which
        // means there was junk at the end
        throw std::runtime_error("Extra characters after the version number");
      }
      if (value < 0)
      {
        throw std::runtime_error("Version number must be positive");
      }

      return value;
    }
  }
}; // namespace urdf
