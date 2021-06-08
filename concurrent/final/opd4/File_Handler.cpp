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
	std::lock_guard<std::mutex> prnt_lk(prnt_mtx);
	std::cout << "message from thread " << std::endl;

}
