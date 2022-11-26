#pragma once

#include <fstream>

size_t get_file_size(std::ifstream& file);
bool is_file_empty(std::ifstream& file);
