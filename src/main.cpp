#include <iostream>
#include <cstdlib>
#include <spdlog_easy.hpp>
#include "a.h"
#include "b/b.h"

int main()
{
    spdlog::easy::init();
    LOG(info, "test");
    A a;
    B b;
    a.run();
    return EXIT_SUCCESS;
}
