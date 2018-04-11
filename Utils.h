#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <tchar.h>

#include <vtkSmartPointer.h>
#include <vtkDirectory.h>
#include <vtksys/SystemTools.hxx>

extern void getFiles(std::string path, std::vector<std::string>& files);
extern bool DeleteDirectory(LPCTSTR lpszDir, bool noRecycleBin = true);
