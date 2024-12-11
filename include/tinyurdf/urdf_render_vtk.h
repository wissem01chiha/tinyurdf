#ifndef URDF_RENDER_VTK
#define URDF_RENDER_VTK

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
#include "pose.h"
#include "link.h"
#include "joint.h"
#include "world.h"

namespace tinyurdf
{
    // write a class for rendring an urdf Link object with many options
    template<typename T>
    class vtkLinkRender{

        public:
            /// @brief default constructor init an empty link with default geomtry
            /// and init vtk piplie attributs 
            vtkLinkRender();

            vtkLinkRender(const urdf::Link<T> link_);
            vtkLinkRender(std::shared_ptr<urdf::Link<T>> link_ptr);

            /// @brief display the object
            void render();

        private:

    };

    template<typename T>
    class vtkURDFRender
    {
        public:
    };


}; // namespace tinyurdf
#endif // URDF_RENDER_VTK


