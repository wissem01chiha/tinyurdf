#ifndef LINK_EXPORTER_H
#define LINK_EXPORTER_H

#include <memory>
#include <nlohmann/json.hpp>
#include <loguru/loguru.hpp>
#include <tinyxml2/tinyxml2.h>
#include "urdf_utilities.h"
#include "urdf_exporter.h"
#include "link.h"

namespace tinyurdf {

    template< typename T = double >
    class LinkJsonExporter : public URDFExporter
    {
        public:
            LinkJsonExporter();

            bool exportData(nlohmann::json* json);
            
            std::string getFormatName() const = 0;

        private:
            bool exportDynamics(nlohmann::json* json);
            bool exportLimits(nlohmann::json* json);
            bool exportSafety(nlohmann::json* json);
            bool exportCalibration(nlohmann::json* json);
            bool exportMimic(nlohmann::json* json);

            std::shared_ptr<urdf::Link<T>>   link;
    };


    template< typename T = double >
    class LinkProtoExporter : public URDFExporter
    {
        public:
            LinkProtoExporter();

            bool exportData();
            
            std::string getFormatName() const = 0;

        private:
            bool exportDynamics();
            bool exportLimits();
            bool exportSafety();
            bool exportCalibration();
            bool exportMimic();

            std::shared_ptr<urdf::Link<T>>   link;
    };

    template< typename T = double >
    class LinkYamlExporter : public URDFExporter
    {
        public:
            LinkYamlExporter();

            bool exportData();
            
            std::string getFormatName() const = 0;

        private:
            bool exportDynamics();
            bool exportLimits();
            bool exportSafety();
            bool exportCalibration();
            bool exportMimic();

            std::shared_ptr<urdf::Link<T>>   link;
    };
}; // namespace tinyurdf 
#endif // LINK_EXPORTER_H