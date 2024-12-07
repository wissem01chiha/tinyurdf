#ifndef URDF_TO_GRAPHIZ
#define URDF_TO_GRAPHIZ

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <loguru/loguru.hpp>
#include "link.hpp"
#include "joint.hpp"
#include "urdf_version.hpp"
#include "model_interface.hpp"

/// \brief 
template<typename T = double >
void addChildLinkNames(const std::shared_ptr<urdf::Link<T>> link, std::ofstream& os);

/// \brief 
template <typename T = double >
void addChildJointNames(const std::shared_ptr<urdf::Link<T>> link, std::ofstream& os);

/// \brief 
template<typename T = double >
void printTree(const std::shared_ptr<urdf::Link<T>> link, std::string file);



int main(int argc, char** argv)
{
  std::string executable_name(argv[0]);
  std::string deprecated_name("urdf_to_graphiz");
  if (deprecated_name == executable_name.substr(executable_name.size() - deprecated_name.size())) {
    std::cerr << "WARNING: The executable named '" << deprecated_name
              << "' is deprecated. Use 'urdf_to_graphviz' instead." << std::endl;
  }
  if (argc < 2 || argc > 3) {
    std::cerr << "Usage: urdf_to_graphviz input.xml [OUTPUT]"
              << "  Will create either $ROBOT_NAME.gv & $ROBOT_NAME.pdf in CWD"
              << "  or OUTPUT.gv & OUTPUT.pdf." << std::endl;
    return -1;
  }
  if (argc != 3) {
    std::cerr << "WARNING: OUTPUT not given. This type of usage is deprecated!"
              << "Usage: urdf_to_graphviz input.xml [OUTPUT]"
              << "  Will create either $ROBOT_NAME.gv & $ROBOT_NAME.pdf in CWD"
              << "  or OUTPUT.gv & OUTPUT.pdf." << std::endl;
  }

  // get the entire file
  std::string xml_string;
  std::fstream xml_file(argv[1], std::fstream::in);
  while ( xml_file.good() )
  {
    std::string line;
    std::getline( xml_file, line);
    xml_string += (line + "\n");
  }
  xml_file.close();

  std::shared_ptr<urdf::ModelInterface<double>> robot = parseURDF(xml_string);
  if (!robot){
    std::cerr << "ERROR: Model Parsing the xml failed" << std::endl;
    return -1;
  }

  std::string output = robot->getName();
  if (argc == 3)
    output = argv[2];

  // print entire tree to file
  printTree<double>(robot->getRoot(), output+".gv");
  std::cout << "Created file " << output << ".gv" << std::endl;

  std::string command = "dot -Tpdf "+output+".gv  -o "+output+".pdf";
  if (system(command.c_str()) != -1)
    std::cout << "Created file " << output << ".pdf" << std::endl;
  else
    std::cout << "There was an error executing '" << command << "'" << std::endl;
  return 0;
}
#endif // URDF_TO_GRAPHIZ