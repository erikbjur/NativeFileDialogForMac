#include "FileDialogs.h"
#import <Cocoa/Cocoa.h>

std::string openFileDialog() {
  @autoreleasepool {
    NSOpenPanel *panel = [NSOpenPanel openPanel];
    [panel setCanChooseFiles:YES];
    [panel setCanChooseDirectories:NO];
    [panel setAllowsMultipleSelection:NO];

    if ([panel runModal] == NSModalResponseOK) {
      NSURL *selectedFile = [[panel URLs] objectAtIndex:0];
      return std::string([[selectedFile path] UTF8String]);
    }
  }
  return "";
}

std::string saveFileDialog() {
  @autoreleasepool {
    NSSavePanel *panel = [NSSavePanel savePanel];

    if ([panel runModal] == NSModalResponseOK) {
      NSURL *selectedFile = [panel URL];
      return std::string([[selectedFile path] UTF8String]);
    }
  }
  return "";
}
