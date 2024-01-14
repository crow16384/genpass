#ifndef PARSER_H
#define PARSER_H

#include "password.hpp"

struct Parser {
    static Tmpl parse(const string& s);
};

#endif
