#ifndef JOINT_H
#define JOINT_H

#include <stdexcept>
#include <string>
#include <memory>
#include <vector>
#include <tinyxml2/tinyxml2.h>
#include <loguru/loguru.hpp>
#include "urdf_utilities.h"
#include "pose.h"

namespace urdf {

  template <typename T = double >
  struct JointDynamics
  {
    T damping;
    T friction;
    T inertia;

    JointDynamics(): damping(static_cast<T>(0.0)),
                    friction(static_cast<T>(0.0)),
                    inertia(static_cast<T>(0.0)){};

    void clear(){
      damping = static_cast<T>(0.0);
      friction= static_cast<T>(0.0);
      inertia = static_cast<T>(0.0);
    }
  };

  template <typename T = double >
  struct JointLimits
  {
      T lower;
      T upper;
      T effort;
      T velocity;

      JointLimits():lower(static_cast<T>(0.0)),
                  upper(static_cast<T>(0.0)),
                  effort(static_cast<T>(0.0)),
                  velocity(static_cast<T>(0.0)){};

      void clear(){
        lower = static_cast<T>(0.0);
        upper = static_cast<T>(0.0);
        effort = static_cast<T>(0.0);
        velocity = static_cast<T>(0.0);
      };
  };

  template <typename T = double >
  struct JointSafety
  {
      T soft_upper_limit;
      T soft_lower_limit;
      T k_position;
      T k_velocity;

      JointSafety(): soft_upper_limit(static_cast<T>(0.0)),
                soft_lower_limit(static_cast<T>(0.0)),
                k_position(static_cast<T>(0.0)),
                k_velocity(static_cast<T>(0.0)){};

      void clear() {
        soft_upper_limit = static_cast<T>(0.0);
        soft_lower_limit = static_cast<T>(0.0); 
        k_position       = static_cast<T>(0.0);
        k_velocity       = static_cast<T>(0.0);
    };
  };

  template <typename T = double >
  struct JointCalibration
  {
      T reference_position;
      T rising;
      T falling;

      JointCalibration(): reference_position(static_cast<T>(0.0)),
                        rising(static_cast<T>(0.0)),
                        falling(static_cast<T>(0.0)) {};
      void clear(){
        reference_position = static_cast<T>(0.0);
        rising  = static_cast<T>(0.0);
        falling = static_cast<T>(0.0);
      };
  };

  template <typename T =  double >
  struct JointMimic
  {
      T offset;
      T multiplier;
      std::string joint_name;

      JointMimic(): offset(static_cast<T>(0.0)),
        multiplier(static_cast<T>(1.0)),
        joint_name("") {};

      void clear(){
        offset = static_cast<T>(0.0);
        multiplier = static_cast<T>(1.0);
        joint_name.clear();
    };
  };

  /**
   * @brief generalized description of a joint:
   * original reference : @link https://wiki.ros.org/urdf/XML/joint
   * @code{.xml}
   * <joint name="my_joint" type="floating">
   *     <origin xyz="0 0 1" rpy="0 0 3.1416"    parent = "parent_link_1"/>
   *     <origin xyz="0 1.5 0.8" rpy="2.5 0 3.0" parent = "parent_link_2"/>
   *     ...
   *     <origin xyz="0 1.5 0.8" rpy="2.5 0 3.0" parent = "parent_link_n"/>
   *
   *     <parent link = "parent_link_1" />
   *     <parent link = "parent_link_2" />
   *     ...
   *     <parent link = "parent_link_n" />
   * 
   *     <child link  = "child_link_1"/>
   *     <child link  = "child_link_2"/>
   *     ...
   *     <child link  = "child_link_n"/>
   * 
   *     <calibration rising="0.0" falling ="0.0"/>
   *     <dynamics damping="0.0" friction="0.0"/>
   *     <axis  xyz = "0 1 0"/>                                            
   *     <limit effort="30" velocity="1.0" lower="-2.2" upper="0.7"/>
   *     <safety_controller k_velocity="10" k_position="15" soft_lower_limit="-2.0" soft_upper_limit="0.5"/>
   * </joint>
   * @endcode
   */
  template<typename T = double >
  class Joint
  {
  public:
    /// \brief  default constructor
    Joint();

    /// \brief copy constructor 
    Joint(const Joint& rhs);

    /// \brief move constructor 
    Joint(Joint<T>&& rhs) noexcept ;

    /// \brief reset member variables
    void clear();

    /// \brief     type_       meaning of axis_
    /// ------------------------------------------------------
    ///            UNKNOWN     unknown type
    ///            REVOLUTE    rotation axis
    ///            PRISMATIC   translation axis
    ///            FLOATING    N/A
    ///            PLANAR      plane normal axis
    ///            FIXED       N/A
    ///            UNIVERSAL   N/A
    enum class Type
    {
      UNKNOWN, REVOLUTE, CONTINUOUS, PRISMATIC, FLOATING, PLANAR, FIXED, 
      UNIVERSAL
    };

    Type           type;
    
    std::string    name;

    math::Vec3<T>  axis;

    /// \brief childs Link element, childs link frame is the same as the Joint frame. 
    std::vector<std::string>             child_links_name;

    /// \brief parent Links elements, origin specifies the transform from Parent 
    /// Link to Joint Frame.
    std::vector<std::string>             parent_links_name;

    /// \brief transform from Parent Links frames to Joint frame
    std::vector<Pose<T>>                 parents_to_joint_origin_transform;

    std::shared_ptr<JointDynamics<T>>    dynamics;
    std::shared_ptr<JointLimits<T>>      limits;
    std::shared_ptr<JointSafety<T>>      safety;
    std::shared_ptr<JointCalibration<T>> calibration;
    std::shared_ptr<JointMimic<T>>       mimic;
  };
}; // namespace urdf
#endif // JOINT_H