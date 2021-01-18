#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include "chat_message.h"

using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class chat_participant
{
public:
	virtual ~chat_participant() {};
	virtual void deliver(const chat_message& msg) = 0;
};

typedef std::shared_ptr<chat_participant> chat_participant_ptr;

class chat_room
{
public:
	void join(chat_participant_ptr participant) {
		participants_.insert(participant);
		for (auto msg : recent_msgs_) {
			participant->deliver(msg);
		}
	}

	void leave(chat_participant_ptr participant) {
		participants_.erase(participant);
	}
	
	void deliver(const chat_message& msg) {
		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() > max_recent_msgs) {
			recent_msgs_.pop_front();

			for (auto p : participants_) {
				p->deliver(msg);
			}
		}
	}

private:
	std::set<chat_participant_ptr> participants_;
	enum{max_recent_msgs = 50};
	chat_message_queue recent_msgs_;
};

class chat_session :
	public chat_participant,
	public std::enable_shared_from_this<chat_session>
{
public:
	chat_session(tcp::socket socket, chat_room& room) : socket_(std::move(socket)), room_(room) {};
	void start() {
		room_.join(shared_from_this());
		read_header();
	}

	void deliver(const chat_message& msg) {
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress) {
			write();
		}
	}

	~chat_session();

private:
	void read_header() {
	};

	void write() {
	};
	tcp::socket socket_;
	chat_room& room_;
	chat_message read_mgs_;
	chat_message_queue write_msgs_;
	};
