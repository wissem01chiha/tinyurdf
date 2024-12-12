#ifndef URDF_RENDER_VTK
#define URDF_RENDER_VTK

#include <memory>

#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPLYReader.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkUnsignedCharArray.h>
#include <vtkPointData.h>
#include <vtkAppendPolyData.h>
#include <vtkSmartPointer.h>

#include "urdf_version.h"
#include "model_interface.h"
#include "urdf_parser.h"
#include "world_parser.h"

namespace tinyurdf
{
    /// @brief main rendering interface using VTK for visualization.
    class vtkURDFRender
    {
    public:
        /// @brief constructor from a URDF model or file.
        explicit vtkURDFRender(const std::string &path = "");
        
        /// @brief constructor given an explict model 
        explicit vtkURDFRender(const urdf::Model<> &model);

        /// @brief constructor from an explicit model interface 
        explicit vtkURDFRender(std::shared_ptr<urdf::ModelInterface<>> interface_ptr);

        /// @brief render the model 
        void render() const;

        // rendering options
        bool displayFrames      = false;
        bool displayLinks       = true;
        bool displayJoints      = true;
        bool displayWorld       = false;
        bool displayTransform   = false;
        bool displayMarkups     = true;
        bool displayLinkNames   = true;
        bool displayJointNames  = true;
        bool displayFrameNames  = true;
        bool displayCollisions  = true;

    private:
        urdf::ModelInterface<> interface;
        urdf::Model<> model;
    };
}; // namespace tinyurdf
#endif // URDF_RENDER_VTK