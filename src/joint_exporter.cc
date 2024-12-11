#include "joint_exporter.h"

namespace tinyurdf
{
    template<typename T>
    JointJsonExporter<T>::JointJsonExporter()
    {   
    }

    template <typename T>
    bool JointJsonExporter<T>::exportData(nlohmann::json *json)
    {
        return false;
    }

    template <typename T>
    bool JointJsonExporter<T>::exportDynamics(nlohmann::json *json)
    {
        return false;
    }

} // namespace tinyurdf
