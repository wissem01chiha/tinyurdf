#include <cstring>
#include <iostream>
#include <fstream>

#include "tinyurdf.hpp"


int main(int argc, char** argv)
{
  if (argc < 2){
    std::cerr << "Expect URDF xml file to parse. Use - for stdin" << std::endl;
    return -1;
  }

  std::string xml_string;
  if (strcmp(argv[1], "-") == 0)
  {
    for (std::string line; std::getline(std::cin, line);)
    {
      xml_string += (line + "\n");
    }
  } else
  {
    std::ifstream xml_file(argv[1]);
    for (std::string line; std::getline(xml_file, line);)
    {
      xml_string += (line + "\n");
    }
    xml_file.close();
  }

  std::shared_ptr<urdf::Model<double>> robot = parseURDF(xml_string);
  if (!robot){
    std::cerr << "ERROR: Model Parsing the xml failed" << std::endl;
    return -1;
  }
  std::cout << "robot name is: " << robot->getName() << std::endl;

  // get info from parser
  std::cout << "---------- Successfully Parsed XML ---------------" << std::endl;
  // get root link
  LinkConstSharedPtr root_link=robot->getRoot();
  if (!root_link) return -1;

  std::cout << "root Link: " << root_link->name << " has " << root_link->child_links.size() << " child(ren)" << std::endl;


  // print entire tree
  printTree(root_link);
  return 0;
}

