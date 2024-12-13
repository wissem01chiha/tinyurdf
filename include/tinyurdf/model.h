#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <map>
#include <vector>
#include <tinyxml2/tinyxml2.h>
#include "urdf_utilities.h"
#include "joint.h"
#include "link.h"
#include "pose.h"

namespace urdf {

  template<typename T = double >
  class Model
  {
  public:
    /// \brief default constructor
    Model();

    /// \brief Load Model from TiXMLElement
    /// \note  major change : as for extension for urdf description
    /// we accept that the xml global elment
    /// @code{.xml}
    Model(tinyxml2::XMLElement* xml);

    /// \brief return a shared pointer to the root link 
    std::shared_ptr<Link<T>>  getRoot(void) const{return this->root_link_;};

    /// \brief  return a shared pointer to a given link by name 
    std::shared_ptr<Link<T>>  getLink(const std::string& name) const;

    /// \brief return a shared pointer to a given Joint by name 
    std::shared_ptr<const Joint<T>> getJoint(const std::string& name) const;

    /// \brief get the multibody model name 
    const std::string& getName() const {return name_;};

    /// \brief return a vector of pointers to model links
    void getLinks(std::vector<std::shared_ptr<Link<T>>>& links) const;

    /// \brief reset memeber vars
    void clear();

    /// \brief get parent Link of a Link given name
    std::shared_ptr<const Link<T>> getParentLink(const std::string& name) const;

    /// \brief get parent Joint of a Link given name
    std::shared_ptr<const Joint<T>> getParentJoint(const std::string& name) const;

    /// \brief get child Link of a Link given name
    std::shared_ptr<const Link<T>> getChildLink(const std::string& name) const;

    /// \brief get child Joint of a Link given name
    std::shared_ptr<const Joint<T>> getChildJoint(const std::string& name) const;

    /// \brief complete list of Links
    std::map<std::string, std::shared_ptr<Link<T>>>     links_;

    /// \brief complete list of Joints
    std::map<std::string, std::shared_ptr<Joint<T>>>    joints_;

    /// \brief complete list of Materials
    std::map<std::string, std::shared_ptr<Material<T>>>  materials_;

  private:

    std::string name_;

    /// \brief non-const getLink()
    void getLink(const std::string& name,std::shared_ptr<Link<T>> &link) const;

    /// non-const getMaterial()
    std::shared_ptr<Material<T>> getMaterial(const std::string& name) const;

    /// in initXml(), onece all links are loaded,
    /// it's time to build a tree
    bool initTree(std::map<std::string, std::string> &parent_link_tree);

    /// in initXml(), onece tree is built,
    /// it's time to find the root Link
    bool initRoot(std::map<std::string, std::string> &parent_link_tree);


    /// Model is restricted to a tree for now, which means there exists one root link
    ///  typically, root link is the world(inertial).  Where world is a special link
    /// or is the root_link_ the link attached to the world by PLANAR/FLOATING joint
    std::vector<std::shared_ptr<Link<T>>> root_links_;
  };
  
}; // namespace urdf
#endif // MODEL_H
