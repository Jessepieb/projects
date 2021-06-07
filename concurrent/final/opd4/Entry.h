#pragma once
#ifndef ENTRY_H 
#define ENTRY_H

#include "json.hpp"

using json = nlohmann::json;

struct Entry {
	std::string loc_name;
	std::string src_directory;
	std::string dst_directory;
	std::vector<std::string> keywords;
	std::vector<std::string> extensions;
	bool sort_files;
	bool sort_dir;

};

void to_json(json& j, const Entry& e);
Entry from_json(json& j);



#endif