#pragma once
#ifndef SETTING_MANAGER_H 
#define SETTING_MANAGER_H
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

#include "json.hpp"
using json = nlohmann::json;
namespace fs = std::filesystem;

struct Entry {
	std::string loc_name;
	std::string src_directory;
	std::string dst_directory;
	std::vector<std::string> keywords;
	std::vector<std::string> extensions;
	bool sort_files;
	bool sort_dir;

	void to_json(json& j, const Entry e);
	void from_json(json& j, const Entry e);

};

namespace sm {
	class Settings_Manager
	{
	public:

		json j_object;
		std::ifstream setting_in;
		std::ofstream setting_out;

		Settings_Manager();
		~Settings_Manager();

		void create_loc();
		void remove_loc();

		void create_keywords(std::vector<std::string>& cur_kw);
		void remove_keywords();

		void create_extensions(std::vector<std::string>& cur_ex);
		void remove_extensions();

		void update_settings(json& j);
		void show_settings(json& j);

	private:

		bool set_active(std::string option);

	};
};
#endif