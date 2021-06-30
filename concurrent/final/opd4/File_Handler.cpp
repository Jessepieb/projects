#include "File_Handler.h"

std::string tolowerString(std::string text) {
	std::string newString;
	std::transform(text.begin(), text.end(), std::back_inserter(newString), (int(*)(int))std::tolower);
	std::cout << newString << std::endl;
	return newString;
}

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

std::vector<fs::path> FileHandler::find_directories(Entry e) {
	std::vector<fs::path> matched_directories;
	for (auto& i : fs::directory_iterator(e.src_directory))
	{
		if (i.is_directory()) {
			if (find_keywords(tolowerString(i.path().filename().string()), e.keywords)) {
				matched_directories.push_back(i.path());
			}
		}
	}
	return matched_directories;
}

std::vector<fs::path> FileHandler::find_files(Entry e) {
	std::vector<fs::path> matched_files;
	std::cout << "For " << e.src_directory << " finding: " << std::endl;
	for (auto& i : fs::directory_iterator(e.src_directory)) {
		if (i.is_regular_file()) {
			if ( find_keywords(tolowerString(i.path().filename().string()), e.keywords)) {
				matched_files.push_back(i.path());
			}
		}
	}
	return matched_files;
}

bool FileHandler::find_keywords(std::string file_name, std::vector<std::string> keywords) {
	for (auto keyword : keywords) {

	/*	std::string::size_type pos = file_name.find(keyword);
		if (pos != std::string::npos) {
			std::cout << "Contains " << keyword << std::endl;
			return true;*/
		std::regex rgx (keyword);
		std::smatch sm;
		if (std::regex_search(file_name,sm, rgx) != NULL) {
			std::cout << "Matched " << file_name << " on: " << keyword << std::endl;
			return true;
		}
	}
	return false;
}

void FileHandler::start_loop(size_t id) {
	for (Entry e : entries) {
		std::vector<fs::path> matches;
		//std::cout << "Finding matches for" << e.loc_name << std::endl;
		if (e.sort_dir) {
			std::vector<fs::path> results = find_directories(e);
			std::cout << "for " << e.loc_name << " got " << results.size() << " results." << std::endl;
			matches.insert(matches.end(), results.begin(), results.end());
		}
		if (e.sort_files)
		{
			std::vector<fs::path> results = find_files(e);
			std::cout << "for " << e.loc_name << " got " << results.size() << " results." << std::endl;
			matches.insert(matches.end(), results.begin(), results.end());
		}

				////std::cout << i.path().filename() << std::endl;
				//std::string::size_type pos = i.path().string().find(tolowerString(e.keywords[0]));
				//if (pos != std::string::npos) {
				//	//std::cout << "Contains " << e.keywords[0] << std::endl;
				//	file_counter++;

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

FileHandler::~FileHandler() {

}
