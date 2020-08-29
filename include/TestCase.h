#pragma once

#include <cstdint>
#include <memory>

struct buffer_t {
	buffer_t()
		:length(0) {}

	buffer_t(char* data, size_t size)
		:data(data), length(size) {}

	buffer_t(buffer_t&& other) noexcept
	{
		data = std::move(other.data);
		length = other.length;
	}

	buffer_t& operator=(buffer_t&& other) noexcept
	{
		data = std::move(other.data);
		length = other.length;
	}

	std::unique_ptr<char> data;
	size_t length;
};

class TestCase {
public:
	buffer_t testcase(size_t seed);
};