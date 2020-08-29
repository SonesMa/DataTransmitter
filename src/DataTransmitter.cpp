#include "DataTransmitter.h"

using namespace AppSoft;

TCPTransmitter::TCPTransmitter(std::string_view server_ip, unsigned short port)
	:local(service),
	peer(asio::ip::address::from_string(server_ip.data()), port)
{
	local.connect(peer);
}

void TCPTransmitter::transmit(const char* buf, size_t size)
{
	local.send(asio::buffer(buf, size));
}

UDPTransmitter::UDPTransmitter(std::string_view server_ip, unsigned short port )
	:local(service, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)),
	peer(asio::ip::address::from_string(server_ip.data()), port)
{
}

void UDPTransmitter::transmit(const char* buf, size_t size)
{
	local.send_to(asio::buffer(buf, size), peer);
}