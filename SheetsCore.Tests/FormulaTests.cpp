#include <catch.hpp>
#include "../SheetsCore/src/StringUtils.cpp"
#include "../SheetsCore/src/TableFormulaCalculator.h"
#include "../SheetsCore/src/Token.h"

using namespace SheetsCore;

TEST_CASE("tokenizeFormula", "[TableFormulaCalculator]") {
    std::string f1 = "= 3 + 5";
    std::vector<Token> tokens1 = TableFormulaCalculator::tokenizeFormula(f1);
    REQUIRE(tokens1[0] == Token(TokenType::NUMBER, "3"));
    REQUIRE(tokens1[1] == Token(TokenType::PLUS, "+"));
    REQUIRE(tokens1[2] == Token(TokenType::NUMBER, "5"));

    std::string f2 = "= ( 3 + 5 - R3C345 ) * R2C1 - 5";
    std::vector<Token> tokens2 = TableFormulaCalculator::tokenizeFormula(f2);
    REQUIRE(tokens2[0] == Token(TokenType::OPENING_PARENTHESIS, "("));
    REQUIRE(tokens2[1] == Token(TokenType::NUMBER, "3"));
    REQUIRE(tokens2[2] == Token(TokenType::PLUS, "+"));
    REQUIRE(tokens2[3] == Token(TokenType::NUMBER, "5"));
    REQUIRE(tokens2[4] == Token(TokenType::MINUS, "-"));
    REQUIRE(tokens2[5] == Token(TokenType::IDENTIFIER, "R3C345"));
    REQUIRE(tokens2[6] == Token(TokenType::CLOSING_PARENTHESIS, ")"));
    REQUIRE(tokens2[7] == Token(TokenType::MULTIPLICATION, "*"));
    REQUIRE(tokens2[8] == Token(TokenType::IDENTIFIER, "R2C1"));
    REQUIRE(tokens2[9] == Token(TokenType::MINUS, "-"));
    REQUIRE(tokens2[10] == Token(TokenType::NUMBER, "5"));
}

TEST_CASE("matchBrackets", "[TableFormulaCalculator]") {
    std::string f1 = "= 3 + 5";
    std::vector<Token> tokens1 = TableFormulaCalculator::tokenizeFormula(f1);
    std::vector<unsigned long> matches1 = TableFormulaCalculator::matchBrackets(tokens1);
    for (const unsigned long &match : matches1) {
        REQUIRE(0 == match);
    }

    std::string f2 = "= ( 3 + 5 ) - 34 * ( 23 + 0 * ( 4 ) )";
    std::vector<Token> tokens2 = TableFormulaCalculator::tokenizeFormula(f2);
    std::vector<unsigned long> matches2 = TableFormulaCalculator::matchBrackets(tokens2);
    REQUIRE(0 == matches2[4]);
    REQUIRE(13 == matches2[15]);
    REQUIRE(8 == matches2[16]);
}