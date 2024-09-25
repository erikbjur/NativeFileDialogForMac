cmake_minimum_required(VERSION 3.10)

############## MAC LIBRARY AND TEST APP ########################

# Set the project name
project(FileDialogs VERSION 1.0)

# Enable Objective-C++ support
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARY_NAME FileDialogLibrary)

set(APPLICATION_NAME FileDialogApp)

# Set the output directories for the targets
set( OutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OutputDir}/${LIBRARY_NAME}/static_libs )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OutputDir}/${APPLICATION_NAME})

if (APPLE)
  # Add the source files for the static library
  set(LIBRARY_SOURCES
      Library/Mac/src/FileDialogs.mm
  )

  # Create a static library
  add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES})

  # Link Cocoa framework to the static library
  find_library(COCOA_LIBRARY Cocoa)
  target_link_libraries(${LIBRARY_NAME} PRIVATE ${COCOA_LIBRARY})

  # Add the main.cpp file for the test application
  add_executable(${APPLICATION_NAME} MACOSX_BUNDLE Application/Mac/src/main.cpp)

  # Link the library and Cocoa framework to the executable
  target_link_libraries(${APPLICATION_NAME} PRIVATE ${LIBRARY_NAME} ${COCOA_LIBRARY})

  # Include directories (so that main.cpp can find FileDialogs.h)
  target_include_directories(${APPLICATION_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Library/Mac/src)

  # Set the app's Info.plist for macOS
  set_target_properties(${APPLICATION_NAME} PROPERTIES
      MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Application/Mac/src/Info.plist"
  )

############## WINDOWS LIBRARY AND TEST APP ########################
elseif(WIN32)

  # Add the source files for the static library
  set(LIBRARY_SOURCES
      Library/Windows/src/FileDialogs.cpp
  )

  # Create a static library
  add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES})

  # Link windows Win32 framework to the static library
  #find_library(WIN32_LIBRARY win32 REQUIRED)
  #target_link_libraries(${LIBRARY_NAME} PRIVATE ${WIN32_LIBRARY})

  # Add the main.cpp file for the test application
  add_executable(${APPLICATION_NAME} Application/Windows/src/main.cpp)

  # Link the library and Windows API dependencies to the executable
  target_link_libraries(${APPLICATION_NAME} PRIVATE ${LIBRARY_NAME})

  # Include directories (so that main.cpp can find FileDialogs.h)
  target_include_directories(${APPLICATION_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Library/Windows/src)

else()
    message(FATAL_ERROR "Unsupported platform")
endif()
