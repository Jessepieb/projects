////#include "chat_client.cpp"
////#include "chat_server.cpp"
//#include "tcp_server_async.cpp"
//#include <thread>
//
//using boost::asio::ip::tcp;
////int main() {
////	char choice;
////	std::cout << "(S)erver or (C)lient:\n";
////	std::cin >> choice;
////	try {
////		boost::asio::io_context io_context;
////		if (choice == 's') {
////			tcp::endpoint serv_end(tcp::v4(),13);
////			std::cout << "Spinning up server on: " << serv_end.address() << std::endl;;
////			chat_server server(io_context, serv_end);
////			io_context.run();
////
////		}
////		else {
////			tcp::resolver resolver(io_context);
////			auto endpoints = resolver.resolve("0.0.0.0","13");
////			chat_client c(io_context, endpoints);
////
////			io_context.run();
////
////			char line[chat_message::max_body_length + 1];
////			while (std::cin.getline(line, chat_message::max_body_length + 1)) {
////				chat_message msg;
////				msg.body_length(std::strlen(line));
////				std::memcpy(msg.body(), line, msg.body_length());
////				msg.encode_header();
////				c.write(msg);
////			}
////
////			c.close();
////		}
////
////	}
////	catch (std::exception& e) {
////		std::cerr << "Exception: " << e.what() << std::endl;
////	}
////	return 0;
////}
//int main() {
//	try {
//		boost::asio::io_context io;
//		tcp_server s(io,1234);
//		
//		io.run();
//	}
//	catch (std::exception& err) {
//		std::cerr << err.what() << "\n";
//	}
//	return 0;
//}
//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "tcp_echo_server_async.cpp"
#include "tcp_echo_client.cpp"
#include "udp_echo_server_async.cpp"
#include "udp_echo_client.cpp"

int main(int argc, char* argv[])
{
    try
    {
      /*  if (argc != 2)
        {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }*/

        boost::asio::io_context io_context;

        //tcp_echo_server s(io_context, std::atoi("13"));
        udp_echo_server s(io_context, 13);

        //udp_client(io_context, "127.0.0.1", "13");

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}