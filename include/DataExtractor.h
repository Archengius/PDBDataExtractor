#pragma once

#include "DataExtractorConfig.h"
#include "DataExtractorResult.h"
#include "Utils/DiaUtils.h"

class DataExtractor
{
    DataExtractorConfig Config;
public:
    explicit DataExtractor(const DataExtractorConfig& InConfig);

    DataExtractorResult ExtractDataFromDatabase(const CComPtr<IDiaSymbol>& GlobalSymbol) const;
    static DataExtractorTypeDataResult ExtractTypeDataFromUDT(const CComPtr<IDiaSymbol>& UDTSymbol, const DataExtractorTypeDefinition& TypeDefinition);
};
