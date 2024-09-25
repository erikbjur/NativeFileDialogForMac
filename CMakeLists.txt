cmake_minimum_required(VERSION 3.10)

############## MAC LIBRARY AND TEST APP ########################

# Set the project name
project(FileDialogs VERSION 1.1)

# Enable Objective-C++ support
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARY_NAME FileDialogLibrary)

set(APPLICATION_NAME FileDialogApp)

# Set the output directories for the targets
set( OutputDir ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OutputDir}/${LIBRARY_NAME}/static_libs )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OutputDir}/${APPLICATION_NAME} )

if (APPLE)
  # Add the source files for the static library
  set(LIBRARY_SOURCES
      Library/Mac/src/FileDialogs.mm
  )

  set(APPLICATION_SOURCES 
      Application/Mac/src/main.cpp
  )

  # Create a static library
  add_library( ${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES} )
  
  # Make sure there's no lib...prefixed on the library name
  set_target_properties( ${LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${LIBRARY_NAME} PREFIX "" )

  # Set the include directory for this library
  target_include_directories( ${LIBRARY_NAME} PUBLIC
    Library/Mac/src
  )

  # Link Cocoa framework to the static library
  find_library( COCOA_LIBRARY Cocoa )
  target_link_libraries( ${LIBRARY_NAME} PRIVATE ${COCOA_LIBRARY} )

  # Add the main.cpp file for the test application
  add_executable(${APPLICATION_NAME} MACOSX_BUNDLE ${APPLICATION_SOURCES})

  # Include directories (so that main.cpp can find FileDialogs.h)
  target_include_directories(${APPLICATION_NAME} PRIVATE
    Library/Mac/src
  )

  # Link the library and Cocoa framework to the executable
  target_link_libraries(${APPLICATION_NAME} PRIVATE ${LIBRARY_NAME} ${COCOA_LIBRARY})

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

  set(APPLICATION_SOURCES 
      Application/Windows/src/main.cpp
  )

  # Create a static library
  add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES})

  # Set the include directory for this library
  target_include_directories( ${LIBRARY_NAME} PUBLIC
    Library/Windows/src
  )

  # Link windows Win32 framework to the static library
  #find_library(WIN32_LIBRARY win32 REQUIRED)
  #target_link_libraries(${LIBRARY_NAME} PRIVATE ${WIN32_LIBRARY})

  # Add the main.cpp file for the test application
  add_executable(${APPLICATION_NAME} ${APPLICATION_SOURCES})

  # Link the library and Windows API dependencies to the executable
  target_link_libraries(${APPLICATION_NAME} PRIVATE ${LIBRARY_NAME})

  # Include directories (so that main.cpp can find FileDialogs.h)
  target_include_directories(${APPLICATION_NAME} PRIVATE
    Library/Windows/src
  )

else()
    message(FATAL_ERROR "Unsupported platform")
endif()
