//#include <cstdlib>
//#include<deque>
//#include<iostream>
//#include <thread>
//#include <boost/asio.hpp>
//#include "chat_message.h"
//
//using boost::asio::ip::tcp;
//typedef std::deque<chat_message> chat_message_queue;
//
//class chat_client
//{
//public:
//	chat_client(boost::asio::io_context& io_context,
//		const tcp::resolver::results_type& endpoints) :
//		io_context_(io_context), socket_(io_context) {
//		std::cout << "Starting client and trying to connect...\n";
//		do_connect(endpoints);
//	};
//
//	void write(const chat_message& msg) {
//		boost::asio::post(io_context_, [this, msg]() {
//			bool write_in_progress = !write_msgs_.empty();
//			write_msgs_.push_back(msg);
//			if (!write_in_progress) {
//				do_write();
//			}
//			});
//	}
//
//	void close() {
//		//close socket using lambda function and post completion token to io context
//		boost::asio::post(io_context_, [this]() {socket_.close(); });
//	}
//
//private:
//	void do_connect(const tcp::resolver::results_type& endpoints) {
//		boost::asio::async_connect(socket_, endpoints, [this]( const boost::system::error_code& error, tcp::endpoint) {
//			if (!error) {
//				read_header();
//			}
//			});
//	}
//
//	void read_header() {
//		boost::asio::async_read(socket_,
//			boost::asio::buffer(read_msg_.data(), chat_message::header_length),
//			[this](const boost::system::error_code& error, std::size_t /*length*/) {
//				if (!error && read_msg_.decode_header()) {
//					read_body();
//				}
//				else { socket_.close(); }
//			});
//	}
//
//	void read_body() {
//		boost::asio::async_read(socket_,
//			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
//			[this](const boost::system::error_code& error, std::size_t /*length*/) {
//				if (!error) {
//					std::cout.write(read_msg_.body(), read_msg_.length());
//					std::cout << std::endl;
//					read_header();
//				}
//				else {
//					socket_.close();
//				}
//			});
//	}
//
//	void do_write() {
//		boost::asio::async_write(socket_,
//			boost::asio::buffer(write_msgs_.front().data(),
//				write_msgs_.front().length()),
//			[this](const boost::system::error_code& error, std::size_t /*length*/)
//			{
//				if (!error) {
//					write_msgs_.pop_front();
//					if (!write_msgs_.empty()) {
//						do_write();
//					}
//					else {
//						socket_.close();
//					}
//				}
//			}
//
//		);
//	}
//
//
//	boost::asio::io_context& io_context_;
//	tcp::socket socket_;
//	chat_message read_msg_;
//	chat_message_queue write_msgs_;
//};
