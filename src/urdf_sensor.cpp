
/* Author: John Hsu */


#include <fstream>
#include <sstream>
#include <algorithm>


namespace urdf{


bool parseCamera(Camera &camera, TiXmlElement* config)
{
  camera.clear();
  camera.type = VisualSensor::CAMERA;

  TiXmlElement *image = config->FirstChildElement("image");
  if (image)
  {
    const char* width_char = image->Attribute("width");
    if (width_char)
    {
      try
      {
        camera.width = boost::lexical_cast<unsigned int>(width_char);
      }
      catch (boost::bad_lexical_cast &e)
      {
        logError("Camera image width [%s] is not a valid int: %s", width_char, e.what());
        return false;
      }
    }
    else
    {
      logError("Camera sensor needs an image width attribute");
      return false;
    }

    const char* height_char = image->Attribute("height");
    if (height_char)
    {
      try
      {
        camera.height = boost::lexical_cast<unsigned int>(height_char);
      }
      catch (boost::bad_lexical_cast &e)
      {
        logError("Camera image height [%s] is not a valid int: %s", height_char, e.what());
        return false;
      }
    }
    else
    {
      logError("Camera sensor needs an image height attribute");
      return false;
    }

    const char* format_char = image->Attribute("format");
    if (format_char)
      camera.format = std::string(format_char);
    else
    {
      logError("Camera sensor needs an image format attribute");
      return false;
    }    

    const char* hfov_char = image->Attribute("hfov");
    if (hfov_char)
    {
      try
      {
        camera.hfov = boost::lexical_cast<double>(hfov_char);
      }
      catch (boost::bad_lexical_cast &e)
      {
        logError("Camera image hfov [%s] is not a valid float: %s", hfov_char, e.what());
        return false;
      }
    }
    else
    {
      logError("Camera sensor needs an image hfov attribute");
      return false;
    }

    const char* near_char = image->Attribute("near");
    if (near_char)
    {
      try
      {
        camera.near = boost::lexical_cast<double>(near_char);
      }
      catch (boost::bad_lexical_cast &e)
      {
        logError("Camera image near [%s] is not a valid float: %s", near_char, e.what());
        return false;
      }
    }
    else
    {
      logError("Camera sensor needs an image near attribute");
      return false;
    }

    const char* far_char = image->Attribute("far");
    if (far_char)
    {
      try
      {
        camera.far = boost::lexical_cast<double>(far_char);
      }
      catch (boost::bad_lexical_cast &e)
      {
        logError("Camera image far [%s] is not a valid float: %s", far_char, e.what());
        return false;
      }
    }
    else
    {
      logError("Camera sensor needs an image far attribute");
      return false;
    }
    
  }
  else
  {
    logError("Camera sensor has no <image> element");
    return false;
  }
  return true;
}



 


}


