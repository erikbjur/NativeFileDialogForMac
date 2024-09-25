#include "FileDialogs.h"
#include <iostream>

int main()
{
  // Open file dialog
  std::string openPath = NativeFileDialog::openFileDialog();
  if( !openPath.empty() ) {
    std::cout << "File chosen: " << openPath << std::endl;
  } else {
    std::cout << "No file selected." << std::endl;
  }

  // Save file dialog
  std::string savePath = NativeFileDialog::saveFileDialog();
  if( !savePath.empty() ) {
    std::cout << "File to save at: " << savePath << std::endl;
  } else {
    std::cout << "Save cancelled." << std::endl;
  }

  return 0;
}
