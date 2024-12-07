#include "link.hpp"

namespace urdf 
{
    template <typename T>
    Link<T>::Link()
    {
    }

    template <typename T>
    std::shared_ptr<Link<T>> Link<T>::getParents() const
    {
        
    }

    template <typename T>
    void Link<T>::setParent(std::shared_ptr<Link> parent)
    {
    }

    template <typename T>
    void Link<T>::clear()
    {
        this->name.clear();
        this->inertial.reset();
        this->visual.reset();
        this->collision.reset();
        this->parent_joints.clear();
        this->child_joints.clear();
        this->child_links.clear();
    }

    template <typename T>
    void Link<T>::setParentJoint(std::shared_ptr<Joint<T>> child)
    {
    }

    template <typename T>
    void Link<T>::addChild(std::shared_ptr<Link> child)
    {
    }

    template <typename T>
    void Link<T>::addChildJoint(std::shared_ptr<Joint<T>> child)
    {
    }

}; // namespace urdf 

template class urdf::Link<double>;
template class urdf::Link<long double>;
template class urdf::Link<float>;