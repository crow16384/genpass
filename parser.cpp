#include "parser.hpp"

Password::Tmpl Parser::parse(const string& s) {
    Password::Tmpl result;

    Password::PwdTmpl t = std::make_pair(Password::Error, 0);
    bool first = true;

    for (char c : s) {
        if (isalpha(c)) {

            if (first) {
                first = !first;
            } else {
                result.push_back(t);
            }

            t = {Password::Error, 0};
            switch (c)
            {
                case 'W':
                    t.first = Password::UWord;
                    break;
                case 'w':
                    t.first = Password::Word;
                    break;
                case 'd':
                    t.first = Password::Digits;
                    break;
                case 's':
                    t.first = Password::Special;
                    break;
                default:
                    t.first = Password::Error;
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