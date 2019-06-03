#include <string>
#include <Strings.h>
#include "CsvFormatter.h"
#include "exceptions/UnknownElementException.h"
#include <TokenType.h>
#include <TokenValues.h>

namespace serialization {
    core::Table CsvFormatter::deserialize(std::istream &istream) {
        std::vector<core::Token> tokens = tokenizeSerializedTable(istream);
        return parseTable(tokens);
    }

    std::string CsvFormatter::extractNextCellElement(std::istream &istream, char currentChar) {
        const char stringSeparator = core::TOKEN_VALUES[(int) core::TokenType::STRING_SEPARATOR].value[0];
        const char rowSeparator = core::TOKEN_VALUES[(int) core::TokenType::ROW_SEPARATOR].value[0];
        const char colSeparator = core::TOKEN_VALUES[(int) core::TokenType::COLUMN_SEPARATOR].value[0];
        const char escapeChar = core::TOKEN_VALUES[(int) core::TokenType::ESCAPE_CHARACTER].value[0];

        std::string result(1, currentChar);

        bool isReadingString = currentChar == stringSeparator;
        bool isEscaped = false;

        while ((istream.get(currentChar)
                && (isReadingString || (currentChar != colSeparator && currentChar != rowSeparator)))) {
            if (currentChar == stringSeparator && !isEscaped) {
                isReadingString = false;
            } else {
                isEscaped = currentChar == escapeChar;
            }
            result += currentChar;
        }

        istream.unget();

        return result;
    }

    std::string CsvFormatter::serialize(const core::Table &table) {
        const std::string rowSeparator = core::TOKEN_VALUES[(int) core::TokenType::ROW_SEPARATOR].value;
        const std::string colSeparator = core::TOKEN_VALUES[(int) core::TokenType::COLUMN_SEPARATOR].value;

        std::vector<std::vector<std::string>> cells =
                table.getAllCellValues();

        std::string serialized;

        for (const std::vector<std::string> &row : cells) {
            for (const std::string &cell : row) {
                serialized += cell + colSeparator;
            }
            serialized += rowSeparator;
        }

        return serialized;
    }

    std::vector<core::Token> CsvFormatter::tokenizeSerializedTable(std::istream &istream) {
        std::vector<core::Token> tokens;

        const char rowSeparator = core::TOKEN_VALUES[(int) core::TokenType::ROW_SEPARATOR].value[0];
        const char colSeparator = core::TOKEN_VALUES[(int) core::TokenType::COLUMN_SEPARATOR].value[0];

        char currentChar;
        while (istream.get(currentChar)) {
            if (currentChar == rowSeparator) {
                tokens.emplace_back(core::TokenType::ROW_SEPARATOR, std::string(1, rowSeparator));
            } else if (currentChar == colSeparator) {
                tokens.emplace_back(core::TokenType::COLUMN_SEPARATOR, std::string(1, colSeparator));
            } else if (std::isspace(currentChar)) {
                continue;
            } else {
                std::string cellElement = extractNextCellElement(istream, currentChar);
                std::string unescapedElement = utils::Strings::unescape(
                        utils::Strings::removeQuotes(cellElement));
                tokens.emplace_back(core::TokenType::TABLE_CELL, unescapedElement);
            }
        }

        return tokens;
    }

    core::Table CsvFormatter::parseTable(const std::vector<core::Token> &tokens) {
        core::Table table;
        long tableCol = 0;
        long tableRow = 0;

        for (const core::Token &currentToken : tokens) {
            switch (currentToken.type) {
                case core::TokenType::COLUMN_SEPARATOR: {
                    tableCol++;
                    break;
                }
                case core::TokenType::ROW_SEPARATOR: {
                    tableRow++;
                    tableCol = 0;
                    break;
                }
                case core::TokenType::TABLE_CELL: {
                    table.setCellValue(tableRow, tableCol, currentToken.value);
                    break;
                }
                default:
                    throw UnknownElementException(tableRow, tableCol, currentToken.value);
            }
        }

        return table;
    }

}