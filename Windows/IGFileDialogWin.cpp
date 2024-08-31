#include "../IGFileDialog.h"
#include <windows.h>
#include <commdlg.h>
#include <string>
#include <atlstr.h> 
#include <shlobj.h> 


std::string CStringToString(const CString& cstr) {
	std::string result;

#ifdef UNICODE
	int len = WideCharToMultiByte(CP_ACP, 0, cstr.GetString(), -1, NULL, 0, NULL, NULL);
	if (len > 0) {
		char* buffer = new char[len];
		WideCharToMultiByte(CP_ACP, 0, cstr.GetString(), -1, buffer, len, NULL, NULL);
		result = buffer;
		delete[] buffer;
	}
#else
	result = cstr.GetString();
#endif

	return result;
}

const char* IGGetFile() {
	//thread un safe
	static std::string file_path;
	OPENFILENAME ofn;
	TCHAR  fileName[MAX_PATH] = L"";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = _T("All files (.)\0*.*\0");
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrTitle = _T("Select a file");

	if (GetOpenFileName(&ofn)) {
		file_path = CStringToString(   fileName);
		
	}
	else
	{
		file_path = "";
	}
	return file_path.c_str();
}

const char* IGGetDirectory() {
	//thread un safe
	static std::string dir_path;
	BROWSEINFO bi;
	TCHAR szDisplayName[MAX_PATH] = { 0 };
	TCHAR szTitle[] = _T("Select a folder");
	TCHAR szPath[MAX_PATH] = { 0 };

	ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDisplayName;
	bi.lpszTitle = szTitle;
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl != NULL) {
		SHGetPathFromIDList(pidl, szPath);
		dir_path = CStringToString(szPath);
		IMalloc* imalloc = NULL;
		if (SUCCEEDED(SHGetMalloc(&imalloc)) && imalloc) {
			imalloc->Free(pidl);
			imalloc->Release();
		}
	}
	else
	{
		dir_path = "";
	}
	return dir_path.c_str();
}

