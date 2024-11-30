#include "getFileAttributes.h"
#include "fileReadBenchmark.h"
#include "asyncFileOperations.h"
#include "utils.h"
#include <iostream>
#include <vector>

int main() {
    std::wstring filePath = L"D:\\Univer\\cpp\\Lab4\\TestTask1.txt";

    std::wcout << L"Path length: " << filePath.length() << std::endl;
    std::wcout << L"Path content: [" << filePath << L"]" << std::endl;

    if (fileExists(filePath)) {
        std::wcout << L"File exists. Fetching attributes..." << std::endl;
        getFileAttributes(filePath);
    }
    else {
        std::wcerr << L"File does not exist: " << filePath << std::endl;
    }

    std::wstring largeFilePath = L"D:\\Univer\\cpp\\Lab4\\LargeTestFile.dat";
    std::wcout << L"Checking large file for reading: " << largeFilePath << std::endl;

    if (fileExists(largeFilePath)) {
        std::wcout << L"Large file exists. Starting benchmarks...\n";
        benchmarkWithFopen(largeFilePath);       
        benchmarkWithWindowsAPI(largeFilePath); 
    }
    else {
        std::wcerr << L"Large file does not exist: " << largeFilePath << std::endl;
    }

    std::vector<std::wstring> inputFiles = {
        L"D:\\Univer\\cpp\\Lab4\\Input1.txt",
        L"D:\\Univer\\cpp\\Lab4\\Input2.txt"
    };
    std::wstring outputFile = L"D:\\Univer\\cpp\\Lab4\\Output.txt";

    std::wcout << L"Processing files asynchronously...\n";
    processFilesAsync(inputFiles, outputFile);

    return 0;
}
