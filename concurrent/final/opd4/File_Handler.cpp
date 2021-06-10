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

std::vector<fs::path> FileHandler::find_directories(fs::path p, std::string keyword) {
	std::vector<fs::path> matched_directories;
	return matched_directories;
}

void FileHandler::start_loop(size_t id){
	std::lock_guard<std::mutex> prnt_lk(prnt_mtx);
	for (Entry e : entries) {
		std::cout << "message from Thread handling: " << e.loc_name << std::endl;
	}
}
void FileHandler::find_keywords(std::vector<std::string> kw) {

}


FileHandler::FileHandler(Entry new_entry) {
	entries.push_back(new_entry);
}

FileHandler::FileHandler(std::vector<Entry> new_entries) {
	for (Entry e : new_entries) {
		entries.push_back(e);
	}
}

FileHandler::~FileHandler() {
	//std::lock_guard<std::mutex> prnt_lk(prnt_mtx);
	//for (Entry e : entries) {
	//	std::cout << "message from thread handling " << e.loc_name << std::endl;
	//}

}
