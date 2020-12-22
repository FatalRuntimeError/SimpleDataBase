#include "InputBuffer.h"
#include "MetaCommand.h"
#include "Statement.h"

void print_prompt()
{
	std::cout << "db > ";
}

int main(int argc, char** argv)
{
	input_buffer* input_buffer = new_input_buffer();

	bool is_running = true;

	while (is_running)
	{
		print_prompt();
		read_input(input_buffer);

		if (input_buffer->buffer[0] == '.')
		{
			switch (do_meta_command(input_buffer))
			{
			case MetaCommandResult::SUCCESS:
				continue;

			case MetaCommandResult::UNRECOGNIZED_COMMAND:
				std::cout << "Unrecognized command '" << input_buffer->buffer << "'" << std::endl;
				continue;

			default:
				break;
			}
		}


		statement statement;
		switch (prepare_statement(input_buffer, &statement))
		{
		case PrepareResult::SUCCESS:
			execute_statement(&statement);
			break;

		case PrepareResult::UNRECOGNIZED_STATEMENT:
			std::cout << "Unrecognized keyword at start of '" << input_buffer->buffer << "'" << std::endl;
			continue;

		default:
			break;
		}
	}

	return 0;
}