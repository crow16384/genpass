#include "parser.hpp"

PasswordTemplate Parser::parse(const string& s) {
    PasswordTemplate result;
    std::stringstream ss{s};
    char c;
    size_t n;
    PasswordPart t;

    while(ss >> c >> n) {
        switch (c)
        {
            case 'W':
                t.first = PasswordPartType::UWord;
                break;
            case 'w':
                t.first = PasswordPartType::Word;
                break;
            case 'd':
                t.first = PasswordPartType::Digits;
                break;
            case 's':
                t.first = PasswordPartType::Special;
                break;
            default:
                t.first = PasswordPartType::Error;
                break;
        }
        t.second = n;
        result.parts.push_back(t);
    }

    return result;
}