#include "fileReadBenchmark.h"
#include <windows.h>
#include <iostream>
#include <cstdio>
#include <memory>
#include <ctime>

void benchmarkWithFopen(const std::wstring& filePath) {
    FILE* file;
    errno_t err = _wfopen_s(&file, filePath.c_str(), L"rb");
    if (err != 0 || file == nullptr) {
        std::wcerr << L"Failed to open file with _wfopen_s: " << filePath << std::endl;
        return;
    }

    const size_t bufferSize = 4096;
    std::unique_ptr<char[]> buffer(new char[bufferSize]);
    size_t bytesRead;
    size_t totalBytesRead = 0;

    std::clock_t start = std::clock();

    while ((bytesRead = fread(buffer.get(), 1, bufferSize, file)) > 0) {
        totalBytesRead += bytesRead;
    }

    std::clock_t end = std::clock();

    fclose(file);

    double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::wcout << L"fopen/fread: Read " << totalBytesRead << L" bytes in " << duration << L" seconds." << std::endl;
}

void benchmarkWithWindowsAPI(const std::wstring& filePath) {
    HANDLE file = CreateFileW(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Failed to open file with Windows API. Error: " << GetLastError() << std::endl;
        return;
    }

    const size_t bufferSize = 4096;
    std::unique_ptr<char[]> buffer(new char[bufferSize]);
    DWORD bytesRead;
    size_t totalBytesRead = 0;

    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    while (ReadFile(file, buffer.get(), bufferSize, &bytesRead, NULL) && bytesRead > 0) {
        totalBytesRead += bytesRead;
    }

    QueryPerformanceCounter(&end);

    CloseHandle(file);

    double duration = static_cast<double>(end.QuadPart - start.QuadPart) / freq.QuadPart;
    std::wcout << L"Windows API: Read " << totalBytesRead << L" bytes in " << duration << L" seconds." << std::endl;
}
