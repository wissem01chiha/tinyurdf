#include "link.h"

namespace urdf 
{
    template <typename T>
    Link<T>::Link()
    {
        name = std::string("link");
        inertial = std::make_shared<Inertial<T>>();
        visual = std::make_shared<Visual<T>>();
        material = std::make_shared<Material<T>>();
    };

    template <typename T>
    std::shared_ptr<Link<T>> Link<T>::getParents() const
    {
        if (!parent_links_.empty()) {
            return parent_links_.front(); 
        }
        return nullptr; 
    };

    template <typename T>
    void Link<T>::setParent(std::shared_ptr<Link> parent)
    {
        if (parent) {
            parent_links_.push_back(parent);  
        }
    }

    template <typename T>
    void Link<T>::clear()
    {
        this->name.clear();
        this->inertial.reset();
        this->visual.reset();
        this->collision.reset();
        this->parent_joint.reset();
        this->child_joint.reset();
        this->child_links.clear();
    }

    template <typename T>
    void Link<T>::setParentJoint(std::shared_ptr<Joint<T>> parent)
    {
        if (parent) {
            parent_joint = std::make_unique<Joint<T>>(*parent);
        }
    }

    template <typename T>
    void Link<T>::addChild(std::shared_ptr<Link> child)
    {
        if (child) {
            child_links.push_back(child);  
        }
    }

    template <typename T>
    void Link<T>::addChildJoint(std::shared_ptr<Joint<T>> child)
    {
        if (child && !child_joint) {
            child_joint = std::make_unique<Joint<T>>(*child); 
        }
    }

}; // namespace urdf 

template class urdf::Link<double>;
template class urdf::Link<long double>;
template class urdf::Link<float>;