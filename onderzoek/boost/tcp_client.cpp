#include <cstdlib>
#include <cstring>
#include<iostream>
#include <string>
#include<boost/asio.hpp>

using boost::asio::ip::tcp;

class tcp_client
{
public:
	tcp_client(boost::asio::io_context& io, tcp::endpoint& endpoint) : socket_(io) {
		do_connect(endpoint);
	}


private:
	void do_connect(tcp::endpoint& endpoint) {
		std::cout << "Connecting to endpoint: \n" << endpoint.address().to_string() << std::endl;
		socket_.connect(endpoint);
		do_write();
	}

	void do_write() {
		boost::system::error_code err;
		try {
			std::cout << "Enter Message: \n";
			std::cin.getline(msg_, max_length);

			std::size_t data_length = std::strlen(msg_);
			socket_.write_some(boost::asio::buffer(msg_, data_length), err);
			//boost::asio::write(socket_, boost::asio::buffer(msg_, data_length), err);
			if (!err) {
				//std::cout << "Message sent to server\n";
			}
			do_read();
		}
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	void do_read() {
		boost::system::error_code err;
		try {
			boost::asio::read(socket_, boost::asio::buffer(reply_, max_length), err);
			if (!err) {
				std::cout << "Data received: \n";
				std::cout.write(reply_, strlen(reply_));
				std::cout << "\n";
			}
			do_write();
		}
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	enum { max_length = 1024 };
	tcp::socket socket_;
	char msg_[max_length];
	char reply_[max_length];
};