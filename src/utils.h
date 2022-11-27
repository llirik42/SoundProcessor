#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <map>

bool contains(const std::vector<std::string>& vector, const std::string& string);

size_t get_file_size(std::ifstream& file);

bool is_file_empty(std::ifstream& file);
