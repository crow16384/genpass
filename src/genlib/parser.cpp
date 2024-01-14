#include "parser.hpp"

Tmpl Parser::parse(const string& s) {
    Tmpl result;

    PwdTmpl t = std::make_pair(PTP::Error, 0);
    bool first = true;

    for (char c : s) {
        if (isalpha(c)) {

            if (first) {
                first = !first;
            } else {
                result.push_back(t);
            }

            t = {PTP::Error, 0};
            switch (c)
            {
                case 'W':
                    t.first = PTP::UWord;
                    break;
                case 'w':
                    t.first = PTP::Word;
                    break;
                case 'd':
                    t.first = PTP::Digits;
                    break;
                case 's':
                    t.first = PTP::Special;
                    break;
                default:
                    t.first = PTP::Error;
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