#include "Main.h"

namespace fs = std::filesystem;

//std::multimap<std::string, std::string> criteria;
//std::multimap<std::string, std::string>::iterator it;

//criteria.insert(std::pair<std::string, std::string>("Python", "python"));

//for (it = criteria.begin(); it != criteria.end(); it++)
//{
//	std::cout << (*it).first << "\t" << (*it).second << std::endl;
//}


class FileHandler {
public:
	std::ifstream src;
	std::ofstream dest;
	FileHandler() {};

	void write_file(std::string file_url) {
		dest.open(file_url);
		if (dest.is_open()) {
			dest << "Testing File Creation\n";
			dest << "and adding several lines, making preparations for thread implementation\n";
		}
		dest.close();

	}

	void copy_file(std::string src_url, std::string dest_url) {
		std::string line;
		
		src.open(src_url);
		dest.open(dest_url);

		if (src.is_open() && dest.is_open()) {
		while (std::getline(src, line)) {
			std::cout << line << std::endl;
			dest << line << std::endl;
		}
	}
			src.close();
			dest.close();
	}

	void find_keywords() {

	}

private:
	
	
};

std::string tolowerString(std::string text) {
	std::string newString;
	std::transform(text.begin(), text.end(),std::back_inserter(newString), (int(*)(int))std::tolower);
	std::cout << newString << std::endl;
	return newString;
}

class Settings_Manager
{
	using json = nlohmann::json;
public:
	Settings_Manager();
	~Settings_Manager();

	void create_loc() {};
	void remove_loc() {};

	void add_keywords() {};
	void remove_keywords() {};

	void add_extensions() {};
	void remove_extensions() {};

private:
	json j_object;
	std::ifstream setting_in;
	std::ofstream setting_out;
};

Settings_Manager::Settings_Manager()
{
	if (fs::exists("settings.json")) {
		setting_in.open("settings.json");
		setting_in >> j_object;
		std::cout << j_object.dump(4);
	}
	else {
		std::cout << "Couldn't find settings.json, creating new settings file" << std::endl;
		setting_out.open("settings.json");
		j_object = { {"locations",{}} };
		std::cout << j_object << std::endl;
		setting_out << std::setw(4) << j_object << std::endl;
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


int main() {

	Settings_Manager sm;

	FileHandler fh;
	fh.write_file("text.txt");
	fh.copy_file("text.txt", "text2.txt");

	int counter = 0;

	for (auto& i : fs::directory_iterator("D:/Github/projects/concurrent/final/opd4"))
	{
		if (i.is_regular_file()) {
			std::cout << i.path().filename() << std::endl;
			std::string::size_type pos = i.path().string().find(tolowerString("TeXt"));
			if (pos != std::string::npos) {
				std::cout << "Contains keyword!\n";
			}
			counter++;
		}	
	}

	std::cout << "amount of files in directory: " << counter << std::endl;
}