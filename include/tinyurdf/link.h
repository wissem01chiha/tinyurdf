#ifndef LINK_H
#define LINK_H

#include <string>
#include <vector>
#include <memory>
#include <tinyxml2/tinyxml2.h>
#include <loguru/loguru.hpp>
#include "urdf_utilities.h"
#include "joint.h"
#include "color.h"
#include "pose.h"

namespace urdf {

  class Geometry
  {
    enum class Type { SPHERE, BOX, CYLINDER, MESH } type;
    virtual ~Geometry() = default;  
  };

  template<typename T = double >
  class Sphere : public Geometry 
  {
    T radius;
    Sphere(){ this->clear(); };  
    void clear(){radius = static_cast<T>(0.0);};
  };

  template<typename T = double >
  class Box : public Geometry
  {
    math::Vec3<T> dim;

    Box(){ this->clear();};
    void clear(){ dim.setZero(); };
  };

  template<typename T = double >
  class Cylinder : public Geometry
  {
    T   length;
    T   radius;

    Cylinder(){this->clear();};

    void clear(){ 
        length = static_cast<T>(0.0);
        radius = static_cast<T>(0.0);
    };
  };

  template<typename T = double >
  class Mesh : public Geometry
  {
    std::string    texture_filename;
    math::Vec3<T>  scale;
    Color<T>       color;

    Mesh(){ this->clear();};
      
    void clear() {
        color.clear();
        texture_filename.clear();
        scale.setOnes();
    };
  };

  template<typename T = double >
  class Material
  {
    std::string  name;
    std::string  texture_filename;
    Color<T>     color;
    T            density;
    
    Material(){this->clear();};

    void clear(){
        name.clear();
        texture_filename.clear();
        color.clear();
        density = static_cast<T>(0.0);
    };
  };

  template<typename T = double >
  class Inertial
  {
    public:
        Pose<T>   origin;
        T         mass;
        T         ixx, ixy, ixz, iyy, iyz, izz;

        Inertial(){this->clear();};

        /// \brief  safe constructor
        Inertial(T mass, T ixx, T ixy, T ixz, T iyy, T iyz, T izz) {
            if (!isValid(mass, ixx, ixy, ixz, iyy, iyz, izz)) {
                std::ostringstream error;
                error << "Invalid inertia matrix or mass."
                    << "Mass: " << mass
                    << ", ixx: " << ixx << ", ixy: " << ixy << ", ixz: " << ixz
                    << ", iyy: " << iyy << ", iyz: " << iyz << ", izz: " << izz;
                LOG_F(ERROR, "%s", error.str().c_str());
                throw std::invalid_argument(error.str());
            }
            this->mass = mass;
            this->ixx = ixx; this->ixy = ixy; this->ixz = ixz; 
            this->iyy = iyy; this->iyz = iyz; this->izz = izz;
        };

        void clear(){
            origin.clear(); 
            mass = static_cast<T>(0.0);
            ixx = ixy = ixz = iyy = iyz = izz = static_cast<T>(0.0);
        };
    private:
        static bool isValid(T mass, T ixx, T ixy, T ixz, T iyy, T iyz, T izz) {
            if (mass <= 0) {
                LOG_F(WARNING, "Mass must be positive: %f", mass);
                return false;
            }
            if (ixx <= 0 || iyy <= 0 || izz <= 0) {
                LOG_F(WARNING, 
                "Principal moments of inertia must be positive: ixx=%f, iyy=%f, izz=%f",
                 ixx, iyy, izz);
                return false;
            }
            if (std::abs(ixy) > std::sqrt(ixx * iyy) ||
                std::abs(ixz) > std::sqrt(ixx * izz) ||
                std::abs(iyz) > std::sqrt(iyy * izz)) {
                LOG_F(WARNING,
                "Products of inertia are invalid: ixy=%f, ixz=%f, iyz=%f",
                 ixy, ixz, iyz);
                return false;
            }
            return true;
        }
  };

  template<typename T = double >
  class Visual
  {
    Pose<T>                      origin;
    std::shared_ptr<Geometry>    geometry;
    std::string                  material_name;
    std::shared_ptr<Material<T>> material;

    Visual(){this->clear();};
    void clear(){
        origin.clear();
        geometry.reset();
        material_name.clear();
        material.reset();
    };
  };

  template<typename T = double >
  class Collision
  {
    std::shared_ptr<Geometry> geometry;
    Pose<T>                   origin;

    Collision(){
        geometry = std::make_shared<Geometry>();
        origin   = Pose<T>();
    };
      
    void clear(){
        geometry.reset();
        origin.clear();
    };
  };

  /**
   * @brief Represents a general description of a link element in a 
   * graph-based structure mechanism.
   * This structure allows modeling more complex connections between 
   * child and parent links via joints, representing a graph of linked 
   * elements example graph-based structure:
   * @verbatim
   *       child_link (1,i) --- --- parent_link (1,i)
   *                           |
   * child_link (2,i) ----- joint(i) --- parent_link (2,i)
   *             ...           |     ....
   *      child_link (n,i) ---  --- parent_link (n,i)
   * @endverbatim
   * @example 
   * XML Representation:
   * @code{.xml}
   * <link name="my_link">
   *   <inertial>
   *     <origin xyz="0 0 0.5" rpy="0 0 0"/>
   *     <mass value="1"/>
   *     <inertia ixx="100"  ixy="0"  ixz="0" iyy="100" iyz="0" izz="100" />
   *   </inertial>
   *   <visual>
   *     <origin xyz="0 0 0" rpy="0 0 0" />
   *     <geometry>
   *       <box size="1 1 1" />
   *     </geometry>
   *     <material name="Cyan">
   *       <color rgba="0 1.0 1.0 1.0"/>
   *     </material>
   *   </visual>
   *   <collision>
   *     <origin xyz="0 0 0" rpy="0 0 0"/>
   *     <geometry>
   *       <cylinder radius="1" length="0.5"/>
   *     </geometry>
   *   </collision>
   * </link>
   * @endcode 
   */
  template<typename T = double >
  class Link
  {
  public:
    /// \brief default constructor 
    Link();

    std::string                             name;
    std::shared_ptr<Inertial<T>>            inertial;
    std::shared_ptr<Visual<T>>              visual;
    std::shared_ptr<Collision<T>>           collision;

    /// \brief return a pointer to the parent links    
    std::shared_ptr<Link<T>> getParents() const;

    /// \brief set a new parent of the link 
    void setParent(std::shared_ptr<Link<T>> parent);

    /// \brief 
    void setParentJoint(std::shared_ptr<Joint<T>> child);

    /// \brief add a new child link 
    void addChild(std::shared_ptr<Link<T>> child);

    /// \brief add a child joint, if not set yet
    void addChildJoint(std::shared_ptr<Joint<T>> child);

    /// \brief reset member varaibles 
    void clear();

  private:
    /// @brief each Link have only one parent joint 
    std::unique_ptr<Joint<T>>               parent_joint;

    /// @brief each link have only one child joint to-go to 
    std::unique_ptr<Joint<T>>               child_joint;

    /// @brief each link can have many child links
    std::vector<std::shared_ptr<Link<T>>>   child_links;

    /// @brief each link can have many parent links
    std::vector<std::shared_ptr<Link<T>>>   parent_links_;
  };
}; // namespace urdf
#endif // LINK_H