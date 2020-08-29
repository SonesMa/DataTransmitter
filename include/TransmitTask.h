#pragma once

#include <chrono>
#include <string>

#include "DataTransmitter.h"

namespace AppSoft {
	enum class TransportType {
		TCP,
		UDP
	};

	class TransmitArgs {
	public:
		TransmitArgs() = default;
		~TransmitArgs() = default;

		TransmitArgs(TransmitArgs &) = delete;
		TransmitArgs(TransmitArgs &&) = delete;

		TransmitArgs& operator=(TransmitArgs&) = delete;
		TransmitArgs&& operator=(TransmitArgs&&) = delete;

		int parse(int argc, char* argv[]);

		size_t getInterval();

		size_t getDuration();

		size_t getSampleNumbers();

		TransportType getTransportType();

		std::string getPeerAddress();

		int getPeerPort();

	private:
		size_t interval_by_us = 100;
		size_t duration_by_minutes = 30;
		size_t sample_numbers = 1000;
		TransportType transport_type = TransportType::UDP;
		std::string peer;
		int port = 10240;
	};

	class DataTransmitter;

	class TransmitTask {
	public:
		TransmitTask(TransmitArgs& _args);

		~TransmitTask()
		{
			if (transmitter)
				delete transmitter;
		}

		void run();

	private:
		TransmitArgs& args;
		DataTransmitter* transmitter;
	};
}