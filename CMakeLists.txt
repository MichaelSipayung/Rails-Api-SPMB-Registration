cmake_minimum_required (VERSION 3.8)
project ("StudentRailsApi")
find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
# Add source to this project's executable.
add_executable (main "main.cpp" "main.h")
target_link_libraries(main PRIVATE CURL::libcurl)
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)