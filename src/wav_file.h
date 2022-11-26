#pragma once

#include <string>

class WAVFile{
public:
    explicit WAVFile(const std::string& file_path);
    ~WAVFile();
private:
    struct Impl;
    Impl* _pimpl;
};