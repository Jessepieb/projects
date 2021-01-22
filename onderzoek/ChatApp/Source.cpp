//#include "chat_client.cpp"
//#include "chat_server.cpp"
#include "tcp_server_async.cpp"
#include <thread>

using boost::asio::ip::tcp;
//int main() {
//	char choice;
//	std::cout << "(S)erver or (C)lient:\n";
//	std::cin >> choice;
//	try {
//		boost::asio::io_context io_context;
//		if (choice == 's') {
//			tcp::endpoint serv_end(tcp::v4(),13);
//			std::cout << "Spinning up server on: " << serv_end.address() << std::endl;;
//			chat_server server(io_context, serv_end);
//			io_context.run();
//
//		}
//		else {
//			tcp::resolver resolver(io_context);
//			auto endpoints = resolver.resolve("0.0.0.0","13");
//			chat_client c(io_context, endpoints);
//
//			io_context.run();
//
//			char line[chat_message::max_body_length + 1];
//			while (std::cin.getline(line, chat_message::max_body_length + 1)) {
//				chat_message msg;
//				msg.body_length(std::strlen(line));
//				std::memcpy(msg.body(), line, msg.body_length());
//				msg.encode_header();
//				c.write(msg);
//			}
//
//			c.close();
//		}
//
//	}
//	catch (std::exception& e) {
//		std::cerr << "Exception: " << e.what() << std::endl;
//	}
//	return 0;
//}
int main() {
	try {
		boost::asio::io_context io;
		tcp_server s(io,1234);
		
		io.run();
	}
	catch (std::exception& err) {
		std::cerr << err.what() << "\n";
	}
	return 0;
}