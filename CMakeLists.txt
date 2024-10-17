cmake_minimum_required(VERSION 3.16)
project(sudocul_solver_api)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(express-cpp
        GIT_REPOSITORY https://github.com/antwxne/express-cpp.git
        GIT_TAG master
        GIT_PROGRESS TRUE
)
FetchContent_GetProperties(express-cpp)
if (NOT express-cpp_POPULATED)
    FetchContent_Populate(express-cpp)
endif ()
add_subdirectory(${express-cpp_SOURCE_DIR})
include_directories(${express-cpp_SOURCE_DIR}/Sources)


FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

SET(BIN_NAME sudocul_solver_api)
include_directories(./Sources)
SET(SOURCES ./Sources/Main.cpp
./Sources/Solve.cpp
./Sources/Tools/Exec.cpp
)

add_executable(${BIN_NAME} ${SOURCES})
target_link_libraries(${BIN_NAME} PRIVATE express-cpp)
target_link_libraries(${BIN_NAME} PRIVATE nlohmann_json::nlohmann_json)

