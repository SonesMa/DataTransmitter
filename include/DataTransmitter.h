#pragma once

#include <string>

#ifdef WIN32
#include "sdkddkver.h"
#endif
#include "asio.hpp"

namespace AppSoft {
	class DataTransmitter {
	public:
		virtual ~DataTransmitter() = default;

		virtual void transmit(const char *buf, size_t size) = 0;

	protected:
		asio::io_service service;
	};

	class TCPTransmitter : public DataTransmitter {
	public:
		TCPTransmitter(std::string_view server_ip, unsigned short port);
		~TCPTransmitter() = default;

		void transmit(const char* buf, size_t size) override;
	private:
		asio::ip::tcp::endpoint peer;
		asio::ip::tcp::socket local;
	};

	class UDPTransmitter : public DataTransmitter {
	public:
		UDPTransmitter(std::string_view server_ip, unsigned short port);
		~UDPTransmitter() = default;

		void transmit(const char* buf, size_t size) override;

	private:
		asio::ip::udp::endpoint peer;
		asio::ip::udp::socket local;
	};
}
