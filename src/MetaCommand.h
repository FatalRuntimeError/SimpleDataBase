#pragma once

#include "InputBuffer.h"

enum class MetaCommandResult {
	SUCCESS,
	UNRECOGNIZED_COMMAND
};

MetaCommandResult do_meta_command(input_buffer* buffer)
{
	if (buffer->buffer == ".exit")
		exit(EXIT_SUCCESS);
	else
		return MetaCommandResult::UNRECOGNIZED_COMMAND;
}