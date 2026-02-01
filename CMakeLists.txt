cmake_minimum_required(VERSION 3.10)
project(FTK)

# Usa C++17 o superiore
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Includi la cartella degli header
include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/GeometricSamplig.cpp
    ${PROJECT_SOURCE_DIR}/src/ThreadPool.cpp
    ${PROJECT_SOURCE_DIR}/src/CsvHandler.cpp
)

# Eseguibile
add_executable(counting_tracks_eseguibile
    ${SOURCES}
    ${PROJECT_SOURCE_DIR}/apps/count_tracks.cpp
)

