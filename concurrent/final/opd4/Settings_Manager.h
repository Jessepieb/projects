#pragma once
#ifndef SETTING_MANAGER_H 
#define SETTING_MANAGER_H
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include "Entry.h"

#include "json.hpp"
using json = nlohmann::json;
namespace fs = std::filesystem;

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