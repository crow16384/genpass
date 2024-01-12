#ifndef PARSER_H
#define PARSER_H

#include "password.hpp"

struct Parser {
public:
    static Password::Tmpl parse(const string& s);
};

#endif
