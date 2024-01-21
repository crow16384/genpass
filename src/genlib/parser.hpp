#pragma once

#include "password.hpp"
#include <sstream>

struct Parser {
    static PasswordTemplate parse(const string& s);
};

