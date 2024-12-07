#ifndef MODEL_INTERFACE_HPP
#define MODEL_INTERFACE_HPP

#include <memory>
#include "pose.hpp"
#include "link.hpp"
#include "model.hpp"
#include "joint.hpp"
#include "twist.hpp"
#include "urdf_utilities.h"

namespace urdf {

    template<typename T =  double >
    class ModelInterface
    {
    public:
        std::shared_ptr<const Link<T>> getRoot(void) const;

        std::shared_ptr<const Link<T>>  getLink(const std::string& name) const;
    
        std::shared_ptr<const Joint<T>> getJoint(const std::string& name) const;
    
        const std::string& getName() const ;

        void getLinks(std::vector<std::shared_ptr<Link<T>>>& links) const;
    
        void clear();
    
        /// \brief  non-const getLink()
        void getLink(const std::string& name, std::shared_ptr<Link<T>> &link) const;
    
        /// \brief  non-const getMaterial()
        std::shared_ptr<Material<T>> getMaterial(const std::string& name) const;
    
        void initTree(std::map<std::string, std::string> &parent_link_tree);

        /// \brief 
        void initRoot(const std::map<std::string, std::string> &parent_link_tree);
    
        /// \brief complete list of Links
        std::map<std::string, LinkSharedPtr> links_;

        /// \brief complete list of Joints
        std::map<std::string, JointSharedPtr> joints_;
        /// \brief complete list of Materials
        std::map<std::string, MaterialSharedPtr> materials_;

        /// \brief The name of the robot model
        std::string name_;

        /// \brief The root is always a link (the parent of the tree describing the robot)
        LinkSharedPtr root_link_;
    };
}; // namespace urdf
#endif // MODEL_INTERFACE_HPP