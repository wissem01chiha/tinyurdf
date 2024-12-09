#ifndef TWIST_H
#define TWIST_H

#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <tinyxml2/tinyxml2.h>
#include <loguru/loguru.hpp>
#include "urdf_utilities.h"
#include "pose.h"

namespace urdf {

    template<typename T= double >
    class Twist
    {
    public:
        /// \brief default constructor 
        Twist();

        /// \brief constructor form an XMl elment
        Twist(tinyxml2::XMLElement* config);

        /// \brief Linear velocity 
        math::Vec3<T>  linear;

        /// \brief Angular velocity represented by Euler angles
        math::Vec3<T>  angular;

        void clear();
    };

}; // namespace urdf 
#endif // TWIST_H