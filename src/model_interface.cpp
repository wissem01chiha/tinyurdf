#include "model_interface.hpp"

namespace urdf
{
    template <typename T>
    std::shared_ptr<const Link<T>> ModelInterface<T>::getRoot(void) const
    {
        return this->root_link_;
    }

    template <typename T>
    std::shared_ptr<const Link<T>> ModelInterface<T>::getLink(const std::string &name) const
    {
        std::shared_ptr<const Link<T>>  ptr;
        if (this->links_.find(name) == this->links_.end())
            ptr.reset();
        else
            ptr = this->links_.find(name)->second;
        return ptr;
    }

    template <typename T>
    std::shared_ptr<const Joint<T>> ModelInterface<T>::getJoint(const std::string &name) const
    {
            std::shared_ptr<const Joint<T>> ptr;
            if (this->joints_.find(name) == this->joints_.end())
            ptr.reset();
            else
            ptr = this->joints_.find(name)->second;
            return ptr;
    }

    template <typename T>
    const std::string &ModelInterface<T>::getName() const { return name_; }

    template <typename T>
    void ModelInterface<T>::getLinks(std::vector<std::shared_ptr<Link<T>>> &links) const
    {
            for (std::map<std::string,std::shared_ptr<Link<T>>>::const_iterator link = 
            this->links_.begin();link != this->links_.end(); link++){

                links.push_back(link->second);
            }
    }

    template <typename T>
    void ModelInterface<T>::clear()
    {
        name_.clear();
        this->links_.clear();
        this->joints_.clear();
        this->materials_.clear();
        this->root_link_.reset();
    }
    template <typename T>
    void ModelInterface<T>::getLink(const std::string &name, std::shared_ptr<Link<T>> &link) const {
            LinkSharedPtr ptr;
        if (this->links_.find(name) == this->links_.end())
        ptr.reset();
        else
        ptr = this->links_.find(name)->second;
        link = ptr;
    }
    template <typename T>
    std::shared_ptr<Material<T>> ModelInterface<T>::getMaterial(const std::string &name) const
    {
        {
            MaterialSharedPtr ptr;
            if (this->materials_.find(name) == this->materials_.end())
            ptr.reset();
            else
            ptr = this->materials_.find(name)->second;
            return ptr;
        };
    }
    template <typename T>
    void ModelInterface<T>::initTree(std::map<std::string, std::string> &parent_link_tree) {
        {
        // loop through all joints, for every link, assign children links and children joints
        for (std::map<std::string, JointSharedPtr>::iterator joint = this->joints_.begin();joint != this->joints_.end(); joint++)
        {
        std::string parent_link_name = joint->second->parent_link_name;
        std::string child_link_name = joint->second->child_link_name;
        
        if (parent_link_name.empty() || child_link_name.empty())
        {
            throw ParseError("Joint [" + joint->second->name + "] is missing a parent and/or child link specification.");
        }
        else
        {
            // find child and parent links
            LinkSharedPtr child_link, parent_link;
            this->getLink(child_link_name, child_link);
            if (!child_link)
            {
            throw ParseError("child link [" + child_link_name + "] of joint [" + joint->first + "] not found");
            }
            this->getLink(parent_link_name, parent_link);
            if (!parent_link)
            {
            throw ParseError("parent link [" + parent_link_name + "] of joint [" + joint->first + "] not found.  This is not valid according to the URDF spec. Every link you refer to from a joint needs to be explicitly defined in the robot description. To fix this problem you can either remove this joint [" + joint->first + "] from your urdf file, or add \"<link name=\"" + parent_link_name + "\" />\" to your urdf file.");
            }
            
            //set parent link for child link
            child_link->setParent(parent_link);

            //set parent joint for child link        
            child_link->parent_joint = joint->second;
            
            //set child joint for parent link
            parent_link->child_joints.push_back(joint->second);

            //set child link for parent link
            parent_link->child_links.push_back(child_link);

            // fill in child/parent string map
            parent_link_tree[child_link->name] = parent_link_name;
        }
        }
    }
    }
    template <typename T>
    void ModelInterface<T>::initRoot(const std::map<std::string, std::string> &parent_link_tree) {
        { 
        this->root_link_.reset();
        
        // find the links that have no parent in the tree
        for (std::map<std::string, LinkSharedPtr>::const_iterator l=this->links_.begin(); l!=this->links_.end(); l++)
        {
        std::map<std::string, std::string >::const_iterator parent = parent_link_tree.find(l->first);
        if (parent == parent_link_tree.end())
        {
            // store root link
            if (!this->root_link_)
            {
            getLink(l->first, this->root_link_);
            }
            // we already found a root link
            else
            {
            throw ParseError("Two root links found: [" + this->root_link_->name + "] and [" + l->first + "]");
            }
        }
        }
        if (!this->root_link_)
        {
        throw ParseError("No root link found. The robot xml is not a valid tree.");
        }
    }
    };
} // namespace urdf

template class urdf::ModelInterface<double>;
template class urdf::ModelInterface<float>;
template class urdf::ModelInterface<long double>;