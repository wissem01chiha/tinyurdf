#include "sensor.h"

namespace urdf
{   
    template <typename T>
    Camera<T>::Camera()
    {
    }

    template <typename T>
    Camera<T>::Camera(const Camera<T> &rhs)
    {
    }

    template <typename T>
    Camera<T>::Camera(tinyxml2::XMLElement *config)
    {
    }

    template <typename T>
    void Camera<T>::clear()
    {
        hfov, width, height, near, far = std::static_cast<T>(0.0);
    }

    template <typename T>
    Sensor<T>::Sensor()
    {
    }

    template <typename T>
    Sensor<T>::Sensor(const Sensor<T> &rhs)
    {
    }

    template <typename T>
    Sensor<T>::Sensor(tinyxml2::XMLElement *config)
    {
        this->clear();
        const char *name_char = config->Attribute("name");
        if (!name_char)
        {
            LOG_F(ERROR, "No name given for the sensor.");
        }
        this->name = std::string(name_char);

        const char *parent_link_name_char = config->Attribute("parent_link_name");
        if (!parent_link_name_char)
        {
            LOG_F(ERROR,"No parent_link_name given for the sensor.");
        }
        this->parent_link_name = std::string(parent_link_name_char);

        tinyxml2::XMLElement *o = config->FirstChildElement("origin");
        if (o)
        {
            if (!parsePose(sensor.origin, o))
        }
    }
    template <typename T>
    std::shared_ptr<Link<T>> Sensor<T>::getParent() const
    {
        return parent_link_.lock();
    }
    template <typename T>
    void Sensor<T>::setParent(std::shared_ptr<Link<T>> parent)
    {
        this->parent_link_ = parent;
    }
    template <typename T>
    void Sensor<T>::clear()
    {
        this->name.clear();
        this->sensor.reset();
        this->parent_link_name.clear();
        this->parent_link_.reset();
    }
}; // namespace urdf

template class urdf::Sensor<double>;
template class urdf::Sensor<float>;
template class urdf::Sensor<long double>;