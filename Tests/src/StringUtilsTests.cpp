#include <catch.hpp>
#include <Strings.h>

TEST_CASE("splitBySpaces works correctly", "[StringUtils]") {
    std::string s1 = "lorem ipsum dolor              sit  \t\n amet";
    std::vector<std::string> split1 = Utils::Strings::splitBySpaces(s1);
    REQUIRE(split1[0] == "lorem");
    REQUIRE(split1[1] == "ipsum");
    REQUIRE(split1[2] == "dolor");
    REQUIRE(split1[3] == "sit");
    REQUIRE(split1[4] == "amet");
}