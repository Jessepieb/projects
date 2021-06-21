#include "File_Handler.h"

void FileHandler::write_file(std::string url) {
	dest.open(url);
	if (dest.is_open()) {
		dest << "Testing File Creation\n";
		dest << "and adding several lines, making preparations for thread implementation\n";
	}
	dest.close();
}

void FileHandler::copy_file(std::string src_url, std::string dst_url) {
	const auto copyOptions = fs::copy_options::overwrite_existing;
	try {
		fs::copy(src_url, dst_url, copyOptions);
	}
	catch (fs::filesystem_error err) {
		std::cout << "failed to copy " << src_url << std::endl;
		std::cout << err.code() << std::endl;
	}
}

//std::vector<fs::path> FileHandler::find_directories(fs::path p, std::string keyword) {
//	std::vector<fs::path> matched_directories;
//	return matched_directories;
//}

void FileHandler::start_loop(size_t id){
	std::lock_guard<std::mutex> prnt_lk(prnt_mtx);
	for (Entry e : entries) {
		std::cout << "message from Thread handling: " << e.loc_name << std::endl;
	}
}
void FileHandler::find_keywords() {
	for (Entry e : entries) {
		for (auto keyword : e.keywords) {
			for (auto path : fs::directory_iterator(e.src_directory)) {

			}
		}
	}
}


FileHandler::FileHandler(Entry new_entry) {
	entries.push_back(new_entry);
}

FileHandler::FileHandler(std::vector<Entry> new_entries) {
	for (Entry e : new_entries) {
		entries.push_back(e);
	}
}
template <typename T>
std::string tolowerString(T text) {
	std::string newString;
	std::transform(text.begin(), text.end(), std::back_inserter(newString), (int(*)(int))std::tolower);
	std::cout << newString << std::endl;
	return newString;
}

FileHandler::~FileHandler() {

	int dir_counter = 0, file_counter = 0;
	for (auto& i : fs::directory_iterator("D:/Github/projects/concurrent/final/opd4/sandbox"))
	{
		//std::cout << i.path() << std::endl;


		if (i.is_directory()) {
			dir_counter++;
		}
		else if (i.is_regular_file()) {
			file_counter++;
		}
		if (i.is_regular_file()) {
			//std::cout << i.path().filename() << std::endl;
			std::string::size_type pos = i.path().string().find(tolowerString("TeXt"));
			if (pos != std::string::npos) {
				std::cout << "Contains keyword!\n";
			}
			file_counter++;
		}	
	}



	std::cout << "amount of directories in directory: " << dir_counter << std::endl;
	std::cout << "amount of files in directory: " << file_counter << std::endl;

	std::lock_guard<std::mutex> prnt_lk(prnt_mtx);
	for (Entry e : entries) {
		std::cout << "closing the thread handling " << e.loc_name << std::endl;
	}

}
