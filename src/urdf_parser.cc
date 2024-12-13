#include "urdf_parser.h"


namespace tinyurdf {

    template <typename T>
    URDFParser<T>::URDFParser()
    {
        model = std::make_shared<urdf::Model<T>>();
        world = std::make_shared<urdf::World<T>>();
    }

    template <typename T>
    URDFParser<T>::URDFParser(const std::string &path_)
    {
        std::filesystem::path p = path_;
        if (!std::filesystem::exists(p))  
        {
            LOG_F(ERROR, "URDF file (%s) does not exist!", path_.c_str());  
        }
        else
        {
            tinyxml2::XMLError eResult = doc.LoadFile(path_);
            if (eResult != tinyxml2::XML_SUCCESS) {
                LOG_F(ERROR, "Error loading XML file: " , doc.ErrorStr());
            } 
        }
    }

    template <typename T>
    void URDFParser<T>::parse()
    {
        if(!parseVersion()){
            LOG_F(ERROR, "Parser Engine : parse version error");
        }else
        {
            
        }
        
    }

    template <typename T>
    std::shared_ptr<urdf::Model<T>> *URDFParser<T>::getModel()
    {
        return model.get();
    }

    template <typename T>
    void URDFParser<T>::log(const std::string &path)
    {
    }
    
    template <typename T>
    bool URDFParser<T>::parseVersion()
    {
        tinyxml2::XMLDeclaration* decl = doc.FirstChild()->ToXMLDeclaration();
        if (decl) {
            const char* version_str = decl->Version();
            version = urdf::URDFVersion(version_str);
            if (version.getMajor()!= 1 && version.getMinor()!=0)
            {
                LOG_F(ERROR, "Parser Engine : only XML version 1.0 supported");
                return false;
            }
            
        } else {
            LOG_F(ERROR,"No XML declaration found!");
            return false;
        }
        return true;
    }
};

template class  tinyurdf::URDFParser<double>;
template class  tinyurdf::URDFParser<long double>;
template class  tinyurdf::URDFParser<float>;