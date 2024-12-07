#ifndef COLOR_HPP
#define COLOR_HPP

#include <sstream>  
#include <string>
#include <vector>
#include <loguru/loguru.hpp>

namespace urdf {

  template<typename T =  double >
  class Color
  {
  public:
    /// \brief default constructor 
    Color();

    /// \brief safe constructor 
    Color(const T& r_,const  T& g_,const  T& b_,const T& a_);

    /// \brief constructor from string input 
    Color(const std::string &vector_str);

    /// \brief convert a Color object value into a string, space-separated.
    static std::string str();

    /// \brief reset memeber variables 
    void clear();
    
    T r, g, b, a;
  };
}; // namesapce urdf 
#endif // COLOR_HPP