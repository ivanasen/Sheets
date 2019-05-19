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
    std::vector<unsigned long> matches = TableFormulaCalculator::matchBrackets(tokens1);
    bool p = false;
}