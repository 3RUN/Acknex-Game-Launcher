
// checks if given directory exists or not
BOOL DirectoryExists(char *szPath)
{
    DWORD dwAttrib = GetFileAttributes(_chr(szPath));
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

// return your computer's the documents folder
STRING *get_documents_folder()
{
    char *documents_path[MAX_PATH]; // MAX_PATH = 260 characters

    // if we are using windows Vista and above ?
    // then use SHGetFolderPath instead of SHGetSpecialFolderPath
    if (sys_winversion >= 6)
    {
        SHGetFolderPath(NULL, CSIDL_PERSONAL, 0, NULL, documents_path);
    }
    else
    {
        SHGetSpecialFolderPath(NULL, _chr(documents_path), CSIDL_PERSONAL, FALSE);
    }
    return _str(documents_path);
}

// returns the full path to your game folder (which is in your PC's documents folder)
STRING *get_savedir_folder()
{
    STRING *game_save_directory = "#260"; // 260 characters = MAX_PATH
    str_cpy(game_save_directory, get_documents_folder());
    str_cat(game_save_directory, "\\");
    str_cat(game_save_directory, project_name_str);
    str_cat(game_save_directory, "\\");
    return game_save_directory;
}

// this function will create game's folder in documents folder
void savedir_create_folder()
{
    // set new save directory
    str_cpy(save_dir, get_savedir_folder());

    // check if directory exists or not
    // and if it doesn't, create it !
    if (!DirectoryExists(save_dir))
    {
        CreateDirectory(_chr(save_dir), NULL);
    }
}