#include "Settings_Manager.h"


using namespace sm;
void to_json(json& j, const Entry& e) {
	j = json{ "Entry", 
		{ {"loc_name", e.loc_name},
		{"src_dir", e.src_directory},
		{"dst_dir", e.dst_directory},
		{"keywords", e.keywords},
		{"extensions", e.extensions},
		{"sort_files", e.sort_files},
		{"sort_dir", e.sort_dir} }
	};
}

void from_json(json& j, Entry& e) {
	j.at("loc_name").get_to(e.loc_name);
	j.at("src_dir").get_to(e.src_directory);
	j.at("dst_dir").get_to(e.dst_directory);
	j.at("keywords").get_to(e.keywords);
	j.at("extensions").get_to(e.extensions);
	j.at("sort_files").get_to(e.sort_files);
	j.at("sort_dir").get_to(e.sort_dir);
};


void Settings_Manager::create_loc() {
	std::cout << j_object.dump(4) << std::endl;

	json new_entry;
	Entry e;

	std::string new_loc_name;
	std::cout << "Insert new location name:" << std::endl;
	std::cin >> new_loc_name;

	std::string src_dir;
	std::cout << "Set the source directory:" << std::endl;
	std::cin >> src_dir;

	std::string dest_dir;
	std::cout << "Set the destination directory" << std::endl;
	std::cin >> dest_dir;

	e.loc_name = new_loc_name;
	e.src_directory = src_dir;
	e.dst_directory = dest_dir;

	std::vector<std::string>new_keywords = add_keywords();
	std::vector<std::string>new_extensions = add_extensions();  //std::vector<std::string>()

	e.keywords = new_keywords;
	e.extensions = new_extensions;

	bool sort_on_files = set_active("Files");
	bool sort_on_dir = set_active("Directories");

	e.sort_files = sort_on_files;
	e.sort_dir = sort_on_dir;

	to_json(new_entry, e);

	j_object.insert(j_object.end(),new_entry.begin(),new_entry.end());

	update_settings(j_object);
	show_settings(j_object);
}

void Settings_Manager::remove_loc() {};



std::vector<std::string> Settings_Manager::add_keywords() {
	std::vector<std::string> new_kw;
	std::string input = "";
	std::cout << "Add new keywords to filter files and/or directories on, type \"exit()\" when done:" << std::endl;
	while (input != "exit()")
	{
		try {
			std::cin >> input;
			if (input != "exit()") {
				new_kw.push_back(std::string(input));
			}
		}
		catch (std::exception e) {
			std::cout << "Something went wrong" << std::endl;
			std::cout << "Input has not been processed" << std::endl;
		}
	}

	return new_kw;
};
void Settings_Manager::remove_keywords() {

};

std::vector<std::string> Settings_Manager::add_extensions() {
	std::vector<std::string> new_ex;
	std::string input = "";
	std::cout << "Add new extensions to filter on, type \"exit()\" when done:" << std::endl;
	while (input != "exit()")
	{
		try {
			std::cin >> input;
			if (input != "exit()") {
				new_ex.push_back(std::string(input));
			}
		}
		catch (std::exception e) {
			std::cout << "Something went wrong" << std::endl;
			std::cout << "Input has not been processed" << std::endl;
		}
	}

	return new_ex;
};
void Settings_Manager::remove_extensions() {};

void Settings_Manager::update_settings(json& j) {
	try {
		setting_out.open("settings.json");
		setting_out << std::setw(4) << j_object << std::endl;
		setting_out.close();
	}
	catch (std::exception e) {
		std::cout << "Not able to update settings" << std::endl;
	}
};

void Settings_Manager::show_settings(json& j) {
	std::cout << j.dump(4) << std::endl;
};


bool Settings_Manager::set_active(std::string option) {
	bool temp = false;
	char answer;
	bool isvalid = false;
	while (!isvalid) {
		std::cout << "Would you like to filter " << option << "? (y or n):" << std::endl;
		try {
			std::cin >> answer;
		}
		catch (std::exception e) {
			std::cout << "Please enter a valid character" << std::endl;
		}
		if (char(answer) == 'y' || char(answer) ==  'n') {
			temp = (answer == 'y') ? true : false;
			isvalid = true;
		}
	}
	return temp;
};


Settings_Manager::Settings_Manager()
{
	if (fs::exists("settings.json")) {
		try {
			setting_in.open("settings.json");
			setting_in >> j_object;
			setting_in.close();
		}
		catch (std::exception e) {
			std::cout << "Could not open settings, exiting" << std::endl;
			exit(1);
			//this -> ~Settings_Manager();
		}
	}
	else {
		std::cout << "Couldn't find settings.json, creating new settings file" << std::endl;
		setting_out.open("settings.json");
		j_object = { {} };
		std::cout << j_object << std::endl;
		setting_out << std::setw(4) << j_object << std::endl;
		setting_out.close();
	}

}

Settings_Manager::~Settings_Manager()
{
	if (setting_in.is_open()) {
		setting_in.close();
	}

	if (setting_out.is_open()) {
		setting_out.close();
	}

}
