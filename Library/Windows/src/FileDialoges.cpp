#include "FileDialogs.h"
#include <commdlg.h> // For file dialogs
#include <windows.h>

std::string openFileDialog() {
  char filename[MAX_PATH] = "";

  OPENFILENAME ofn; // Structure to hold dialog settings
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = NULL; // Set to NULL for console apps
  ofn.lpstrFile = filename;
  ofn.nMaxFile = MAX_PATH;
  ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";
  ofn.nFilterIndex = 1;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  if (GetOpenFileName(&ofn)) {
    return std::string(filename); // Return selected file path
  }
  return ""; // If no file is selected or dialog is canceled
}

std::string saveFileDialog() {
  char filename[MAX_PATH] = "";

  OPENFILENAME ofn; // Structure to hold dialog settings
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = NULL; // Set to NULL for console apps
  ofn.lpstrFile = filename;
  ofn.nMaxFile = MAX_PATH;
  ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";
  ofn.nFilterIndex = 1;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

  if (GetSaveFileName(&ofn)) {
    return std::string(filename); // Return selected file path
  }
  return ""; // If dialog is canceled
}
