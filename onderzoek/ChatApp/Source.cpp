#include "chat_client.cpp"
#include "chat_server.cpp"
#include <thread>
#include <string.h>

int main(int argc, char* argv[])
{
	char choice;
	std::cout << "(S)erver or (C)lient:\n";
	std::cin >> choice;
	try
	{
		boost::asio::io_context io_context;
		if (::tolower(choice) == 's') {
			
			std::list<chat_server> servers;
			int amount;
			std::cout << "Amount of servers (max 10): ";
			try {
				std::cin >> amount;
				if (amount > 10) {
					std::cerr << "Too many severs!\n";
					amount = 0;
				}
			}
			catch (std::exception& e) {
				std::cerr << e.what() << "\n";
			}
			for (int i = 0; i < amount; i++) {
				int port;
				std::cout << "Server " << i << ", Port: ";

				try{
					std::cin >> port;

					tcp::endpoint endpoint(tcp::v4(), port);
					servers.emplace_back(io_context, endpoint);
				}
				catch (std::exception& e) {
					break;
				}
			}

			io_context.run();

		}
		else if(::tolower(choice) == 'c') {

			std::string ip, port, name;
			std::cout << "Enter IP adress:\n";
			std::cin >> ip;
			std::cout << "Enter port:\n";
			std::cin >> port;
			std::cout << "Enter name:\n";
			std::cin >> name;
			name = "[" + name + "]";
			//start client
			tcp::resolver resolver(io_context);
			auto endpoints = resolver.resolve(ip, port);
			chat_client c(io_context, endpoints, name);

			std::thread t([&io_context]() { io_context.run(); });
			char line[chat_message::max_body_length + 1];
			while (std::cin.getline(line, chat_message::max_body_length + 1)) {
				chat_message msg;
				msg.body_length(std::strlen(line));
				std::memcpy(msg.body(), line, msg.body_length());
				msg.encode_header();
				c.write(msg);
			}

			c.close();
			t.join();
		}
	}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}

		return 0;
	}