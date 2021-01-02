#pragma once

#include <cstdint>
#include "Row.h"

namespace DB
{
	const uint32_t PageSize = 4096;
	const uint32_t TableMaxPages = 100;
	const uint32_t RowsPerPage = PageSize / RowSize;
	const uint32_t TableMaxRows = TableMaxPages * RowsPerPage;

	struct table {
		uint32_t num_rows;
		char* pages[TableMaxPages];
	};

	table* new_table()
	{
		table* table = new DB::table;
		table->num_rows = 0;
		for (uint32_t i = 0; i < TableMaxPages; i++)
			table->pages[i] = nullptr;

		return table;
	}

	char* row_slot(table* table, uint32_t row_num)
	{
		uint32_t page_num = row_num / RowsPerPage;
		char* page = table->pages[page_num];

		if (page == nullptr)
			page = table->pages[page_num] = new char[PageSize];

		uint32_t row_offset = row_num % RowsPerPage;
		uint32_t byte_offset = row_offset * RowSize;
		return page + byte_offset;
	}
}