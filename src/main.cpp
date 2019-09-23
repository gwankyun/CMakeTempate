#include <iostream>
#include <cstdlib>
#include <spdlog_easy.hpp>
#include "a.h"

int main()
{
    spdlog::easy::init();
    LOG(info, "test");
    A a;
    return EXIT_SUCCESS;
}
