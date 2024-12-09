#ifndef MODEL_INTERFACE_H
#define MODEL_INTERFACE_H

#include <memory>
#include "pose.h"
#include "link.h"
#include "model.h"
#include "joint.h"
#include "twist.h"
#include "urdf_utilities.h"

namespace urdf {

    template<typename T =  double >
    class ModelInterface
    {
    public:
        std::shared_ptr<const Link<T>>  getRoot(void)                     const;
        std::shared_ptr<const Link<T>>  getLink(const std::string& name)  const;
        std::shared_ptr<const Joint<T>> getJoint(const std::string& name) const;
        const std::string&              getName()                         const ;
        void       getLinks(std::vector<std::shared_ptr<Link<T>>>& links) const;
    
        void clear();
    
        void getLink(const std::string& name, std::shared_ptr<Link<T>> &link) ;
        std::shared_ptr<Material<T>> getMaterial(const std::string& name)     const;

        void initTree(std::map<std::string, std::string> &parent_link_tree);
        void initRoot(const std::map<std::string, std::string> &parent_link_tree);
    
        /// \brief complete list of model Links
        std::map<std::string, std::shared_ptr<Link<T>> >   links_;

        /// \brief complete list of Joints
        std::map<std::string, std::shared_ptr<Joint<T>>>   joints_;

        /// \brief complete list of Materials
        std::map<std::string, std::shared_ptr<Material<T>>> materials_;

        /// \brief The name of the multibody model
        std::string name_;

        /// \brief The root is always a link (the parent of the tree describing the robot)
        std::shared_ptr<Link<T>> root_link_;
    };
}; // namespace urdf
#endif // MODEL_INTERFACE_HPP