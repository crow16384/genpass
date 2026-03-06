// SPDX-License-Identifier: GPL-3.0-only

#include "randomer.hpp"

Rand::Rand(std::size_t max)
    : gen_(std::random_device{}()), dist_(0, max > 0 ? max - 1 : 0) {}

std::size_t Rand::operator()() { return dist_(gen_); }
