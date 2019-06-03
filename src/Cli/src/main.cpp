#include <iostream>
#include "SheetsClient.h"
#include <iostream>

int main() {
    cli::SheetsClient client(std::cout, std::cin);
    client.start();

    return 0;
}
