#include "parser.hpp"

PasswordTemplate Parser::parse(const string& s) {
    PasswordTemplate result;
    std::stringstream ss{s};
    char c;
    size_t n;
    PasswordPart password_part;

    while(ss >> c >> n) {
        try{
            password_part.first = pt.at(c);
            password_part.second = n;
        } catch (std::out_of_range&) {}
        result.parts.push_back(password_part);
    }

    return result;
}