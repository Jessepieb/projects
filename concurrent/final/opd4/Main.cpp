#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <cstdio>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

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

private:
	
	
};




int main() {
	FileHandler fh;
	fh.write_file("test.txt");
	fh.copy_file("test.txt", "text2.txt");

	for (auto& i : fs::directory_iterator("D:/Github/projects/concurrent/final/opd4"))
	{
		std::cout << i.path() << std::endl;
	}
}