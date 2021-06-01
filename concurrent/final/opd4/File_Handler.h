#pragma once
#ifndef FILE_HANDLER_H 
#define FILE_HANDLER_H

#include <fstream>
#include <filesystem>
#include <iostream>
#include "Settings_Manager.h"

namespace fs = std::filesystem;
using namespace sm;
namespace fh {
	class FileHandler
	{
	public:

		FileHandler();
		FileHandler(Entry e);
		~FileHandler();

		std::ifstream src;
		std::ofstream dest;

		void write_file(std::string file_url);
		void copy_file(std::string src_url, std::string dst_url);

		void find_keywords();

		void start_loop(int id);

	private:

	};
}

#endif