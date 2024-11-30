#include "getFileAttributes.h"
#include <windows.h>
#include <iostream>

void getFileAttributes(const std::wstring& filePath) {
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;

    if (!GetFileAttributesEx(filePath.c_str(), GetFileExInfoStandard, &fileInfo)) {
        std::wcerr << L"Failed to get file attributes. Error code: " << GetLastError() << std::endl;
        return;
    }

    std::wcout << L"=== File Attributes: " << filePath << L" ===" << std::endl;

    DWORD64 fileSize = (static_cast<DWORD64>(fileInfo.nFileSizeHigh) << 32) | fileInfo.nFileSizeLow;
    std::wcout << L"File Size: " << fileSize << L" bytes" << std::endl;

    FILETIME ftCreate = fileInfo.ftCreationTime;
    FILETIME ftAccess = fileInfo.ftLastAccessTime;
    FILETIME ftWrite = fileInfo.ftLastWriteTime;
    SYSTEMTIME stUTC, stLocal;

    FileTimeToSystemTime(&ftCreate, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
    std::wcout << L"Creation Time: " << stLocal.wDay << L"/" << stLocal.wMonth << L"/" << stLocal.wYear
        << L" " << stLocal.wHour << L":" << stLocal.wMinute << L":" << stLocal.wSecond << std::endl;

    FileTimeToSystemTime(&ftAccess, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
    std::wcout << L"Last Access Time: " << stLocal.wDay << L"/" << stLocal.wMonth << L"/" << stLocal.wYear
        << L" " << stLocal.wHour << L":" << stLocal.wMinute << L":" << stLocal.wSecond << std::endl;

    FileTimeToSystemTime(&ftWrite, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
    std::wcout << L"Last Modification Time: " << stLocal.wDay << L"/" << stLocal.wMonth << L"/" << stLocal.wYear
        << L" " << stLocal.wHour << L":" << stLocal.wMinute << L":" << stLocal.wSecond << std::endl;
}
