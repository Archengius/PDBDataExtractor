#include "DataExtractor.h"
#include <iostream>
#include <Utils/StringUtils.h>
#include "DataExtractorResult.h"

DataExtractor::DataExtractor(const DataExtractorConfig& InConfig) : Config(InConfig)
{
}

DataExtractorResult DataExtractor::ExtractDataFromDatabase(const CComPtr<IDiaSymbol>& GlobalSymbol) const
{
    DataExtractorResult ExtractorResult;

    for (const DataExtractorTypeDefinition& TypeDefinition : Config.TypeDefinitions)
    {
        const std::wstring WideTypeName = StringUtf8ToWide(TypeDefinition.TypeName);
        DiaChildSymbolIterator TypeSymbolEnumerator(GlobalSymbol, SymTagUDT, WideTypeName.c_str());

        // Skip the definition if we did not find the symbol for it. This is not fatal
        if (TypeSymbolEnumerator.GetItemCount() == 0)
        {
            std::wcout << L"Skipping type definition " << WideTypeName << L" because no UDT symbol for it was found" << std::endl;
            continue;
        }

        // Print an error and skip the UDT if more than one symbol was found
        if (TypeSymbolEnumerator.GetItemCount() != 1)
        {
            std::wcerr << "Found multiple UDTs matching the type definition " << WideTypeName << L". " << TypeSymbolEnumerator.GetItemCount() << L" UDT symbols were found." << std::endl;
            throw std::exception("Found multiple UDT symbols matching the given type name");
        }

        const CComPtr<IDiaSymbol> UDTSymbol = *TypeSymbolEnumerator;
        DataExtractorTypeDataResult TypeDataResult = ExtractTypeDataFromUDT(UDTSymbol, TypeDefinition);

        ExtractorResult.Types.insert({TypeDefinition.TypeName, TypeDataResult});
    }
    return ExtractorResult;
}

DataExtractorTypeDataResult DataExtractor::ExtractTypeDataFromUDT(const CComPtr<IDiaSymbol>& UDTSymbol, const DataExtractorTypeDefinition& TypeDefinition)
{
    DataExtractorTypeDataResult DataResult;

    const ULONGLONG TypeSize = GET_SYMBOL_ATTRIBUTE_CHECKED(UDTSymbol, length);
    DataResult.TypeSize = static_cast<size_t>(TypeSize);

    for (DiaChildSymbolIterator ChildSymbolIterator(UDTSymbol); ChildSymbolIterator; ++ChildSymbolIterator)
    {
        const CComPtr<IDiaSymbol> ChildSymbol = *ChildSymbolIterator;
        const DWORD SymbolTypeTag = GET_SYMBOL_ATTRIBUTE_CHECKED(ChildSymbol, symTag);
        const DWORD SymbolLocationType = GET_SYMBOL_ATTRIBUTE_OR_DEFAULT(ChildSymbol, locationType);
        const std::wstring WideSymbolName = GET_SYMBOL_ATTRIBUTE_OR_DEFAULT(ChildSymbol, name);
        const bool bIsVirtualFunction = GET_SYMBOL_ATTRIBUTE_OR_DEFAULT(ChildSymbol, virtual);

        const std::string SymbolName = StringWideToUtf8(WideSymbolName);

        // If symbol is a this-relative data member we are looking for, write the offset
        if (SymbolTypeTag == SymTagData && SymbolLocationType == LocIsThisRel && TypeDefinition.MemberNames.contains(SymbolName))
        {
            const LONG ThisRelativeOffset = GET_SYMBOL_ATTRIBUTE_CHECKED(ChildSymbol, offset);
            DataResult.MemberOffsets.insert({SymbolName, static_cast<int32_t>(ThisRelativeOffset)});
        }
        // if symbol is a function that we are looking for, write the offset
        if (SymbolTypeTag == SymTagFunction && bIsVirtualFunction && TypeDefinition.VirtualFunctionNames.contains(SymbolName))
        {
            const DWORD VirtualTableOffset = GET_SYMBOL_ATTRIBUTE_CHECKED(ChildSymbol, virtualBaseOffset);
            DataResult.VirtualFunctionOffsets.insert({SymbolName, static_cast<int32_t>(VirtualTableOffset)});
        }
    }
    return DataResult;
}
