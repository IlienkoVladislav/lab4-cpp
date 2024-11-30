#ifndef FILEREADBENCHMARK_H
#define FILEREADBENCHMARK_H

#include <string>

void benchmarkWithFopen(const std::wstring& filePath);

void benchmarkWithWindowsAPI(const std::wstring& filePath);

#endif // FILEREADBENCHMARK_H
