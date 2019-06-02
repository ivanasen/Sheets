#include <catch.hpp>
#include <Strings.h>

TEST_CASE("splitBySpaces works correctly", "[StringUtils]") {
    std::string s1 = "lorem ipsum dolor              sit  \t\n amet";
    std::vector<std::string> split1 = utils::Strings::splitBySpaces(s1, 0);
    REQUIRE(split1[0] == "lorem");
    REQUIRE(split1[1] == "ipsum");
    REQUIRE(split1[2] == "dolor");
    REQUIRE(split1[3] == "sit");
    REQUIRE(split1[4] == "amet");
}

TEST_CASE("String escaping works correctly", "[StringUtils]") {
    std::string s1 = "Hello, \"World!?\" \n \t";
    std::string expected1 = R"(Hello, \"World!?\" \n \t)";
    std::string s1Escaped = utils::Strings::escape(s1);
    REQUIRE(expected1 == s1Escaped);
}

TEST_CASE("String unescaping works correctly", "[StringUtils]") {
    std::string s1 = "Pesho,\\\" Gosho \\\n \\\t";
    std::string expected = "Pesho,\" Gosho \n \t";
    std::string s1Unescaped = utils::Strings::unescape(s1);
    REQUIRE(expected == s1Unescaped);
}

