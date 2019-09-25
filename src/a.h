#pragma once
#include <memory>

class AImpl;

class A
{
public:
    A();

    ~A() = default;

    void run();

private:
    std::shared_ptr<AImpl> impl;
};

