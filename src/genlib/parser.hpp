// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "password.hpp"
#include <map>
#include <string>

struct Parser {
    static PasswordTemplate parse(const std::string& s);

    static const std::map<char, PasswordPartType> pt;
};
