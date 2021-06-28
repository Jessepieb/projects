#include "Main.h"
#include "File_Handler.h"
#include "Settings_Manager.h"
namespace fs = std::filesystem;

//create thread_guard to make sure that all threads are properly closed
class thread_guard
{
public:
	explicit thread_guard(std::thread& t_) : t(t_) {};
	~thread_guard() {
		//on destuction of this object it will check if the referenced thread is joinable
		//since threads can only be joined once
		if (t.joinable()) {
			t.join();
		}
	};
	//mark copy and assingment methods with delete to ensure that they don't outlive the intended scope
	//trying to copy a thread_guard object will result in a compilation error
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;

private:
	std::thread& t;
};

int main() {

	//get hardware core count to avoid oversubscription
	const auto max_threads = std::thread::hardware_concurrency();

	//create a setting manager object to load, edit and save settings
	Settings_Manager setting_m;

	//FileHandler fh;
	//fh.write_file("sandbox/text.txt");
	//fh.copy_file("sandbox/text.txt", "sandbox/text2.txt");
	//fh.copy_file("Pictures/test_picture.jpg", "Pictures/copied_picture.jpg");
	//static_cast<void>(std::system("tree"));

	std::vector<Entry> entries;

	for (size_t it = 0; it != setting_m.j_object.size(); ++it) {
		std::cout << setting_m.j_object[it] << "\n";
		std::cout << "--------------------------------------------\n";

		Entry e = from_json(setting_m.j_object[it]);
		entries.push_back(e);
	}

	for (size_t i = 0; i < entries.size(); i++)
	{
		std::cout << entries[i].loc_name << std::endl;
	}


	int thread_count = 0;
	int spare = 0 , entries_per_thread = 0;
	if (max_threads != 0) {
		if (entries.size() < max_threads) {
			thread_count = entries.size();
			entries_per_thread = 1;
		}
		else {
			thread_count = max_threads;
			spare = entries.size() % max_threads;
			entries_per_thread = entries.size() / max_threads;
		}
	}

	std::vector<std::thread> threads;
	int block = 0;
	for (size_t i = 0; i < thread_count; i++)
	{
		FileHandler* fh;
		if (entries_per_thread > 1) {
			std::vector<Entry> entry_block;
			//std::copy(entries[block], entries[block + entries_per_thread-1],std::back_inserter(entry_block));
			fh = new FileHandler(entry_block);
			block = block + entries_per_thread;
		}
		else {
		 fh = new FileHandler(entries[i]);
		}
		
		threads.push_back(std::thread(&FileHandler::start_loop, fh, i));
	}
	std::cout << "Created " << threads.size() << " Threads" << std::endl;
	for (auto& th : threads)
	{
		if (th.joinable()) {
			th.join();
		}
	}

	//sm.create_loc();
}