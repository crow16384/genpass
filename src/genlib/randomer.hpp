#pragma once

#include <random>

using namespace std;

class Rand {
    mt19937 gen_;
    uniform_int_distribution<size_t> dist_;
public:
    explicit Rand(const size_t max) :
            gen_(random_device{}()), dist_(0, max-1) {}

    size_t  operator()() {
        return dist_(gen_);
    }
};
