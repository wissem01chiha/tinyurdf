#include "model.h"

namespace urdf {

  template <typename T>
  Model<T>::Model()
  {
  }

  template <typename T>
  Model<T>::Model(tinyxml2::XMLElement *xml)
  {
  }

  template <typename T>
  Model<T>::Model(const std::string &filename)
  {
  }

  template <typename T>
  std::shared_ptr<const Link<T>> Model<T>::getLink(const std::string &name) const
  {
      return std::shared_ptr<const Link<T>>();
  }

  template <typename T>
  std::shared_ptr<const Joint<T>> Model<T>::getJoint(const std::string &name) const
  {
      return std::shared_ptr<const Joint<T>>();
  }

  template <typename T>
  void Model<T>::getLinks(std::vector<std::shared_ptr<Link<T>>> &links) const
  {
  }

  template <typename T>
  void Model<T>::clear()
  {
  }

  template <typename T>
  std::shared_ptr<const Link<T>> Model<T>::getParentLink(const std::string &name) const
  {
      return std::shared_ptr<const Link<T>>();
  }

  template <typename T>
  std::shared_ptr<const Joint<T>> Model<T>::getParentJoint(const std::string &name) const
  {
      return std::shared_ptr<const Joint<T>>();
  }

  template <typename T>
  std::shared_ptr<const Link<T>> Model<T>::getChildLink(const std::string &name) const
  {
      return std::shared_ptr<const Link<T>>();
  }

  template <typename T>
  std::shared_ptr<const Joint<T>> Model<T>::getChildJoint(const std::string &name) const
  {
      return std::shared_ptr<const Joint<T>>();
  }


  template <typename T>
  bool Model<T>::initTree(std::map<std::string, std::string> &parent_link_tree)
  {
      return false;
  }

  template <typename T>
  bool Model<T>::initRoot(std::map<std::string, std::string> &parent_link_tree)
  {
      return false;
  }

}; // namespace urdf 

