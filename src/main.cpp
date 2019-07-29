#include <iostream>
#include <cstdlib>
#include <spdlog_easy.hpp>

int main()
{
    spdlog::easy::init();
    LOG(info, "test");
    return EXIT_SUCCESS;
}
