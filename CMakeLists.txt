cmake_minimum_required(VERSION 3.10)

# Set the project name
project(FileDialogsApp)

# Enable Objective-C++ support
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the source files for the static library
set(LIBRARY_SOURCES
    src/FileDialogs.mm
)

set( OutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OutputDir}/${PROJECT_NAME}/static_libs )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OutputDir}/${PROJECT_NAME})

# Create a static library called 'filedialogs'
add_library(filedialogs STATIC ${LIBRARY_SOURCES})

# Link Cocoa framework to the static library
find_library(COCOA_LIBRARY Cocoa)
target_link_libraries(filedialogs PRIVATE ${COCOA_LIBRARY})

# Add the main.cpp file
add_executable(FileDialogsApp src/main.cpp)

# Link the filedialogs library and Cocoa framework to the executable
target_link_libraries(FileDialogsApp PRIVATE filedialogs ${COCOA_LIBRARY})

# Include directories (so that main.cpp can find FileDialogs.h)
target_include_directories(FileDialogsApp PRIVATE ${CMAKE_SOURCE_DIR}/src)
