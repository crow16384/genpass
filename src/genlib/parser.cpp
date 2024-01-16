#include "parser.hpp"

Template Parser::parse(const string& s) {
    Template result;

    PasswordPart t = std::make_pair(PasswordPartType::Error, 0);
    bool first = true;

    for (char c : s) {
        if (isalpha(c)) {

            if (first) {
                first = !first;
            } else {
                result.push_back(t);
            }

            t = {PasswordPartType::Error, 0};
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
        }

        if (isdigit(c)) {
            t.second = t.second*10 + (c - '0');
        }
    };

    result.push_back(t);

    return result;
}