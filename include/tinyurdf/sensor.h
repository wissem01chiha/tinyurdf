#ifndef SENSOR_H
#define SENSOR_H

#include <memory>
#include <loguru/loguru.hpp>
#include <tinyxml2/tinyxml2.h>
#include "urdf_utilities.h"
#include "pose.h"
#include "link.h"

namespace urdf
{
    template<typename T = double >
    class Camera 
    {
    public:
        /// \brief default constructor 
        Camera();

        /// \brief copy constructor 
        Camera(const Camera<T>& rhs);

        /// \brief constructor from an xml element
        Camera(tinyxml2::XMLElement* config);

        /// \brief reset member variables 
        void clear();

        enum class Type {
            L8, R8G8B8, B8G8R8, BAYER_RGGB8, BAYER_BGGR8, 
            BAYER_GBRG8, BAYER_GRBG8
        };

        Type type; 

        unsigned int width, height;
        T hfov, near, far; 
    };

    template<typename T = double >
    class Sensor
    {
    public:
        /// \brief default constructor 
        Sensor();

        /// \brief copy constructor 
        Sensor(const Sensor<T>& rhs);

        /// \brief constructor from an xml element
        Sensor(tinyxml2::XMLElement* config_);

        /// \brief  sensor name must be unique
        std::string name;

        /// \brief  update rate in Hz
        T update_rate;

        /// transform from parent frame to optical center
        /// with z-forward and x-right, y-down
        Pose<T> origin;

        /// \brief Parent link element name.  A pointer is stored in parent_link_.
        std::string parent_link_name;

        /// \brief return sensor parent link pointer 
        std::shared_ptr<Link<T>> getParent() const ;

        /// \brief set sensor parent link pointer 
        void setParent(std::shared_ptr<Link<T>> parent);

        /// \brief reset member variables 
        void clear();
    private:
        std::weak_ptr<Link<T>> parent_link_;
    };
} // namespace urdf
#endif // SENSOR_HPP