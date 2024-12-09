#include "joint_parser.h"

namespace tinyurdf{

  template <typename T>
  JointParser<T>::JointParser()
  {
    
  }

  template <typename T>
  JointParser<T>::JointParser(tinyxml2::XMLElement *config_)
  {
    this->config = config_;
  }

  template <typename T>
  JointParser<T>::JointParser(const JointParser &rhs)
  {
  }

  template <typename T>
  bool JointParser<T>::parseDynamics(tinyxml2::XMLElement* xml)
  {
    joint->dynamics->clear();
    const char* damping_str = xml->Attribute("damping");
    if (damping_str == NULL){
      LOG_F(WARNING,"no damping, defaults to 0");
      joint->dynamics->damping = static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(damping_str, joint->dynamics->damping);
      } catch(std::runtime_error &) {
        LOG_F(ERROR, "damping value (%s) is not a valid float", damping_str);
        return false;
      }
    }
    const char* friction_str = xml->Attribute("friction");
    if (friction_str == NULL){
      LOG_F(WARNING, "no friction, defaults to 0");
      joint->dynamics->friction = static_cast<T>(0);
    }
    else
    {
      try {
        str2num<T>(friction_str, joint->dynamics->friction);
      } catch (std::runtime_error &) {
         LOG_F(ERROR, "friction value (%s) is not a valid float", friction_str);
        return false;
      }
    }
    if (damping_str == NULL && friction_str == NULL)
    {
      LOG_F(ERROR,"joint dynamics element specified with no damping and no friction");
      return false;
    }
    else{ return true;}
  };
 
  template <typename T>
  bool JointParser<T>::parseLimits(tinyxml2::XMLElement* xml)
  {
    joint->limits->clear();
    const char* lower_str = xml->Attribute("lower");
    if (lower_str == NULL){
      LOG_F(WARNING,"joint limit: no lower, defaults to 0");
      joint->limits->lower = static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(lower_str, joint->limits->lower);
      } catch (std::runtime_error &) {
         LOG_F(ERROR, "lower value (%s) is not a valid float", lower_str);
        return false;
      }
    }
    const char* upper_str = xml->Attribute("upper");
    if (upper_str == NULL){
      LOG_F(WARNING,"urdfdom.joint_limit: no upper, , defaults to 0");
      joint->limits->upper =static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(upper_str, joint->limits->upper);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "upper value (%s) is not a valid float", upper_str);
        return false;
      }
    }
    const char* effort_str = xml->Attribute("effort");
    if (effort_str == NULL){
       LOG_F(ERROR, "joint limit: no effort");
      return false;
    }
    else
    {
      try {
        str2num<T>(effort_str, joint->limits->effort);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "effort value (%s) is not a valid float", effort_str);
        return false;
      }
    }

    const char* velocity_str = xml->Attribute("velocity");
    if (velocity_str == NULL){
       LOG_F(ERROR, "joint limit: no velocity");
      return false;
    }
    else
    {
      try {
        str2num<T>(velocity_str, joint->limits->velocity);
      } catch(std::runtime_error &) {
         LOG_F(ERROR,"velocity value (%s) is not a valid float", velocity_str);
        return false;
      }
    }
    return true;
  };

  template <typename T>
  bool JointParser<T>::parseSafety(tinyxml2::XMLElement* xml)
  {
    joint->safety->clear();
    const char* soft_lower_limit_str = xml->Attribute("soft_lower_limit");
    if (soft_lower_limit_str == NULL)
    {
      LOG_F(WARNING,"joint safety: no soft_lower_limit, using default value");
      joint->safety->soft_lower_limit =static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(soft_lower_limit_str, joint->safety->soft_lower_limit);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "soft_lower_limit value (%s) is not a valid float", soft_lower_limit_str);
        return false;
      }
    }
    const char* soft_upper_limit_str = xml->Attribute("soft_upper_limit");
    if (soft_upper_limit_str == NULL)
    {
      LOG_F(WARNING,"joint safety: no soft_upper_limit, using default value");
      joint->safety->soft_upper_limit = static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(soft_upper_limit_str, joint->safety->soft_upper_limit);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "soft_upper_limit value (%s) is not a valid float", soft_upper_limit_str);
        return false;
      }
    }
    const char* k_position_str = xml->Attribute("k_position");
    if (k_position_str == NULL)
    {
      LOG_F(WARNING,"joint_safety: no k_position, using default value");
      joint->safety->k_position = static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(k_position_str, joint->safety->k_position);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "k_position value (%s) is not a valid float", k_position_str);
        return false;
      }
    }
    const char* k_velocity_str = xml->Attribute("k_velocity");
    if (k_velocity_str == NULL)
    {
      LOG_F(ERROR, "joint safety: no k_velocity");
      return false;
    }
    else
    {
      try {
        str2num<T>(k_velocity_str, joint->safety->k_velocity);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "k_velocity value (%s) is not a valid float", k_velocity_str);
        return false;
      }
    }
    return true;
  };

  template <typename T>
  bool JointParser<T>::parseCalibration(tinyxml2::XMLElement* xml)
  {
    joint->calibration->clear();
    const char* rising_position_str = xml->Attribute("rising");
    if (rising_position_str == NULL)
    {
      LOG_F(WARNING,"joint_calibration: no rising, using default value");
      joint->calibration->rising = static_cast<T>(0.0);
    }
    else
    {
      try {
        T rising_position;
        str2num<T>(rising_position_str, rising_position);
        joint->calibration->rising = rising_position;
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "rising value (%s) is not a valid float", rising_position_str);
        return false;
      }
    }
    const char* falling_position_str = xml->Attribute("falling");
    if (falling_position_str == NULL)
    {
      LOG_F(WARNING,"urdfdom.joint_calibration: no falling, using default value");
      joint->calibration->falling = static_cast<T>(0.0);
    }
    else
    {
      try {
        T falling_position;
        str2num<T>(falling_position_str, falling_position);
        joint->calibration->falling = falling_position;
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "falling value (%s) is not a valid float", falling_position_str);
        return false;
      }
    }
    return true;
  };

  template <typename T>
  bool JointParser<T>::parseMimic(tinyxml2::XMLElement* xml)
  {
    joint->mimic->clear();
    const char* joint_name_str = xml->Attribute("joint");
    if (joint_name_str == NULL)
    {
      LOG_F(ERROR, "joint mimic: no mimic joint specified");
      return false;
    }
    else
      joint->mimic->joint_name = std::string(joint_name_str);
     const char* multiplier_str = xml->Attribute("multiplier");

    if (multiplier_str == NULL)
    {
      LOG_F(WARNING,"joint mimic: no multiplier, using default value of 1");
      joint->mimic->multiplier = static_cast<T>(1);
    }
    else
    {
      try {
        str2num<T>(multiplier_str,joint->mimic->multiplier);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "multiplier value (%s) is not a valid float", multiplier_str);
        return false;
      }
  }
    const char* offset_str = xml->Attribute("offset");
    if (offset_str == NULL)
    {
      LOG_F(WARNING,"joint mimic: no offset, using default value of 0");
      joint->mimic->offset = static_cast<T>(0.0) ;
    }
    else
    {
      try {
        str2num<T>(offset_str,joint->mimic->offset);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "offset value (%s) is not a valid float", offset_str);
        return false;
      }
    }
    return true;
  }
  
  template <typename T>
  bool JointParser<T>::parseType(tinyxml2::XMLElement *xml)
  {
    const char* type_char = xml->Attribute("type");
    if (!type_char)
    {
      LOG_F(ERROR, "joint [%s] has no type, check to see if it's a reference.", joint->name.c_str());
      return false;
    }
    std::string type_str(type_char);
    if      (type_str == "planar")     {joint->type = urdf::Joint<T>::Type::PLANAR;    return true;}
    else if (type_str == "floating")   {joint->type = urdf::Joint<T>::Type::FLOATING;  return true;}
    else if (type_str == "revolute")   {joint->type = urdf::Joint<T>::Type::REVOLUTE;  return true;}
    else if (type_str == "continuous") {joint->type = urdf::Joint<T>::Type::CONTINUOUS;return true;}
    else if (type_str == "prismatic")  {joint->type = urdf::Joint<T>::Type::PRISMATIC; return true;}
    else if (type_str == "fixed")      {joint->type = urdf::Joint<T>::Type::FIXED;     return true;}
    else
    {
      LOG_F(ERROR,"joint [%s] has no known type [%s]", joint->name.c_str(), type_str.c_str());
      return false; 
    }
    return false;
  };

  template <typename T>
  bool JointParser<T>::parseName(tinyxml2::XMLElement *xml)
  {
    const char *name = xml->Attribute("name");
    if (!name)
    {
      LOG_F(ERROR, "unnamed joint found");
      return false;
    }
    joint->name = std::string(name);
    return true;
  };

  template <typename T>
  bool JointParser<T>::parseParentChildLinks()
  {
    tinyxml2::XMLElement *parent_xml = this->config->FirstChildElement("parent");
    while (parent_xml)
    {
      const char* parent_str = parent_xml->Attribute("link");
      if (parent_str)
      {
        joint->parent_links_name.push_back(std::string(parent_str));
      }
      else
      {
        LOG_F(WARNING, " 'parent' element missing 'link' attribute.");
      }
      parent_xml = parent_xml->NextSiblingElement("parent");
    }
    tinyxml2::XMLElement *child_xml = this->config->FirstChildElement("child");
    while (child_xml)
    {
      const char* child_str = child_xml->Attribute("link");
      if (child_str)
      {
        joint->child_links_name.push_back(std::string(child_str));
      }
      else
      {
        LOG_F(WARNING, " 'child' element missing 'link' attribute." );
      }
      child_xml = child_xml->NextSiblingElement("child");
    }
    return true;
  }

  template <typename T>
  bool JointParser<T>::parseOrigins()
  {
    tinyxml2::XMLElement *origin_xml = this->config->FirstChildElement("origin");
    if (!origin_xml)
    {
      LOG_F(ERROR, " 'origin' element not found in joint configuration." );
      return false;
    }
    const char* origin_parent = origin_xml->Attribute("parent");
    if (origin_parent)
    {
      std::string parent_str(origin_parent);
      auto it = std::find(joint->parent_links_name.begin(), joint->parent_links_name.end(), parent_str);
      if (it != joint->parent_links_name.end())
      {
        try
        {
          urdf::Pose<T> pose(origin_xml);
          joint->parents_to_joint_origin_transform.push_back(pose);
        }
        catch (const std::exception& e)
        {
          LOG_F(ERROR, "Error parsing origin pose: %s", e.what() );
          return false;
        }
        return true;
      }
      else
      {
        LOG_F(ERROR, "specified parent '%s' in origin does not match any known parent links.",
        parent_str.c_str());
        return false;
      }
  }
  else
  {
    if (joint->parent_links_name.size() == 1)
    {
      try
      {
        urdf::Pose<T> pose(origin_xml);
        joint->parents_to_joint_origin_transform.push_back(pose);
      }
      catch (const std::exception& e)
      {
        LOG_F(ERROR, "parsing origin pose: %s " , e.what() );
        return false;
      }
      return true;
    }
    else if (joint->parent_links_name.empty())
    {
      LOG_F(ERROR, "No parent links found, but origin is defined without a reference.");
    }
    else
    {
      LOG_F(ERROR, 
      "Multiple parent links exist, but origin is defined without a reference." );
    }
    return false;
    }
    return false;
  };

  template <typename T>
  bool JointParser<T>::parseAxis(tinyxml2::XMLElement *xml)
  {
    if (joint->type != urdf::Joint<T>::Type::FLOATING && 
        joint->type != urdf::Joint<T>::Type::PLANAR && 
        joint->type != urdf::Joint<T>::Type::FIXED)
    {
        tinyxml2::XMLElement *axis_xml = config->FirstChildElement("axis");
        if (!axis_xml)
        {
            LOG_F(WARNING, "No axis element for JointParser link [%s], defaulting to (1,0,0) axis",
                  joint->name.c_str());
            joint->axis = math::Vec3<T>(1.0, 0.0, 0.0);
        }
        else
        {
            const char *xyz_str = axis_xml->Attribute("xyz");
            if (xyz_str)
            {
                std::istringstream stream(xyz_str);
                str2vec<T>(stream, joint->axis);
            }
        }
      return true;  
    }
    else
    {
      return false; 
    }
  }

  template <typename T>
  bool JointParser<T>::parse()
  {
    this->joint->clear();
    tinyxml2::XMLElement *xml_joint = config->FirstChildElement("joint");

    if (!parseName(xml_joint)) {
      return false;
    }
    if (!parseType(xml_joint)) {
      return false;
    }
    if (!parseParentChildLinks()) {
      return false;
    }
    if (!parseOrigins()) {
      return false;
    }
    tinyxml2::XMLElement *xml_axis = config->FirstChildElement("axis");
    if (!parseAxis(xml_axis)) {
      return false;
    }
    tinyxml2::XMLElement *xml_limit = config->FirstChildElement("limit");
    if (!parseLimits(xml_limit)) {
      return false;
    }
    tinyxml2::XMLElement *xml_safty = config->FirstChildElement("safety_controller");
    if (!parseSafety(xml_safty)) {
        return false;
    }
    tinyxml2::XMLElement *xml_calibration = config->FirstChildElement("calibration");
    if (!parseCalibration(xml_calibration)) {
      return false;
    }
    tinyxml2::XMLElement *xml_mimic = config->FirstChildElement("mimic");
    if (!parseMimic(xml_mimic)) {
      return false;
    }
    tinyxml2::XMLElement *xml_dynamics = config->FirstChildElement("dynamics");
    if (!parseDynamics(xml_dynamics)) {
      return false;
    }
    return true;
  };
  
  template <typename T>
  urdf::Joint<T>* JointParser<T>::getJoint() const
  {
    return joint.get();
  }
}; // namespace tinyurdf

template class tinyurdf::JointParser<double>;
template class tinyurdf::JointParser<float>;
template class tinyurdf::JointParser<long double>;