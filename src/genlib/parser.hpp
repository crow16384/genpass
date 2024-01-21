#pragma once

#include "password.hpp"
#include <sstream>
#include <map>

struct Parser {
    static PasswordTemplate parse(const string& s);

    static inline std::map<char, PasswordPartType> pt {
        {'W',PasswordPartType::UWord},
        {'w',PasswordPartType::Word},
        {'d',PasswordPartType::Digits},
        {'s',PasswordPartType::Special}
    };
};
