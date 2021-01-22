//#include <ctime>
//#include <iostream>
//#include <string>
//#include <boost/array.hpp>
//#include <boost/bind.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/enable_shared_from_this.hpp>
//#include <boost/asio.hpp>
//using boost::asio::ip::tcp;
//using boost::asio::ip::udp;
//
//std::string make_daytime() {
//	using namespace std;
//	time_t now = time(0);
//	return ctime(&now);
//}
//
//
//class tcp_connection:public boost::enable_shared_from_this<tcp_connection>
//{
//public:
//	typedef boost::shared_ptr<tcp_connection> pointer;
//
//	static pointer create(boost::asio::io_context& io_context) {
//		return pointer(new tcp_connection(io_context));
//	}
//
//	tcp::socket& socket() {
//		return socket_;
//	}
//
//	void start() {
//		message_ = make_daytime();
//		std::cout << socket_.local_endpoint() << std::endl;
//		boost::asio::async_write(socket_, boost::asio::buffer(message_),
//			boost::bind(&tcp_connection::handle_write, shared_from_this()));
//	}
//
//private:
//	tcp_connection(boost::asio::io_context& io) :socket_(io) {
//	}
//
//	void handle_write() {
//
//	}
//	tcp::socket socket_;
//	std::string message_;
//};
//
//class tcp_server
//{
//public:
//	tcp_server(boost::asio::io_context& io) : io_(io), acceptor_(io, tcp::endpoint(tcp::v4(), 13)) {
//		start_accept();
//	};
//private:
//	void start_accept() {
//		tcp_connection::pointer new_connection =
//			tcp_connection::create(io_);
//		acceptor_.async_accept(new_connection->socket(),
//			boost::bind(&tcp_server::handle_accept, this, new_connection,
//				boost::asio::placeholders::error));
//
//	}
//
//	void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error) {
//		std::cout << "handling request\n";
//		if (!error) {
//			new_connection->start();
//		}
//		start_accept();
//	}
//
//	boost::asio::io_context& io_;
//	tcp::acceptor acceptor_;
//};
//
//class udpServer
//{
//public:
//	udpServer(boost::asio::io_context& io) :socket_(io, udp::endpoint(udp::v4(), 13)) {
//		try {
//			std::cout << "spinning up UDP server\n";
//			for (;;) {
//				boost::array<char, 1> recv_buffer;
//				udp::endpoint remote_endpoint;
//				socket_.receive_from(boost::asio::buffer(recv_buffer), remote_endpoint);
//
//				std::string message = "Apple Pie";//make_daytime();
//				socket_.send_to(boost::asio::buffer(message), remote_endpoint, 0);
//			}
//		}
//		catch (std::exception& e) {
//			std::cerr << e.what() << std::endl;
//		}
//	};
//
//private:
//	udp::socket socket_;
//};
#include "tcp_client.cpp"
int main() {
	try
	{
		std::cout << "Spinning up...\n";
		boost::asio::io_context io;
		tcp::endpoint end(boost::asio::ip::address::from_string("127.0.0.1"), 1234);
		//tcp::resolver resolver(io);
		/*resolver.resolve("127.0.0.1", "1337");*/
		//tcp_server server(io);
		tcp_client server(io, end);
		io.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}