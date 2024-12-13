#ifndef JOINT_EXPORTER_H
#define JOINT_EXPORTER_H

#include <vector>
#include <memory>
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <loguru/loguru.hpp>
#include <tinyxml2/tinyxml2.h>
#include "urdf_utilities.h"
#include "urdf_exporter.h"
#include "urdf_version.h"
#include "joint.h"
#include "pose.h"

namespace tinyurdf {

    /// @brief json port exporter 
    template< typename T = double >
    class JointJsonExporter : public URDFExporter
    {
        public:
            JointJsonExporter();

            bool exportData(nlohmann::json* json);
            
            std::string getFormatName() const = 0;

        private:
            bool exportDynamics(nlohmann::json* json);
            bool exportLimits(nlohmann::json* json);
            bool exportSafety(nlohmann::json* json);
            bool exportCalibration(nlohmann::json* json);
            bool exportMimic(nlohmann::json* json);

            std::shared_ptr<urdf::Joint<T>>   joint;
    };

    /// @brief protobuffer port exporter
    template< typename T = double >
    class JointProtoExporter : public URDFExporter
    {
        public:
            JointProtoExporter();

            bool exportData();
            
            std::string getFormatName() const = 0;

        private:
            bool exportDynamics();
            bool exportLimits();
            bool exportSafety();
            bool exportCalibration();
            bool exportMimic();

            std::shared_ptr<urdf::Joint<T>>   joint;
    };

    /// @brief yaml port exporter
    template< typename T = double >
    class JointYamlExporter : public URDFExporter
    {
        public:
            JointYamlExporter();

            bool exportData();
            
            std::string getFormatName() const = 0;

        private:
            bool exportDynamics();
            bool exportLimits();
            bool exportSafety();
            bool exportCalibration();
            bool exportMimic();

            std::shared_ptr<urdf::Joint<T>>   joint;
    };
}; // namespace tinyurdf 
#endif // JOINT_EXPORTER_H