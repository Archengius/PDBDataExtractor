## PDB Data Extractor

A command line tool to extract data from the PDB files into a portable JSON format.

Usage:
``PDBDataExtractor <PDBFilePath> <ConfigFilePath> <OutputFilePath>``

### Example Configuration File

```json
{
  "TypeDefinitions":
  [
    {
      "TypeName": "FMalloc",
      "MemberNames": [],
      "VirtualFunctionNames": [
        "Malloc",
        "Free",
        "Realloc"
      ]
    },
    {
      "TypeName": "FName",
      "MemberNames": [
        "ComparisonIndex",
        "DisplayIndex",
        "Number"
      ],
      "VirtualFunctionNames": []
    },
    {
      "TypeName": "UObjectBase",
      "MemberNames": [
        "NamePrivate",
        "ClassPrivate",
        "OuterPrivate",
        "InternalIndex",
        "ObjectFlags"
      ],
      "VirtualFunctionNames": []
    }
  ]
}
```

### Example Tool Output

```json
{
  "Types": {
    "FMalloc": {
      "MemberOffsets": {},
      "TypeSize": 8,
      "VirtualFunctionOffsets": {
        "Free": 64,
        "Malloc": 32,
        "Realloc": 48
      }
    },
    "FName": {
      "MemberOffsets": {
        "ComparisonIndex": 0,
        "Number": 4
      },
      "TypeSize": 8,
      "VirtualFunctionOffsets": {}
    },
    "UObjectBase": {
      "MemberOffsets": {
        "ClassPrivate": 16,
        "InternalIndex": 12,
        "NamePrivate": 24,
        "ObjectFlags": 8,
        "OuterPrivate": 32
      },
      "TypeSize": 40,
      "VirtualFunctionOffsets": {}
    }
  }
}
```
