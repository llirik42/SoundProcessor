#pragma once

#include <string>
#include "utils.h"

class WAVFile{
public:
    explicit WAVFile(const std::string& file_path);

    [[nodiscard]] size_t get_duration_s() const;
    [[nodiscard]] Sample get_sample() const;
    [[nodiscard]] size_t get_samples_count() const;

    ~WAVFile();
private:
    struct Imple;
    Imple* _pimple;
};
