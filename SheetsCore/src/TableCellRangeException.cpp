#include <Table.h>
#include "TableCellRangeException.h"

SheetsCore::TableCellRangeException::TableCellRangeException()
        : std::invalid_argument(
        "Invalid table cell. Table cells range from 1 to " + std::to_string(Table::MAX_SIZE)) {
}
