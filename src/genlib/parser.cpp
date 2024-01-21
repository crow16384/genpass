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
            if (n > 255) throw(std::out_of_range("invalid n value"));
            password_part.second = n;
        } catch (const std::out_of_range&) {
            password_part.first = PasswordPartType::Error,
            password_part.second = 1;
        }
        result.parts.push_back(password_part);
    }

    return result;
}