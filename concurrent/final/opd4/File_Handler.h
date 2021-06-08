#pragma once
#ifndef FILE_HANDLER_H 
#define FILE_HANDLER_H

#include <fstream>
#include <filesystem>
#include <iostream>
#include <chrono>
#include <mutex>
#include "Entry.h"

namespace fs = std::filesystem;
class FileHandler
{
public:


	FileHandler(Entry new_entry);
	FileHandler(std::vector<Entry> new_entries);
	~FileHandler();

	std::ifstream src;
	std::ofstream dest;

	void write_file(std::string file_url);
	void copy_file(std::string src_url, std::string dst_url);

	std::vector<fs::path> find_directories(fs::path p, std::string keyword);

	void find_keywords(std::vector<std::string> kw);


private:
	std::mutex prnt_mtx;
	std::vector<Entry> entries;
};

#endif