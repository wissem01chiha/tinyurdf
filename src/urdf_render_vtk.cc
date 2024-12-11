#include "urdf_render_vtk.h"

namespace tinyurdf {

    template <typename T>
    vtkLinkRender<T>::vtkLinkRender()
    {
    }

    template <typename T>
    vtkLinkRender<T>::vtkLinkRender(const urdf::Link<T> link_)
    {
    }

    template <typename T>
    vtkLinkRender<T>::vtkLinkRender(std::shared_ptr<urdf::Link<T>> link_ptr)
    {
    }

    template <typename T>
    void vtkLinkRender<T>::render()
    {
    }

}; // namespace tinyurdf {