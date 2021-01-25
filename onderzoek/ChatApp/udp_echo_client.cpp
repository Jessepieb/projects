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
		endpoints(resolver_.resolve(udp::v4(),host,port)){
		do_write();
	};


	void do_write() {
		std::cout << "Enter Message\n";
		std::cin.getline(data_, max_length);
		std::cout << "\n";
		socket_.send_to(boost::asio::buffer(data_, max_length), *endpoints.begin());

		do_read();
	}

	void do_read() {
		udp::endpoint sender_endpoint;
		std::size_t data_length = socket_.receive_from(
			boost::asio::buffer(data_, max_length), sender_endpoint);
		std::cout << "Reply is: ";
		std::cout.write(data_, data_length);
		std::cout << "\n";
	}

private:
	udp::socket socket_;
	udp::resolver resolver_;
	udp::resolver::results_type endpoints;
	enum{max_length = 1024};
	char data_[max_length];
};