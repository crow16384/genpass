// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <cstddef>
#include <random>

class Rand {
    std::mt19937 gen_;
    std::uniform_int_distribution<std::size_t> dist_;

public:
    explicit Rand(std::size_t max);
    std::size_t operator()();
};
