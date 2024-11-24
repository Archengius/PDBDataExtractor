#include "DataExtractorConfig.h"
#include <fstream>
#include <iostream>

bool DataExtractorConfigManager::LoadConfigFrom(const std::filesystem::path& FilePath)
{
    // Attempt to open the file for reading
    std::ifstream FileInputStream{FilePath};
    if (!FileInputStream.good())
    {
        std::cerr << "Failed to open config file for reading: " << FilePath << std::endl;
        return false;
    }

    // Read the file as JSON
    nlohmann::json ParsedJson;
    try
    {
        ParsedJson = nlohmann::json::parse(FileInputStream);
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Failed to parse config file as valid JSON: " << Exception.what() << std::endl;
        return false;
    }

    // Convert the resulting JSON to our structure
    try
    {
        ParsedJson.get_to(ExtractorConfig);
    } catch (const std::exception& Exception)
    {
        std::cerr << "Failed to convert config JSON to a valid configuration: " << Exception.what() << std::endl;
        return false;
    }
    return true;
}
