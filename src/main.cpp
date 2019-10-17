#include <iostream>
#include <cstdlib>
#include <spdlog_easy.hpp>
#include "a.h"
#include "b/b.h"
#include <boost/filesystem.hpp>
using namespace std;

int main()
{
    spdlog::easy::init();
    LOG(info, "test");
    A a;
    B b;
    a.run();
    cout << boost::filesystem::current_path() << endl;
    return EXIT_SUCCESS;
}
