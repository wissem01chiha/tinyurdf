
/* Author: John Hsu */

#include <fstream>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <tinyxml2.h>


namespace urdf{

bool parseModelState(ModelState &ms, tinyxml2::XMLElement* config)
{
  ms.clear();

  const char *name_char = config->Attribute("name");
  if (!name_char)
  {
    CONSOLE_BRIDGE_logError("No name given for the model_state.");
    return false;
  }
  ms.name = std::string(name_char);

  const char *time_stamp_char = config->Attribute("time_stamp");
  if (time_stamp_char)
  {
    try {
      ms.time_stamp.set(strToDouble(time_stamp_char));
    } catch(std::runtime_error &) {
      CONSOLE_BRIDGE_logError("Parsing time stamp [%s] failed", time_stamp_char);
      return false;
    }
  }

  tinyxml2::XMLElement *joint_state_elem = config->FirstChildElement("joint_state");
  if (joint_state_elem)
  {
    JointStateSharedPtr joint_state;
    joint_state.reset(new JointState());

    const char *joint_char = joint_state_elem->Attribute("joint");
    if (joint_char)
      joint_state->joint = std::string(joint_char);
    else
    {
      CONSOLE_BRIDGE_logError("No joint name given for the model_state.");
      return false;
    }


    const char *position_char = joint_state_elem->Attribute("position");
    if (position_char)
    {

      std::vector<std::string> pieces;
      urdf::split_string( pieces, position_char, " ");
      for (unsigned int i = 0; i < pieces.size(); ++i){
        if (pieces[i] != ""){
          try {
            joint_state->position.push_back(strToDouble(pieces[i].c_str()));
          } catch(std::runtime_error &) {
            throw ParseError("position element ("+ pieces[i] +") is not a valid float");
          }
        }
      }
    }

    const char *velocity_char = joint_state_elem->Attribute("velocity");
    if (velocity_char)
    {

      std::vector<std::string> pieces;
      urdf::split_string( pieces, velocity_char, " ");
      for (unsigned int i = 0; i < pieces.size(); ++i){
        if (pieces[i] != ""){
          try {
            joint_state->velocity.push_back(strToDouble(pieces[i].c_str()));
          } catch(std::runtime_error &) {
            throw ParseError("velocity element ("+ pieces[i] +") is not a valid float");
          }
        }
      }
    }

    // parse effort
    const char *effort_char = joint_state_elem->Attribute("effort");
    if (effort_char)
    {

      std::vector<std::string> pieces;
      urdf::split_string( pieces, effort_char, " ");
      for (unsigned int i = 0; i < pieces.size(); ++i){
        if (pieces[i] != ""){
          try {
            joint_state->effort.push_back(strToDouble(pieces[i].c_str()));
          } catch(std::runtime_error &) {
            throw ParseError("effort element ("+ pieces[i] +") is not a valid float");
          }
        }
      }
    }

    // add to vector
    ms.joint_states.push_back(joint_state);
  }
  return false;
}



}
