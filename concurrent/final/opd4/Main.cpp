#include "Main.h"
#include "File_Handler.h"
#include "Settings_Manager.h"
namespace fs = std::filesystem;

using json = nlohmann::json;

std::string tolowerString(std::string text) {
	std::string newString;
	std::transform(text.begin(), text.end(), std::back_inserter(newString), (int(*)(int))std::tolower);
	std::cout << newString << std::endl;
	return newString;
}


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