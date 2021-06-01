#include "File_Handler.h"
using namespace fh;

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

void FileHandler::find_keywords() {

}
std::mutex prnt_mtx;
void FileHandler::start_loop(int id) {
	std::lock_guard<std::mutex> prnt_lk(prnt_mtx);
	std::cout << "message from thread " << id << std::endl;
}

FileHandler::FileHandler() {};

FileHandler::FileHandler(Entry e) {

}

FileHandler::~FileHandler() {

}
