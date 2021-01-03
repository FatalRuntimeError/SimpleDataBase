#include "InputBuffer.h"
#include "MetaCommand.h"
#include "Statement.h"

void print_prompt()
{
	std::cout << "db > ";
}

using namespace DB;

int main(int argc, char** argv)
{
	table* table = new_table();
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
			break;

		case PrepareResult::SYNTAX_ERROR:
			std::cout << "Syntax error. Could not parse statement." << std::endl;
			continue;

		case PrepareResult::UNRECOGNIZED_STATEMENT:
			std::cout << "Unrecognized keyword at start of '" << input_buffer->buffer << "'" << std::endl;
			continue;

		case PrepareResult::STRING_TOO_LONG:
			std::cout << "String is too long." << std::endl;
			continue;

		case PrepareResult::NEGATIVE_ID:
			std::cout << "ID must be positive." << std::endl;
			continue;

		default:
			break;
		}

		switch (execute_statement(&statement, table))
		{
		case ExecuteResult::SUCCESS:
			std::cout << "Executed." << std::endl;
			break;
		case ExecuteResult::TABLE_FULL:
			std::cout << "Error: Table full." << std::endl;
			break;
		default:
			break;
		}
	}

	return 0;
}