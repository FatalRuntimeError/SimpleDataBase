#pragma once

#include <iostream>
#include <istream>
#include <string>
#include <cstdlib>

namespace DB
{
	struct input_buffer {
		std::string buffer;
		size_t input_length;
	};

	input_buffer* new_input_buffer()
	{
		input_buffer* buffer = new input_buffer;
		buffer->buffer = "";
		buffer->input_length = 0;

		return buffer;
	}

	void read_input(input_buffer* buffer)
	{
		if (std::getline(std::cin, buffer->buffer).fail())
		{
			printf("Error reading input\n");
			exit(EXIT_FAILURE);
		}

		buffer->input_length = buffer->buffer.length() - 1;
	}

	void close_input_buffer(input_buffer* buffer)
	{
		delete buffer;
	}
}