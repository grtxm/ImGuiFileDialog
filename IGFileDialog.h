#ifndef __IMGUI_EXT_FILE_DIALOG
#define __IMGUI_EXT_FILE_DIALOG

#ifdef FILEDLG_LIB_IMPORT
#define IG_LIB_API __declspec(dllimport)
#else
#define IG_LIB_API __declspec(dllexport)
#endif

extern "C" IG_LIB_API const char* IGGetFile();
extern "C" IG_LIB_API const char* IGGetDirectory();

#endif // !__IMGUI_FILE_DIALOG
