

#include "link_parser.h"
#include "joint_parser.h"
#include "world_parser.h"
#include "sensor_parser.h"
#include "world_parser.h"


ModelInterfaceSharedPtr  parseURDFFile(const std::string &path)
{
    std::ifstream stream( path.c_str() );
    if (!stream)
    {
      CONSOLE_BRIDGE_logError(("File " + path + " does not exist").c_str());
      return ModelInterfaceSharedPtr();
    }

    std::string xml_str((std::istreambuf_iterator<char>(stream)),
	                     std::istreambuf_iterator<char>());
    return urdf::parseURDF( xml_str );
}