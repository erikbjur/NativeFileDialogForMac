# Intro
This is a library and test application to use the native file open and file save dialog windows in mac osx and windows.

# Building Library and Test Application
```bash
cd build
cmake --build .
```

# Adding this library to your app
Add this CMakeLists.txt file to your 3rd Party Libraries folder -> This Library Folder.
```
add_subdirectory( nativefiledialogs )
```