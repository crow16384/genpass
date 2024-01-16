#ifndef RANDOMER_HPP
#define RANDOMER_HPP

#include <random>

class Randomer {
    // random seed by default
    std::mt19937 gen_;
    std::uniform_int_distribution<size_t> dist_;
public:
    Randomer(const size_t min, const size_t max) :
            gen_(std::random_device{}()), dist_(min, max-1) {}

    size_t  operator()() {
        return dist_(gen_);
    }
};

#endif //RANDOMER_HPP
