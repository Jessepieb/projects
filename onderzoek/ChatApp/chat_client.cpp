#include <cstdlib>
#include<deque>
#include<iostream>
#include <thread>
#include <boost/asio.hpp>
#include "chat_message.h"

using boost::asio::ip::tcp;
using boost::system::error_code;
typedef std::deque<chat_message> chat_message_queue;

class chat_client
{
public:
	chat_client(boost::asio::io_context& io_context,
		const tcp::resolver::results_type& endpoints) :
		io_context_(io_context), socket_(io_context) {
		do_connect(endpoints);
	};

	void write(const chat_message& msg) {
		boost::asio::post(io_context_, [this, msg]() {
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(msg);
			if (!write_in_progress) {
				do_write();
			}
			});
	}

	void close() {
		//close socket using lambda function and post completion token to io context
		boost::asio::post(io_context_, [this]() {socket_.close(); });
	}

private:
	void do_connect(const tcp::resolver::results_type& endpoints) {
		boost::asio::async_connect(socket_, endpoints, [this](error_code& error, tcp::endpoint) {
			if (!error) {
				read_header();
			}
			});
	}

	void read_header() {
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::header_length),
			[this](error_code& error, std::size_t /*length*/) {
				if (!error && read_msg_.decode_header()) {
					read_body();
				}
				else { socket_.close(); }
			});
	}

	void read_body() {
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			[this](error_code& error, std::size_t /*length*/) {
				if (!error) {
					std::cout.write(read_msg_.body(), read_msg_.length());
					std::cout << std::endl;
					read_header();
				}
				else {
					socket_.close();
				}
			});
	}

	void do_write() {
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			[this](error_code& error, std::size_t /*length*/)
			{
				if (!error) {
					write_msgs_.pop_front();
					if (!write_msgs_.empty()) {
						do_write();
					}
					else {
						socket_.close();
					}
				}
			}

		);
	}


	boost::asio::io_context& io_context_;
	tcp::socket socket_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
};

int main() {
	try {
		boost::asio::io_context io_context;

		tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve("127.0.0.1", "13");
		chat_client c(io_context, endpoints);


		std::thread t([&io_context]() {io_context.run(); });

		char line[chat_message::max_body_length + 1];
		while (std::cin.getline(line, chat_message::max_body_length + 1)) {
			chat_message msg;
			msg.body_length(std::strlen(line));
			std::memcpy(msg.body(), line, msg.body_length());
			msg.encode_header();
			c.write(msg);
		}

		c.close();
		t.join();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 0;
}
