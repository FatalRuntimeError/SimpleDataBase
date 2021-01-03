#pragma once
#include <cstdint>

namespace DB
{
	const int Username = 32;
	const int Email = 255;

	struct row
	{
		uint32_t id;
		char username[Username + 1];
		char email[Email + 1];
	};

	const uint32_t IDSize = sizeof(row::id);
	const uint32_t UsernameSize = sizeof(row::username);
	const uint32_t EmailSize = sizeof(row::email);
	const uint32_t IDOffset = 0;
	const uint32_t UsernameOffset = IDOffset + IDSize;
	const uint32_t EmailOffset = UsernameOffset + UsernameSize;
	const uint32_t RowSize = IDSize + UsernameSize + EmailSize;

	void serialize_row(row* source, char* destination)
	{
		std::memcpy(destination, &(source->id), IDSize);
		std::memcpy(destination + UsernameOffset, &(source->username), UsernameSize);
		std::memcpy(destination + EmailOffset, &(source->email), EmailSize);
	}

	void deserialize_row(char* source, row* destination)
	{
		memcpy(&(destination->id), source + IDOffset, IDSize);
		memcpy(&(destination->username), source + UsernameOffset, UsernameSize);
		memcpy(&(destination->email), source + EmailOffset, EmailSize);
	}

	void print_row(row* row)
	{
		std::cout << '(' << row->id << ", " << row->username << ", " << row->email << ')' << std::endl;
	}
}