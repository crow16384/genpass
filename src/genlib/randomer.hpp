#ifndef RANDOMER_H
#define RANDOMER_H

#include <random>

class Rand {
    // random seed by default
    std::mt19937 gen_;
    std::uniform_int_distribution<size_t> dist_;
public:
    explicit Rand(const size_t max) :
            gen_(std::random_device{}()), dist_(0, max-1) {}

    size_t  operator()() {
        return dist_(gen_);
    }
};

#endif //RANDOMER_H
