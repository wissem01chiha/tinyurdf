#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <map>
#include <tinyxml2/tinyxml2.h>
#include "urdf_utilities.h"
#include "joint.hpp"
#include "link.hpp"
#include "pose.hpp"

namespace urdf {

  template<typename T = double >
  class Model
  {
  public:
    /// \brief default constructor
    Model();

    /// \brief Load Model from TiXMLElement
    bool Model(TiXmlElement *xml);

    /// \brief Load Model given a filename
    bool Model(const std::string& filename);

    /// \brief Load Model from a XML-string
    bool Model(const std::string& xmlstring);

    /// \brief return a shared pointer to the root link 
    std::shared_ptr<const Link<T>> getRoot(void) const{return this->root_link_;};

    /// \brief  return a shared pointer to a given link by name 
    std::shared_ptr<const Link<T>> getLink(const std::string& name) const;

    /// \brief 
    std::shared_ptr<const Joint> getJoint(const std::string& name) const;

    /// \brief get the robot model name 
    const std::string& getName() const {return name_;};

    /// \brief 
    void getLinks(std::vector<std::shared_ptr<Link> >& links) const;

    /// \brief get parent Link of a Link given name
    std::shared_ptr<const Link> getParentLink(const std::string& name) const;

    /// \brief get parent Joint of a Link given name
    std::shared_ptr<const Joint> getParentJoint(const std::string& name) const;

    /// \brief get child Link of a Link given name
    std::shared_ptr<const Link> getChildLink(const std::string& name) const;

    /// \brief get child Joint of a Link given name
    std::shared_ptr<const Joint> getChildJoint(const std::string& name) const;

    /// \brief complete list of Links
    std::map<std::string, std::shared_ptr<Link> > links_;

    /// \brief complete list of Joints
    std::map<std::string, std::shared_ptr<Joint> > joints_;

    /// \brief complete list of Materials
    std::map<std::string, std::shared_ptr<Material> > materials_;

  private:

    /// \brief rest memeber varibles 
    void clear();

    std::string name_;

    /// \brief non-const getLink()
    void getLink(const std::string& name,std::shared_ptr<Link> &link) const;

    /// non-const getMaterial()
    std::shared_ptr<Material> getMaterial(const std::string& name) const;

    /// in initXml(), onece all links are loaded,
    /// it's time to build a tree
    bool initTree(std::map<std::string, std::string> &parent_link_tree);

    /// in initXml(), onece tree is built,
    /// it's time to find the root Link
    bool initRoot(std::map<std::string, std::string> &parent_link_tree);


    /// Model is restricted to a tree for now, which means there exists one root link
    ///  typically, root link is the world(inertial).  Where world is a special link
    /// or is the root_link_ the link attached to the world by PLANAR/FLOATING joint?
    ///  hmm...
    std::shared_ptr<Link> root_link_;

  };

}

#endif // MODEL_HPP
