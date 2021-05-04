#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>

class FileHandler {
public:
	FileHandler() {

	};

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
		dest.open(dest_url, std::ios::trunc);
		if (src.is_open() && dest.is_open()) {
		while (std::getline(src, line)) {
			std::cout << line;
			dest << line;
		}
	}
			src.close();
			dest.close();
	}

private:
	std::ifstream src;
	std::ofstream dest;
	
};




int main() {
	FileHandler fh;
	fh.write_file("test.txt");
	fh.copy_file("text.txt", "text2.txt");
}