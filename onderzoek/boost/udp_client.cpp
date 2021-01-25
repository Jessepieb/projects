#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class udp_client
{
public:
	udp_client(boost::asio::io_context& io, std::string host, std::string port) :
		socket_(io, udp::endpoint(udp::v4(), 0)), resolver_(io),
		endpoints(resolver_.resolve(udp::v4(), host, port)) {
		do_write();
	};


	void do_write() {
		try{
		char data[max_length];
		std::cout << "Enter Message\n";
		std::cin.getline(data, max_length);
		std::cout << "\n";
		std::size_t msg_length = strlen(data);
		socket_.send_to(boost::asio::buffer(data, msg_length), *endpoints.begin());

		do_read();
	}
		catch (std::exception& e) {
			std::cerr << e.what() << "\n";
		}
	}

	void do_read() {
		try {
			udp::endpoint sender_endpoint;
			char reply[max_length];
			socket_.receive_from(boost::asio::buffer(reply, max_length), sender_endpoint);
			std::size_t reply_length = strlen(reply);
			std::cout << "Reply is:\n";
			std::cout.write(reply, reply_length);
			std::cout << "\n";
			
			do_write();
		}
		catch (std::exception& e) {
			std::cerr << e.what() << "\n";
		}
	}

private:
	udp::socket socket_;
	udp::resolver resolver_;
	udp::resolver::results_type endpoints;
	enum { max_length = 1024 };
};