#pragma once

#include <sstream>
#include "InputBuffer.h"
#include "Table.h"

namespace DB
{
	enum class PrepareResult
	{
		SUCCESS,
		UNRECOGNIZED_STATEMENT,
		SYNTAX_ERROR
	};

	enum class StatementType
	{
		INSERT,
		SELECT
	};

	enum class ExecuteResult
	{
		SUCCESS,
		TABLE_FULL
	};

	struct statement
	{
		row row_to_insert;
		StatementType type;
	};

	PrepareResult prepare_statement(input_buffer* buffer, statement* statement)
	{
		if (buffer->buffer.find("insert") == 0)
		{
			statement->type = StatementType::INSERT;

			std::stringstream tokenizer(buffer->buffer.substr(7));
			tokenizer >> statement->row_to_insert.id;
			tokenizer >> statement->row_to_insert.username;
			tokenizer >> statement->row_to_insert.email;

			if (tokenizer.fail())
				return PrepareResult::SYNTAX_ERROR;

			return PrepareResult::SUCCESS;
		}

		if (buffer->buffer.find("select") == 0)
		{
			statement->type = StatementType::SELECT;
			return PrepareResult::SUCCESS;
		}

		return PrepareResult::UNRECOGNIZED_STATEMENT;
	}

	ExecuteResult execute_insert(statement* statement, table* table)
	{
		if (table->num_rows >= TableMaxRows)
			return ExecuteResult::TABLE_FULL;

		row* row_to_insert = &(statement->row_to_insert);

		serialize_row(row_to_insert, row_slot(table, table->num_rows));
		table->num_rows += 1;

		return ExecuteResult::SUCCESS;
	}

	ExecuteResult execute_select(statement* statement, table* table)
	{
		row row;
		for (uint32_t i = 0; i < table->num_rows; i++)
		{
			deserialize_row(row_slot(table, i), &row);
			print_row(&row);
		}

		return ExecuteResult::SUCCESS;
	}

	ExecuteResult execute_statement(statement* statement, table* table) {
		switch (statement->type) {
		case (StatementType::INSERT):
			return execute_insert(statement, table);
		case (StatementType::SELECT):
			return execute_select(statement, table);
		}
	}
}