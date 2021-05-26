#include "Main.h"
#include "File_Handler.h"
#include "Settings_Manager.h"
namespace fs = std::filesystem;

using json = nlohmann::json;

//class FileHandler {
//public:
//	std::ifstream src;
//	std::ofstream dest;
//	FileHandler() {};
//
//	void write_file(std::string file_url) {
//		dest.open(file_url);
//		if (dest.is_open()) {
//			dest << "Testing File Creation\n";
//			dest << "and adding several lines, making preparations for thread implementation\n";
//		}
//		dest.close();
//
//	}
//
//	void copy_file(std::string src_url, std::string dest_url) {
//		const auto copyOptions = fs::copy_options::overwrite_existing;
//		try {
//			fs::copy(src_url, dest_url, copyOptions);
//		}
//		catch (fs::filesystem_error err) {
//			std::cout << "failed to copy " << src_url << std::endl;
//			std::cout << err.code() << std::endl;
//		}
//	}
//
//	void find_keywords() {
//
//	}
//
//private:
//
//
//};

std::string tolowerString(std::string text) {
	std::string newString;
	std::transform(text.begin(), text.end(), std::back_inserter(newString), (int(*)(int))std::tolower);
	std::cout << newString << std::endl;
	return newString;
}

//namespace sm {
//	struct Entry {
//		std::string loc_name;
//		std::string src_directory;
//		std::string dst_directory;
//		std::vector<std::string> keywords;
//		std::vector<std::string> extensions;
//		bool sort_files;
//		bool sort_dir;
//
//	};
//
//	void to_json(json& j, const Entry& e) {
//		j = json{ {"loc_name", e.loc_name},
//			{"src_dir", e.src_directory},
//			{"dst_dir", e.dst_directory},
//			{"keywords", e.keywords},
//			{"extensions", e.extensions},
//			{"sort_files", e.sort_files},
//			{"sort_dir", e.sort_dir}
//		};
//	}
//
//	void from_json(json& j, Entry& e) {
//		j.at("loc_name").get_to(e.loc_name);
//		j.at("src_dir").get_to(e.src_directory);
//		j.at("dst_dir").get_to(e.dst_directory);
//		j.at("keywords").get_to(e.keywords);
//		j.at("extensions").get_to(e.extensions);
//		j.at("sort_files").get_to(e.sort_files);
//		j.at("sort_dir").get_to(e.sort_dir);
//	}
//}
//
//bool set_active(std::string option) {
//	bool temp = false;
//	char answer;
//	std::cout << "Would you like to filter " << option << "? (y or n):" << std::endl;
//	try {
//		std::cin >> answer;
//	}
//	catch (std::exception e) {
//		std::cout << "Please enter a character" << std::endl;
//	}
//	if (answer == ('y' || 'n')) {
//		temp = (answer == 'y') ? true : false;
//	}
//	return temp;
//}
//
//class Settings_Manager
//{
//
//
//public:
//	Settings_Manager();
//	~Settings_Manager();
//
//	void create_loc() {
//		std::cout << j_object.dump(4) << std::endl;
//
//		json new_entry;
//		sm::Entry e;
//
//		std::string new_loc_name;
//		std::cout << "Insert new location name:" << std::endl;
//		std::cin >> new_loc_name;
//
//		std::string src_dir;
//		std::cout << "Set the source directory:" << std::endl;
//		std::cin >> src_dir;
//
//		std::string dest_dir;
//		std::cout << "Set the destination directory" << std::endl;
//		std::cin >> dest_dir;
//
//		/*	new_loc = {
//				{new_loc_name, {
//					{"src_directory", src_dir},
//					{"dest_directory", dest_dir},
//					{"keywords", {}}
//				}
//				}
//			};*/
//
//		e.loc_name = new_loc_name;
//		e.src_directory = src_dir;
//		e.dst_directory = dest_dir;
//
//		std::vector<std::string>new_keywords = add_keywords();
//		std::vector<std::string>new_extensions = add_extensions();//std::vector<std::string>();
//
//		e.keywords = new_keywords;
//		e.extensions = new_extensions;
//
//		bool sort_on_files = set_active("Files");
//		bool sort_on_dir = set_active("Directories");
//
//		e.sort_files = sort_on_files;
//		e.sort_dir = sort_on_dir;
//
//		sm::to_json(new_entry, e);
//
//		show_settings(new_entry);
//
//		j_object.update(new_entry);
//
//		update_settings();
//		show_settings(j_object);
//	};
//	void remove_loc() {};
//
//	std::vector<std::string> add_keywords() {
//		std::vector<std::string> new_kw;
//		std::string input = "";
//		std::cout << "Add new keywords to filter files and/ or directories on, type \"exit()\" when done:" << std::endl;
//		while (input != "exit()")
//		{
//			try {
//				std::cin >> input;
//				if (input != "exit()") {
//					new_kw.push_back(std::string(input));
//				}
//			}
//			catch (std::exception e) {
//				std::cout << "Something went wrong" << std::endl;
//				std::cout << "Input has not been processed" << std::endl;
//			}
//		}
//
//		return new_kw;
//	};
//	void remove_keywords() {
//
//	};
//
//	std::vector<std::string> add_extensions() {
//		std::vector<std::string> new_ex;
//		std::string input = "";
//		std::cout << "Add new keywords to filter files and/ or directories on, type \"exit()\" when done:" << std::endl;
//		while (input != "exit()")
//		{
//			try {
//				std::cin >> input;
//				if (input != "exit()") {
//					new_ex.push_back(std::string(input));
//				}
//			}
//			catch (std::exception e) {
//				std::cout << "Something went wrong" << std::endl;
//				std::cout << "Input has not been processed" << std::endl;
//			}
//		}
//
//		return new_ex;
//	};
//	void remove_extensions() {};
//
//	void update_settings() {
//		try {
//			setting_out.open("settings.json");
//			setting_out << std::setw(4) << j_object << std::endl;
//		}
//		catch (std::exception e) {
//
//		}
//	};
//
//	void show_settings(json j) {
//		std::cout << j.dump(4) << std::endl;
//	};
//
//private:
//	json j_object;
//	std::ifstream setting_in;
//	std::ofstream setting_out;
//};
//
//Settings_Manager::Settings_Manager()
//{
//	if (fs::exists("settings.json")) {
//		try {
//			setting_in.open("settings.json");
//			setting_in >> j_object;
//		}
//		catch (std::exception e) {
//			std::cout << "Could not open settings, exiting...." << std::endl;
//			//this -> ~Settings_Manager();
//		}
//	}
//	else {
//		std::cout << "Couldn't find settings.json, creating new settings file" << std::endl;
//		setting_out.open("settings.json");
//		j_object = {};
//		std::cout << j_object << std::endl;
//		setting_out << std::setw(4) << j_object << std::endl;
//	}
//
//}
//
//Settings_Manager::~Settings_Manager()
//{
//	if (setting_in.is_open()) {
//		setting_in.close();
//	}
//
//	if (setting_out.is_open()) {
//		setting_out.close();
//	}
//
//}

using namespace fh;
using namespace sm;
int main() {

	Settings_Manager sm;

	FileHandler fh;
	//fh.write_file("sandbox/text.txt");
	//fh.copy_file("sandbox/text.txt", "sandbox/text2.txt");
	//fh.copy_file("Pictures/test_picture.jpg", "Pictures/copied_picture.jpg");
	//static_cast<void>(std::system("tree"));

	int counter = 0;

	for (auto& i : fs::directory_iterator("D:/Github/projects/concurrent/final/opd4"))
	{
		std::cout << i.path() << std::endl;

		if (i.is_directory()) {

		}
		else if (i.is_regular_file()) {

		}
		//if (i.is_regular_file()) {
		//	//std::cout << i.path().filename() << std::endl;
		//	std::string::size_type pos = i.path().string().find(tolowerString("TeXt"));
		//	if (pos != std::string::npos) {
		//		std::cout << "Contains keyword!\n";
		//	}
		//	counter++;
		//}	
	}
	std::cout << "amount of files in directory: " << counter << std::endl << std::endl;

	sm.create_loc();
}