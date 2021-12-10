#ifndef _SAVEDIR_H_
#define _SAVEDIR_H_

// this is needed for SHGetSpecialFolderPath function
// to return (quote from microsoft documents - Windows CE 5.0):
// "file system directory that serves as a common repository for documents"
#define CSIDL_PERSONAL 0x0005

// this one I've found over the web
// it needed for the DirectoryExists function
const long INVALID_FILE_ATTRIBUTES = -1;

// get folder path function for Vista and above (thanks to Emre)
HRESULT WINAPI SHGetFolderPath(HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwFlags, char *pszPath);
#define PRAGMA_API SHGetFolderPath;Shell32.dll!SHGetFolderPathA

// checks if given directory exists or not
BOOL DirectoryExists(char *szPath);

// return your computer's the documents folder
STRING *get_documents_folder();

// returns the full path to your game folder (which is in your PC's documents folder)
STRING *get_savedir_folder();

// this function will create game's folder in documents folder
void savedir_create_folder();

#endif