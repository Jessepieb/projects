//#include <ctime>
//#include <iostream>
//#include<string>
//#include<boost/asio.hpp>
//
//using boost::asio::ip::tcp;
//std::string make_daytime() {
//	using namespace std;
//	time_t now = time(0);
//	return ctime(&now);
//}
//
//int start() {
//	try {
//		boost::asio::io_context io;
//
//		tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 13));
//
//		for (;;) {
//			tcp::socket socket(io);
//			acceptor.accept(socket);
//
//			std::string message = make_daytime();
//
//			boost::system::error_code ignored_error;
//			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
//		}
//	}
//	catch (std::exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//	return 0;
//}