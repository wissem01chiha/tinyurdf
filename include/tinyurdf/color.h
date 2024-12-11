#ifndef COLOR_H
#define COLOR_H

#include <sstream>  
#include <string>
#include <vector>
#include <loguru/loguru.hpp>

namespace urdf {

  template<typename T =  double >
  class Color
  {
  public:

    enum class Type
    {
      Red,
      Green,
      Blue,
      Black,
      White,
      Yellow,
      Cyan,
      Magenta
    };

    T r, g, b, a;

    /// \brief default constructor 
    Color();

    /// \brief safe constructor 
    Color(const T& r_,const  T& g_,const  T& b_,const T& a_);

    /// \brief constructor from string input 
    Color(const std::string &vector_str);

    /// @brief constructor from Color::Type object
    Color(const Type type_);

    /// \brief convert a Color object value into a string, space-separated.
    static std::string str();

    /// \brief reset memeber variables 
    void clear();
  
  };
}; // namesapce urdf 
#endif // COLOR_H