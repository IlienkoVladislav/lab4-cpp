#include "utils.h"
#include <windows.h>

bool fileExists(const std::wstring& filePath) {
    DWORD fileAttrib = GetFileAttributesW(filePath.c_str());
    return (fileAttrib != INVALID_FILE_ATTRIBUTES && !(fileAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
