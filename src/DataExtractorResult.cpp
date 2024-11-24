#include "DataExtractorResult.h"
#include <fstream>
#include <iostream>

bool DataExtractorResult::WriteToFile(const std::filesystem::path& OutputFilePath)
{
    // Open the output file for write, and truncate it
    std::ofstream OutputFileStream{OutputFilePath, std::ios_base::out | std::ios_base::trunc};
    if (!OutputFileStream.good())
    {
        std::cerr << "Failed to open output file for write: " << OutputFilePath << std::endl;
        return false;
    }

    // Convert result to a valid JSON
    nlohmann::json OutputJson;
    nlohmann::to_json(OutputJson, *this);

    // Write JSON into the underlying file
    try
    {
        OutputFileStream.width(2);
        OutputFileStream << OutputJson;
        return true;
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Failed to write data extraction result to output file: " << Exception.what() << std::endl;
        return false;
    }
}
