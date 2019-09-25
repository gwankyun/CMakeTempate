#include "a.h"
#include <spdlog_easy.hpp>

class AImpl
{
public:
    AImpl() = default;

    ~AImpl() = default;

    void run()
    {
        LOG(info);
    }

private:
    int i = 0;
};

A::A()
{
    impl = std::shared_ptr<AImpl>();
}

void A::run()
{
    impl->run();
}
