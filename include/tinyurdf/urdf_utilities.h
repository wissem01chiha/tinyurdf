#ifndef URDF_UTILITIES_H
#define URDF_UTILITIES_H

#include <sstream>  
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <Eigen/Dense>
#include <loguru/loguru.hpp>

namespace math
{
    template<typename T = double >
    using Vec3 = Eigen::Matrix<T, 3, 1>;

    template <typename T = double >
    using Rot3 = Eigen::Quaternion<T>;

}; // namespace math

/**
 * @brief constructs a Vec3 object from a space-separated string.
 * Parses a string representation of a 3D vector in the format "x y z" and
 * initializes a `math::Vec3<T>` object. If a conversion error occurs, an
 * error flag is set on the stream. 
 */
template <typename T>
void str2vec(std::istringstream& stream, math::Vec3<T>& v){

  T val;
  std::vector<T> values;

  while (stream >> val) {
      values.push_back(val);
  }
  if (values.size() != 3) {
    LOG_F(ERROR, "string contains %i elements instead of 3 elements", 
                (int)values.size());
    return;
  }
  v << values[0], values[1], values[2];
};

/**
 * @brief constructs a Rot3 object from a space-separated string.
 * Parses a string representation of a rotation and initializes a `math::Rot3<T>` 
 * object.
 */
template <typename T>
void str2rot(std::istringstream& stream, math::Rot3<T>& q) {

    T val;
    std::vector<T> values;
    while (stream >> val) {
        values.push_back(val);
    }
    if (values.size() == 4) {
        q = Eigen::Quaternion<T>(values[3], values[0], values[1], values[2]);
    } 
    else if (values.size() == 3) {
        q = Eigen::Quaternion<T>(
            Eigen::AngleAxis<T>(values[2], Eigen::Matrix<T, 3, 1>::UnitZ()) *
            Eigen::AngleAxis<T>(values[1], Eigen::Matrix<T, 3, 1>::UnitY()) *
            Eigen::AngleAxis<T>(values[0], Eigen::Matrix<T, 3, 1>::UnitX())
        );
    }
    else {
        LOG_F(ERROR,"Rotation values contain %i elements instead of 3 or 4 elements",
              static_cast<int>(values.size()));
        return;
    }
};

/**
 * @brief convert a Vec3 based type values into a string,space-separated.
 */
template<typename T>
void vec2str(const math::Vec3<T>& vec, std::string& str_){

  std::ostringstream stream;
  stream << vec(0) << " " << vec(1) << " " << vec(2);
  str_ = stream.str();
};

/**
 * @brief convert a Rot3 based type values into a string,space-separated.
 */
template<typename T>
void rot2str(const math::Rot3<T>& q, std::string& str_){

  std::ostringstream stream;
  stream << q.x() << " " << q.y() << " " << q.z() << " " << q.w();
  str_ = stream.str();
};

/**
 * @brief This is a locale-safe version of string-to-double, which is suprisingly
 * difficult to do correctly.This function ensures that the C locale is used
 * for parsing, as that matches up with what the XSD for double specifies.
 */
template<typename T>
void str2num(const char *in, T& num_)
{
  try {
      if (std::is_same_v<T, double>) {
          num_ = std::stod(in);  
      }
      else if (std::is_same_v<T, float>) {
          num_ = std::stof(in);  
      }
      else if (std::is_same_v<T, long double>) {
          num_ = std::stold(in);  
      } else {
          LOG_F(ERROR,"unsupported type for conversion.");
      }
    } catch (const std::exception& e) {
      LOG_F(ERROR, "failed converting string to %s: %s", typeid(T).name(), e.what());
  }
};

namespace urdf {

    inline void split(const std::string& str,std::vector<std::string>& split_result,
            const std::string& delimiter)
    {
        size_t start = 0;
        size_t end   = 0;

        while ((end = str.find(delimiter, start)) != std::string::npos) {
            split_result.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
        }
        split_result.push_back(str.substr(start));
    };
}; // namesapce urdf
#endif // URDF_UTILITIES_H