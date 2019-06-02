#pragma once

#include <string>
#include <Table.h>

namespace serialization::csv {

    core::Table deserialize(std::istream &stream);

    core::Table deserialize(std::string &serialized);

    void serialize(std::ostream &stream, const core::Table &table);

    std::string serialize(const core::Table &table);

    std::string extract(std::istream &istream, char previousChar);
}
