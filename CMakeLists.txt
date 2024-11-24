cmake_minimum_required(VERSION 3.28)
project(PDBDataExtractor)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp )
string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} SYSTEM_PROCESSOR_LOWERCASE)

add_executable(PDBDataExtractor ${SOURCE_FILES} )
target_include_directories(PDBDataExtractor PUBLIC include)

# DIA SDK dependency
target_include_directories(PDBDataExtractor PRIVATE dependencies/DIA_SDK/include)
target_link_libraries(PDBDataExtractor PRIVATE ${CMAKE_CURRENT_LIST_DIR}/dependencies/DIA_SDK/lib/${SYSTEM_PROCESSOR_LOWERCASE}/diaguids.lib)

# nlohmann-json dependency
add_subdirectory(dependencies/nlohmann-json)
target_link_libraries(PDBDataExtractor PRIVATE nlohmann_json::nlohmann_json)