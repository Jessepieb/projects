//#include <cstdlib>
//#include <cstring>
//#include<iostream>
//#include <string>
//#include<boost/asio.hpp>
//
//using boost::asio::ip::tcp;
//
//class tcp_client
//{
//public:
//	tcp_client(boost::asio::io_context& io, tcp::endpoint endpoint) : socket_(io), resolver_(io) {
//		do_connect(endpoint);
//	}
//
//
//private:
//	void do_connect(tcp::endpoint endpoint) {
//		boost::asio::connect(socket_, endpoint,
//			[this](const boost::system::error_code& e, std::size_t length) {
//				if (!e) {
//					do_write();
//				}
//			});
//	}
//
//	void do_write() {
//		std::cout << "Enter Message: \n";
//		std::cin.getline(data_, max_length);
//		std::cout << "\n";
//
//		std::size_t data_length = std::strlen(data_);
//		boost::asio::write(socket_, boost::asio::buffer(data_, data_length));
//
//		do_read(data_length);
//	}
//
//	void do_read(std::size_t data_length) {
//		boost::asio::read(socket_,
//			boost::asio::buffer(data_, data_length), [this](const boost::system::error_code& e, std::size_t length) {
//				if (!e) {
//					std::cout.write(data_, strlen(data_));
//					std::cout << "\n";
//				}
//				else {
//					do_write();
//				}			
//			});
//	}
//
//	enum { max_length = 1024 };
//	tcp::socket socket_;
//	tcp::resolver resolver_;
//	char data_[max_length];
//};