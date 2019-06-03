#include <Table.h>
#include "TableCellRangeException.h"

core::TableCellRangeException::TableCellRangeException()
        : std::invalid_argument(
        "Invalid table cell. Table cells start from 1.") {
}
