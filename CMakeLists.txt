# General

cmake_minimum_required(VERSION 3.12)

project(NPuzzle)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

# Computer library

set(SourcesDir ${CMAKE_CURRENT_SOURCE_DIR}/Sources)

file(GLOB ComputerSources   ${SourcesDir}/Parser.hpp
                            ${SourcesDir}/Parser.cpp
                            ${SourcesDir}/Solver.hpp
                            ${SourcesDir}/Solver.cpp
                            ${SourcesDir}/Simplifier.hpp
                            ${SourcesDir}/Simplifier.cpp
                            ${SourcesDir}/Chunk.hpp
                            ${SourcesDir}/Shower.hpp
                            ${SourcesDir}/Shower.cpp
                            ${SourcesDir}/Utils.hpp
)

add_library(Computer STATIC ${ComputerSources})

# Run executable

set(RunnerDir ${CMAKE_CURRENT_SOURCE_DIR}/Runner)
file(GLOB RunnerSources ${RunnerDir}/main.cpp)

add_executable(Run ${RunnerSources})

target_link_libraries(Run Computer)

target_include_directories(Run PUBLIC ${SourcesDir})

# RunTests executable

set(TestsDir ${CMAKE_CURRENT_SOURCE_DIR}/Tests)
file(GLOB TestsSources          ${TestsDir}/main.cpp
                                ${TestsDir}/Parser.cpp
                                ${TestsDir}/Solver.cpp
                                ${TestsDir}/Simplifier.cpp
                                ${TestsDir}/Utils.cpp
)

add_executable(RunTests ${TestsSources})

target_link_libraries(RunTests Computer)

target_include_directories(RunTests PUBLIC ${SourcesDir})
