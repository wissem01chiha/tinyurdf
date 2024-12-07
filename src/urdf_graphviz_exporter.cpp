#include "urdf_to_graphviz.hpp"

template <typename T>
void addChildLinkNames(const std::shared_ptr<urdf::Link<T>> link, std::ofstream &os)
{
  os << "\"" << link->name << "\" [label=\"" << link->name << "\"];" << std::endl;
  for (std::vector<LinkSharedPtr>::const_iterator child = link->child_links.begin(); child != link->child_links.end(); ++child)
    addChildLinkNames(*child, os);
}

template <typename T>
void addChildJointNames(const std::shared_ptr<urdf::Link<T>> link, std::ofstream &os)
{
  double r, p, y;
  for (std::vector<LinkSharedPtr>::const_iterator child = link->child_links.begin(); child != link->child_links.end(); ++child){
    (*child)->parent_joint->parent_to_joint_origin_transform.rotation.getRPY(r,p,y);
    os << "\"" << link->name << "\" -> \"" << (*child)->parent_joint->name 
       << "\" [label=\"xyz: "
       << (*child)->parent_joint->parents_to_joint_origin_transform.position.x << " " 
       << (*child)->parent_joint->parents_to_joint_origin_transform.position.y << " " 
       << (*child)->parent_joint->parent_to_joint_origin_transform.position.z << " " 
       << "\\nrpy: " << r << " " << p << " " << y << "\"]" << endl;
    os << "\"" << (*child)->parent_joint->name << "\" -> \"" << (*child)->name << "\"" << std::endl;
    addChildJointNames(*child, os);
  }
}

void printTree(const std::shared_ptr<urdf::Link<T>> link, std::string file)
{
  std::ofstream os;
  os.open(file.c_str());
  os << "digraph G {" << std::endl;

  os << "node [shape=box];" << std::endl;
  addChildLinkNames(link, os);

  os << "node [shape=ellipse, color=blue, fontcolor=blue];" << endl;
  addChildJointNames(link, os);

  os << "}" << endl;
  os.close();
}
