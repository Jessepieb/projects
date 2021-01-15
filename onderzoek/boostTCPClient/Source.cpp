#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

class tcpClient
{
public:
	tcpClient(boost::asio::io_service& io,std::string client, std::string host) : resolver_(io), socket_(io){
		try {
			tcp::resolver::results_type endpoints = resolver_.resolve(client, host);

			boost::asio::connect(socket_, endpoints);

			for (;;) {
				boost::array<char, 128> buf;
				boost::system::error_code error;

				size_t len = socket_.read_some(boost::asio::buffer(buf), error);

				if (error == boost::asio::error::eof) {
					break; //connection properly closed by peer
				}
				else if (error) {
					throw boost::system::system_error(error); //other errors
				}

				std::cout.write(buf.data(), len);
			}
		}
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	};

private:
	tcp::resolver resolver_;
	tcp::socket socket_;
};

class udpClient
{
public:
	udpClient(boost::asio::io_service& io, std::string client, std::string host): resolver_(io), socket_(io){
		try {
			udp::resolver::query query(udp::v4(), client, host);

			udp::endpoint receiver_endpoint = *resolver_.resolve(query);

			socket_.open(udp::v4());

			boost::array<char, 1> send_buf = { 0 };
			socket_.send_to(boost::asio::buffer(send_buf), receiver_endpoint);


			boost::array<char, 128> recv_buffer;

			udp::endpoint sender_endpoint;
			size_t len = socket_.receive_from(boost::asio::buffer(recv_buffer), sender_endpoint);

			std::cout.write(recv_buffer.data(), len);


		}
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

private:
	udp::resolver resolver_;
	udp::socket socket_;
};

int main() {
	boost::asio::io_service io;
	udpClient client(io, "127.0.0.1", "daytime");
	io.run();
	return 0;
}