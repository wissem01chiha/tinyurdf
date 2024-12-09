#ifndef URDF_EXPORTER_H
#define URDF_EXPORTER_H

#include <map>
#include <string>
#include <vector>

namespace tinyurdf {

  class URDFExporter {
    public:
      virtual ~URDFExporter() = default;
      virtual bool initialize(void* output) = 0;
      virtual bool exportData(void* output) = 0;
      virtual bool finalize(void* output) = 0;
      virtual std::string getFormatName() const = 0;
      virtual bool validate(void* output) = 0;
      virtual bool supportsCompression() const = 0;
      virtual bool setCompressionLevel(int level) = 0;
      virtual std::string exportStatus() const = 0;
      static std::vector<std::string> getSupportedFormats();
      virtual bool setConfiguration(const std::map<std::string, std::string>& config) = 0;
      virtual std::string getExportedData() const = 0;
      virtual bool supportsStreaming() const = 0;
  };

}; // namespace tinyurdf
#endif // URDF_EXPORTER_H