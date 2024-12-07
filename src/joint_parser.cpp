#include "joint_parser.hpp"

namespace tinyurdf{

  template <typename T>
  JointParser<T>::JointParser()
  {

  }

  template <typename T>
  JointParser<T>::JointParser(tinyxml2::XMLElement *config_)
  {
  }

  template <typename T>
  JointParser<T>::JointParser(const JointParser &rhs)
  {
  }

  template <typename T>
  JointParser<T>::~JointParser()
  {

  }

  template <typename T>
  bool JointParser<T>::parseJointDynamics(tinyxml2::XMLElement* xml)
  {
    jd->clear();
    const char* damping_str = xml->Attribute("damping");
    if (damping_str == NULL){
      LOG_F(WARNING,"no damping, defaults to 0");
      jd->damping = static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(damping_str, jd->damping);
      } catch(std::runtime_error &) {
        LOG_F(ERROR, "damping value (%s) is not a valid float", damping_str);
        return false;
      }
    }
    const char* friction_str = xml->Attribute("friction");
    if (friction_str == NULL){
      LOG_F(WARNING, "no friction, defaults to 0");
      jd.friction = 0;
    }
    else
    {
      try {
        str2num<T>(friction_str, jd->friction);
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
  bool JointParser<T>::parseJointLimits(tinyxml2::XMLElement* xml)
  {
    jl.clear();
    const char* lower_str = xml->Attribute("lower");
    if (lower_str == NULL){
      LOG_F(WARNING,"joint_limit: no lower, defaults to 0");
      jl->lower = static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(lower_str, jd->lower);
      } catch (std::runtime_error &) {
         LOG_F(ERROR, "lower value (%s) is not a valid float", lower_str);
        return false;
      }
    }
    const char* upper_str = xml->Attribute("upper");
    if (upper_str == NULL){
      LOG_F(WARNING,"urdfdom.joint_limit: no upper, , defaults to 0");
      jl->upper =static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(upper_str, jd->upper);
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
        str2num<T>(effort_str, jd->effort);
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
        str2num<T>(velocity_str, jd->velocity);
      } catch(std::runtime_error &) {
         LOG_F(ERROR,"velocity value (%s) is not a valid float", velocity_str);
        return false;
      }
    }
    return true;
  };

  template <typename T>
  bool JointParser<T>::parseJointSafety(tinyxml2::XMLElement* xml)
  {
    js.clear();
    const char* soft_lower_limit_str = xml->Attribute("soft_lower_limit");
    if (soft_lower_limit_str == NULL)
    {
      LOG_F(WARNING,"joint_safety: no soft_lower_limit, using default value");
      js->soft_lower_limit =static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(soft_lower_limit_str, jd->soft_lower_limit);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "soft_lower_limit value (%s) is not a valid float", soft_lower_limit_str);
        return false;
      }
    }
    const char* soft_upper_limit_str = xml->Attribute("soft_upper_limit");
    if (soft_upper_limit_str == NULL)
    {
      LOG_F(WARNING,"urdfdom.joint_safety: no soft_upper_limit, using default value");
      js->soft_upper_limit = static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(soft_upper_limit_str, jd->soft_upper_limit);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "soft_upper_limit value (%s) is not a valid float", soft_upper_limit_str);
        return false;
      }
    }
    const char* k_position_str = xml->Attribute("k_position");
    if (k_position_str == NULL)
    {
      LOG_F(WARNING,"joint_safety: no k_position, using default value");
      js->k_position = static_cast<T>(0.0);
    }
    else
    {
      try {
        str2num<T>(k_position_str, jd->k_position);
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
        str2num<T>(k_velocity_str, jd->k_velocity);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "k_velocity value (%s) is not a valid float", k_velocity_str);
        return false;
      }
    }
    return true;
  };

  template <typename T>
  bool JointParser<T>::parseJointCalibration(tinyxml2::XMLElement* xml)
  {
    jc->clear();
    const char* rising_position_str = xml->Attribute("rising");
    if (rising_position_str == NULL)
    {
      LOG_F(WARNING,"joint_calibration: no rising, using default value");
      jc.rising.reset();
    }
    else
    {
      try {
        T* ricing_position = new T;
        str2num<T>(ricing_position, ricing_position);
        jc.falling.reset(ricing_position);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "rising value (%s) is not a valid float", rising_position_str);
        return false;
      }
    }
    const char* falling_position_str = xml->Attribute("falling");
    if (falling_position_str == NULL)
    {
      LOG_F(WARNING,"urdfdom.joint_calibration: no falling, using default value");
      jc.falling.reset();
    }
    else
    {
      try {
        T* falling_position = new T;
        str2num<T>(falling_position_str, falling_position);
        jc.falling.reset(falling_position);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "falling value (%s) is not a valid float", falling_position_str);
        return false;
      }
    }
    return true;
  };

  template <typename T>
  bool JointParser<T>::parseJointMimic(tinyxml2::XMLElement* xml)
  {
    jm->clear();
    const char* joint_name_str = xml->Attribute("joint");
    if (joint_name_str == NULL)
    {
      LOG_F(ERROR, "joint mimic: no mimic joint specified");
      return false;
    }
    else
      jm.joint_name = std::string(joint_name_str);
    const char* multiplier_str = xml->Attribute("multiplier");

    if (multiplier_str == NULL)
    {
      LOG_F(WARNING,"urdfdom.joint_mimic: no multiplier, using default value of 1");
      jm->multiplier = static_cast<T>(1);
    }
    else
    {
      try {
        str2num<T>(multiplier_str,jm->multiplier);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "multiplier value (%s) is not a valid float", multiplier_str);
        return false;
      }
  }
    const char* offset_str = xml->Attribute("offset");
    if (offset_str == NULL)
    {
      LOG_F(WARNING,"joint_mimic: no offset, using default value of 0");
      jm.offset = static_cast<T>(0.0) ;
    }
    else
    {
      try {
        str2num<T>(offset_str,jm->offset);
      } catch(std::runtime_error &) {
         LOG_F(ERROR, "offset value (%s) is not a valid float", offset_str);
        return false;
      }
    }
    return true;
  }

  template <typename T>
  bool JointParser<T>::parse()
  {
    joint.clear();
    const char *name = config->Attribute("name");
    if (!name)
    {
      LOG_F(ERROR, "unnamed joint found");
      return false;
    }
    joint->name = name;
    tinyxml2::XMLElement *origin_xml = config->FirstChildElement("origin");
    if (!origin_xml)
    {
      LOG_F(WARNING,
      "JointParser [%s] missing origin tag under parent describing transform from Parent Link to JointParser Frame, (using Identity transform).", joint.name.c_str());
      joint.parent_to_joint_origin_transform.clear();
    }
    else
    {
      if (!parsePoseInternal(joint.parent_to_joint_origin_transform, origin_xml))
      {
        joint.parent_to_joint_origin_transform.clear();
         LOG_F(ERROR, "Malformed parent origin element for joint [%s]", joint.name.c_str());
        return false;
      }
    }
    tinyxml2::XMLElement *parent_xml = config->FirstChildElement("parent");
    if (parent_xml)
    {
      const char *pname = parent_xml->Attribute("link");
      if (!pname)
      {
        LOG_F(WARNING, "no parent link name specified for JointParser link [%s]. this might be the root?",
         joint.name.c_str());
      }
      else
      {
        joint.parent_link_name = std::string(pname);
      }
    }
    tinyxml2::XMLElement *child_xml = config->FirstChildElement("child");
    if (child_xml)
    {
      const char *pname = child_xml->Attribute("link");
      if (!pname)
      {
        CONSOLE_BRIDGE_logInform("no child link name specified for JointParser link [%s].", joint.name.c_str());
      }
      else
      {
        joint.child_link_name = std::string(pname);
      }
    }
    const char* type_char = config->Attribute("type");
    if (!type_char)
    {
      LOG_F(ERROR, "joint [%s] has no type, check to see if it's a reference.", joint.name.c_str());
      return false;
    }
    std::string type_str = type_char;
    if (type_str == "planar")
      joint.type = JointParser::PLANAR;
    else if (type_str == "floating")
      joint.type = JointParser::FLOATING;
    else if (type_str == "revolute")
      joint.type = JointParser::REVOLUTE;
    else if (type_str == "continuous")
      joint.type = JointParser::CONTINUOUS;
    else if (type_str == "prismatic")
      joint.type = JointParser::PRISMATIC;
    else if (type_str == "fixed")
      joint.type = JointParser::FIXED;
    else
    {
       LOG_F(ERROR, "JointParser [%s] has no known type [%s]", joint.name.c_str(), type_str.c_str());
      return false;
    }
    if (joint.type != Type::FLOATING && joint.type != JointParser::FIXED)
    {
      tinyxml2::XMLElement *axis_xml = config->FirstChildElement("axis");
      if (!axis_xml){
        LOG_F(WARNING,"urdfdom: no axis element for JointParser link [%s], defaulting to (1,0,0) axis", joint.name.c_str());
        joint.axis = Vector3(1.0, 0.0, 0.0);
      }
      else{
        if (axis_xml->Attribute("xyz")){
          try {
            joint.axis.init(axis_xml->Attribute("xyz"));
          }
          catch (ParseError &e) {
            joint.axis.clear();
             LOG_F(ERROR, "Malformed axis element for joint [%s]: %s", joint.name.c_str(), e.what());
            return false;
          }
        }
      }
    }
    tinyxml2::XMLElement *limit_xml = config->FirstChildElement("limit");
    if (limit_xml)
    {
      joint.limits.reset(new JointLimits());
      if (!parseJointLimits(*joint.limits, limit_xml))
      {
         LOG_F(ERROR, "Could not parse limit element for joint [%s]", joint.name.c_str());
        joint.limits.reset();
        return false;
      }
    }
    else if (joint.type == JointParser::REVOLUTE)
    {
      LOG_F(ERROR, "JointParser [%s] is of type REVOLUTE but it does not specify limits", joint.name.c_str());
      return false;
    }
    else if (joint.type == JointParser::PRISMATIC)
    {
      LOG_F(ERROR, "JointParser [%s] is of type PRISMATIC without limits", joint.name.c_str());
      return false;
    }
    tinyxml2::XMLElement *safety_xml = config->FirstChildElement("safety_controller");
    if (safety_xml)
    {
      joint.safety.reset(new JointSafety());
      if (!parseJointSafety(*joint.safety, safety_xml))
      {
        LOG_F(ERROR, "Could not parse safety element for joint [%s]", joint.name.c_str());
        joint.safety.reset();
        return false;
      }
    }
    tinyxml2::XMLElement *calibration_xml = config->FirstChildElement("calibration");
    if (calibration_xml)
    {
      joint.calibration.reset(new JointCalibration());
      if (!parseJointCalibration(*joint.calibration, calibration_xml))
      {
        LOG_F(ERROR, "Could not parse calibration element for joint  [%s]", joint.name.c_str());
        joint.calibration.reset();
        return false;
      }
    }
    tinyxml2::XMLElement *mimic_xml = config->FirstChildElement("mimic");
    if (mimic_xml)
    {
      joint.mimic.reset(new JointMimic());
      if (!parseJointMimic(*joint.mimic, mimic_xml))
      {
        LOG_F(ERROR, "Could not parse mimic element for joint  [%s]", joint.name.c_str());
        joint.mimic.reset();
        return false;
      }
    }

    tinyxml2::XMLElement *prop_xml = config->FirstChildElement("dynamics");
    if (prop_xml)
    {
      joint.dynamics.reset(new JointDynamics());
      if (!parseJointDynamics(*joint.dynamics, prop_xml))
      {
        LOG_F(ERROR, "Could not parse joint_dynamics element for joint [%s]", joint.name.c_str());
        joint.dynamics.reset();
        return false;
      }
    }
    return true;
  };
/**
  template <typename T>
  bool JointParser<T>::exportPose(urdf::Pose<T> &pose)
  {
      return false;
  }

  template <typename T>
  bool tinyurdf::JointParser<T>::exportJointDynamics(tinyxml2::XMLElement *xml)
  {
    tinyxml2::XMLElement *dynamics_xml = xml->GetDocument()->NewElement("dynamics");
    dynamics_xml->SetAttribute("damping", urdf_export_helpers::values2str(jd.damping).c_str() );
    dynamics_xml->SetAttribute("friction", urdf_export_helpers::values2str(jd.friction).c_str() );
    xml->LinkEndChild(dynamics_xml);
    return true;
  }

  template <typename T>
  bool tinyurdf::JointParser<T>::exportJointLimits(tinyxml2::XMLElement *xml)
  {
    tinyxml2::XMLElement *limit_xml = xml->GetDocument()->NewElement("limit");
    limit_xml->SetAttribute("effort", urdf_export_helpers::values2str(jl.effort).c_str());
    limit_xml->SetAttribute("velocity", urdf_export_helpers::values2str(jl.velocity).c_str());
    limit_xml->SetAttribute("lower", urdf_export_helpers::values2str(jl.lower).c_str());
    limit_xml->SetAttribute("upper", urdf_export_helpers::values2str(jl.upper).c_str());
    xml->LinkEndChild(limit_xml);
    return true;
  }

  template <typename T>
  bool tinyurdf::JointParser<T>::exportJointSafety(tinyxml2::XMLElement *xml)
  {
    tinyxml2::XMLElement *safety_xml = xml->GetDocument()->NewElement("safety_controller");
    safety_xml->SetAttribute("k_position", urdf_export_helpers::values2str(js.k_position).c_str());
    safety_xml->SetAttribute("k_velocity", urdf_export_helpers::values2str(js.k_velocity).c_str());
    safety_xml->SetAttribute("soft_lower_limit", urdf_export_helpers::values2str(js.soft_lower_limit).c_str());
    safety_xml->SetAttribute("soft_upper_limit", urdf_export_helpers::values2str(js.soft_upper_limit).c_str());
    xml->LinkEndChild(safety_xml);
    return true;
  }

  template <typename T>
  bool tinyurdf::JointParser<T>::exportJointCalibration(tinyxml2::XMLElement *xml)
  {
      if (jc.falling || jc.rising)
    {
      tinyxml2::XMLElement *calibration_xml = xml->GetDocument()->NewElement("calibration");
      if (jc.falling)
        calibration_xml->SetAttribute("falling", urdf_export_helpers::values2str(*jc.falling).c_str());
      if (jc.rising)
        calibration_xml->SetAttribute("rising", urdf_export_helpers::values2str(*jc.rising).c_str());
      //calibration_xml->SetAttribute("reference_position", urdf_export_helpers::values2str(jc.reference_position) );
      xml->LinkEndChild(calibration_xml);
    }
    return true;
  }

  template <typename T>
  bool tinyurdf::JointParser<T>::exportJointMimic(tinyxml2::XMLElement *xml)
  {
    if (!jm.joint_name.empty())
    {
      tinyxml2::XMLElement *mimic_xml = xml->GetDocument()->NewElement("mimic");
      mimic_xml->SetAttribute("offset", urdf_export_helpers::values2str(jm.offset).c_str());
      mimic_xml->SetAttribute("multiplier", urdf_export_helpers::values2str(jm.multiplier).c_str());
      mimic_xml->SetAttribute("joint", jm.joint_name.c_str());
      xml->LinkEndChild(mimic_xml);
    }
    return true;
  }

  template <typename T>
  bool tinyurdf::JointParser<T>::export2xml(tinyxml2::XMLElement *xml)
  {
      tinyxml2::XMLElement * joint_xml = xml->GetDocument()->NewElement("joint");
    joint_xml->SetAttribute("name", joint.name.c_str());
    if (joint.type == urdf::JointParser::PLANAR)
      joint_xml->SetAttribute("type", "planar");
    else if (joint.type == urdf::JointParser::FLOATING)
      joint_xml->SetAttribute("type", "floating");
    else if (joint.type == urdf::JointParser::REVOLUTE)
      joint_xml->SetAttribute("type", "revolute");
    else if (joint.type == urdf::JointParser::CONTINUOUS)
      joint_xml->SetAttribute("type", "continuous");
    else if (joint.type == urdf::JointParser::PRISMATIC)
      joint_xml->SetAttribute("type", "prismatic");
    else if (joint.type == urdf::JointParser::FIXED)
      joint_xml->SetAttribute("type", "fixed");
    else
       LOG_F(ERROR, "ERROR:  JointParser [%s] type [%d] is not a defined type.\n",joint.name.c_str(), joint.type);

    // origin
    exportPose(joint.parent_to_joint_origin_transform, joint_xml);

    // axis
    tinyxml2::XMLElement * axis_xml = joint_xml->GetDocument()->NewElement("axis");
    axis_xml->SetAttribute("xyz", urdf_export_helpers::values2str(joint.axis).c_str());
    joint_xml->LinkEndChild(axis_xml);

    // parent
    tinyxml2::XMLElement * parent_xml = joint_xml->GetDocument()->NewElement("parent");
    parent_xml->SetAttribute("link", joint.parent_link_name.c_str());
    joint_xml->LinkEndChild(parent_xml);

    // child
    tinyxml2::XMLElement * child_xml = joint_xml->GetDocument()->NewElement("child");
    child_xml->SetAttribute("link", joint.child_link_name.c_str());
    joint_xml->LinkEndChild(child_xml);

    if (joint.dynamics)
      exportJointDynamics(*(joint.dynamics), joint_xml);
    if (joint.limits)
      exportJointLimits(*(joint.limits), joint_xml);
    if (joint.safety)
      exportJointSafety(*(joint.safety), joint_xml);
    if (joint.calibration)
      exportJointCalibration(*(joint.calibration), joint_xml);
    if (joint.mimic)
      exportJointMimic(*(joint.mimic), joint_xml);

    xml->LinkEndChild(joint_xml);
    return true;
  }
  */
}; // namespace tinyurdf