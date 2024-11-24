#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <set>

struct DataExtractorTypeDefinition
{
    std::string TypeName;
    std::set<std::string> MemberNames;
    std::set<std::string> VirtualFunctionNames;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataExtractorTypeDefinition, TypeName, MemberNames, VirtualFunctionNames);
};

struct DataExtractorConfig
{
    std::vector<DataExtractorTypeDefinition> TypeDefinitions;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataExtractorConfig, TypeDefinitions);
};

class DataExtractorConfigManager
{
    DataExtractorConfig ExtractorConfig{};
public:
    [[nodiscard]] const DataExtractorConfig& GetConfig() const { return ExtractorConfig; }

    bool LoadConfigFrom(const std::filesystem::path& FilePath);
};
