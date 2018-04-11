#include "Utils.h"

using namespace std;

void getFiles(string path, vector<string> &files) {
	vtkSmartPointer<vtkDirectory> directory = vtkSmartPointer<vtkDirectory>::New();
	int opened = directory->Open(path.c_str());
	if (!opened) {
		std::cout << "Invalid directory!" << std::endl;
		return;
	}
	int numberOfFiles = directory->GetNumberOfFiles();
	for (int i = 0; i < numberOfFiles; i++) {
		if (!directory->FileIsDirectory(directory->GetFile(i)))
			files.push_back(directory->GetFile(i));
	}
}

bool DeleteDirectory(LPCTSTR lpszDir, bool noRecycleBin) {
	int len = _tcslen(lpszDir);
	TCHAR *pszFrom = new TCHAR[len + 2];
	_tcscpy(pszFrom, lpszDir);
	pszFrom[len] = 0;
	pszFrom[len + 1] = 0;

	SHFILEOPSTRUCT fileop;
	fileop.hwnd = NULL;    // no status display
	fileop.wFunc = FO_DELETE;  // delete operation
	fileop.pFrom = pszFrom;  // source file name as double null terminated string
	fileop.pTo = NULL;    // no destination needed
	fileop.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;  // do not prompt the user

	if (!noRecycleBin)
		fileop.fFlags |= FOF_ALLOWUNDO;

	fileop.fAnyOperationsAborted = FALSE;
	fileop.lpszProgressTitle = NULL;
	fileop.hNameMappings = NULL;

	int ret = SHFileOperation(&fileop);
	delete[] pszFrom;
	return (ret == 0);
}
