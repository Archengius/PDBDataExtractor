#pragma once

#include <string>
#include <map>
#include <nlohmann/json.hpp>
#include <filesystem>

struct DataExtractorTypeDataResult
{
    size_t TypeSize{0};
    std::map<std::string, int32_t> MemberOffsets;
    std::map<std::string, int32_t> VirtualFunctionOffsets;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataExtractorTypeDataResult, TypeSize, TypeSize, MemberOffsets, VirtualFunctionOffsets);
};

struct DataExtractorResult
{
    std::map<std::string, DataExtractorTypeDataResult> Types;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataExtractorResult, Types);

    bool WriteToFile(const std::filesystem::path& OutputFilePath);
};
