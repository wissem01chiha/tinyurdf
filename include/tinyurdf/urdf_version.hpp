#ifndef  URDF_VERSION_HPP
#define  URDF_VERSION_HPP

#include <string>
#include <vector>
#include <type_traits>
#include <stdexcept>
#include <loguru/loguru.hpp>

namespace urdf {
      
  template<typename T = double >
  class URDFVersion final
  {
  public:
    /// \brief default constructor 
    URDFVersion(const char *attr);

    /// \brief move constructor
    URDFVersion(const URDFVersion& rhs);

    /// \brief destructor 
    ~URDFVersion();

    bool equal(T maj, T min);
    T getMajor() const;
    T getMinor() const;

  private:
    T strToUnsigned(const char *str);
    T major_;
    T minor_;
  };

}; // namespace urdf
#endif // URDF_VERSION_HPP