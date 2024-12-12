#include "urdf_render_vtk.h"

namespace tinyurdf {

    vtkURDFRender::vtkURDFRender(const std::string &path)
    {
    }

    vtkURDFRender::vtkURDFRender(const urdf::Model<> &model)
    {
    }

    vtkURDFRender::vtkURDFRender(std::shared_ptr<urdf::ModelInterface<>> interface_ptr)
    {

    }

    void vtkURDFRender::render() const
    {
    }

}; // namespace tinyurdf {