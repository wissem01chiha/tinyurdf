#include "joint.hpp"

namespace urdf {

    template <typename T>
    Joint<T>::Joint(){ 
        dynamics = std::make_shared<JointDynamics<T>>();
        limits  = std::make_shared<JointLimits<T>>();
        safety  = std::make_shared<JointSafety<T>>();
        calibration = std::make_shared<JointCalibration<T>>();
        mimic = std::make_shared<JointMimic<T>>();
        type = Type::UNKNOWN;
     }

    template <typename T>
    Joint<T>::Joint(const Joint &rhs)
    {
        this->type = rhs.type;
        this->axis = rhs.axis;
        this->name = rhs.name;
        this->child_links_name = rhs.child_links_name; 
        this->parent_links_name = rhs.parent_links_name; 
        this->parents_to_joint_origin_transform = rhs.parents_to_joint_origin_transform;

        if (rhs.dynamics) { dynamics = std::make_shared<JointDynamics<T>>(*rhs.dynamics);  }
        if (rhs.limits) { limits = std::make_shared<JointLimits<T>>(*rhs.limits); }
        if (rhs.safety) { safety = std::make_shared<JointSafety<T>>(*rhs.safety); }
        if (rhs.calibration) { calibration = std::make_shared<JointCalibration<T>>(*rhs.calibration);}
        if (rhs.mimic) { mimic = std::make_shared<JointMimic<T>>(*rhs.mimic); }
    }

    template <typename T>
    Joint<T>::Joint(Joint<T> &&rhs) noexcept
    {
    }

    template <typename T>
    void Joint<T>::clear()
    {
        this->axis.setZero();
        this->child_links_name.clear();
        this->parent_links_name.clear();
        this->parents_to_joint_origin_transform.clear();
        this->dynamics.reset();
        this->limits.reset();
        this->safety.reset();
        this->calibration.reset();
        this->type = Type::UNKNOWN;
    }
}; //namespace urdf 

template class urdf::Joint<double>;
template class urdf::Joint<long double>;
template class urdf::Joint<float>;