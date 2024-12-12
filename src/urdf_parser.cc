#include "urdf_parser.h"


namespace tinyurdf {

    template <typename T>
    URDFParser<T>::URDFParser()
    {
    }
    template <typename T>
    URDFParser<T>::URDFParser(const std::string &path)
    {
    }
    template <typename T>
    void URDFParser<T>::parse()
    {
    }
    template <typename T>
    std::shared_ptr<urdf::Model<T>> *URDFParser<T>::getModel()
    {
        return nullptr;
    }
    template <typename T>
    void URDFParser<T>::log(const std::string &path)
    {
    }
};

/*  
inline ModelInterfaceSharedPtr  parseURDFFile(const std::string &path)
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
};
*/