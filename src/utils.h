#pragma once

#include <fstream>
#include <string>

size_t get_file_size(std::fstream& file);

bool is_file_empty(std::fstream& file);

std::string generate_random_wav_file_name();

void copy_file(std::string_view from, std::string_view to);

void rename_file(std::string_view old_name, std::string new_name);
