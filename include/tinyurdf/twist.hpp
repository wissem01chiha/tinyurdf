#ifndef TWIST_HPP
#define TWIST_HPP

#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <tinyxml2/tinyxml2.h>
#include <loguru/loguru.hpp>
#include "urdf_utilities.h"
#include "pose.hpp"

namespace urdf {

    template<typename T>
    class Twist
    {
    public:
        /// \brief default constructor 
        Twist();

        /// \brief 
        Twist(tinyxml2::XMLElement* config);

        /// \brief Linear velocity 
        math::Vec3<T>  linear;

        /// \brief Angular velocity represented by Euler angles
        math::Vec3<T>  angular;

        void clear();
    };

}; 
#endif // TWIST_HPP