#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
class session : public std::enable_shared_from_this<session>
{
public:
	session(tcp::socket socket) : socket_(std::move(socket)),data_() {

	}

	void start() { do_read(); }
private:
	void do_read() {
		auto self(shared_from_this());
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
			[this, self](const boost::system::error_code& err, std::size_t length) {
				if (!err) {
					do_write(length);
				}
			});
	}

	void do_write(std::size_t length) {
		auto self(shared_from_this());
		boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
			[this, self](const boost::system::error_code& err, std::size_t length) {
				if (!err) {
					std::cout.write(data_, strlen(data_));
					std::cout<<"\n";
					do_read();
				}
			});
	}

	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
};

class tcp_server
{
public:
	tcp_server(boost::asio::io_context& io, int port) : acceptor_(io, tcp::endpoint(tcp::v4(), port)) {
		std::cout << "Spinning up...\n";
		do_accept();
	};

private:
	void do_accept() {
		acceptor_.async_accept(
			[this](const boost::system::error_code& err, tcp::socket socket) {
				if (!err) {
					std::make_shared<session>(std::move(socket))->start();
				}
				else { do_accept(); }
			});
	}

	tcp::acceptor acceptor_;
};