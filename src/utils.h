#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <map>

size_t get_file_size(std::ifstream& file);

bool contains(const std::vector<std::string>& vector, const std::string& string);

bool is_file_empty(std::ifstream& file);

//void write_default_wav_headers(std::ofstream& file, size_t samples_count);

/*
void write_sample(std::ofstream& file, Sample sample);
*/
void copy_file(const std::string& to, const std::string& from);
