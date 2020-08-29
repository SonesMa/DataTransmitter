#include "TransmitTask.h"
#include "DataTransmitter.h"
#include "TestCase.h"

#include "args.h"

#include <iostream>

using namespace AppSoft;
using namespace std::chrono_literals;

int TransmitArgs::parse(int argc, char* argv[])
{
    args::ArgumentParser parser("This is a test program to trasmit binary data"
        " to given peer with IP address and port.", 
        "This program is used to send binary data in given duraion.");
    args::HelpFlag help(parser, "help", "Display this help menu", { 'h', "help" });
    args::ValueFlag<size_t> interval(parser, "", "The interval time by microseconds", 
        { 'i', "interval" }, 100);
    args::ValueFlag<size_t> duration(parser, "", "The duration time by minutes",
        { 'd', "duration" }, 30);
    args::ValueFlag<size_t> numbers(parser, "", "The sample numbers",
        { 'n', "numbers" }, 1000);
    args::ValueFlag<std::string> type(parser, "", "The transport type: TCP or UDP", { 't', "type" }, args::Options::Required);
    args::ValueFlag<std::string> address(parser, "", "The IP address of peer", { 'p', "peer" }, args::Options::Required);
    args::ValueFlag<int> port_provided(parser, "", "The port of peer", { 'r', "port" }, args::Options::Required);

    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help)
    {
        std::cout << parser << std::endl;
        return -1;
    }
    catch (args::ParseError e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    catch (args::ValidationError e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    if (interval) {
        interval_by_us = interval.Get();
    }

    if (duration) {
        duration_by_minutes = duration.Get();
    }

    if (numbers) {
        sample_numbers = numbers.Get();
    }

    if (type) {
        if (type.Get() == "TCP") {
            transport_type = TransportType::TCP;
        }
        else {
            transport_type = TransportType::UDP;
        }
    }

    if (address) {
        peer = address.Get();
    }

    if (port_provided) {
        port = port_provided.Get();
    }

	return 0;
}

size_t TransmitArgs::getInterval()
{
    return interval_by_us;
}

size_t TransmitArgs::getDuration()
{
    return duration_by_minutes;
}

size_t TransmitArgs::getSampleNumbers()
{
    return sample_numbers;
}

TransportType TransmitArgs::getTransportType()
{
    return transport_type;
}

std::string TransmitArgs::getPeerAddress()
{
    return peer;
}

int TransmitArgs::getPeerPort()
{
    return port;
}

AppSoft::TransmitTask::TransmitTask(TransmitArgs& _args)
    :args(_args), transmitter(nullptr)
{
    switch (args.getTransportType()) {
    case TransportType::TCP:
        transmitter = new TCPTransmitter(args.getPeerAddress(), args.getPeerPort());
        break;
    case TransportType::UDP:
        transmitter = new UDPTransmitter(args.getPeerAddress(), args.getPeerPort());
        break;
    default:
        break;
    }
}

void TransmitTask::run()
{
    try {
        auto start = std::chrono::steady_clock::now();
        auto watch_point = std::chrono::steady_clock::now();
        auto duration = std::chrono::minutes(args.getDuration());

        TestCase item;
        size_t counts = args.getSampleNumbers();
        while(counts != 0) {
            buffer_t buffer = item.testcase(counts);
            transmitter->transmit(buffer.data.get(), buffer.length);
            std::this_thread::sleep_for(std::chrono::milliseconds(args.getInterval()));

            auto now = std::chrono::steady_clock::now();

            if (now - watch_point >= 1min) {
                std::cout << "This is one minute heart beat." << std::endl;
                watch_point = now;
            }

            if (now - start >= duration)
                break;
            
            --counts;

            if (counts == 0)
                counts = args.getSampleNumbers();
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
