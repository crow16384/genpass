#include "generator.hpp"

#include <iostream> 
unsigned int Generator::rnd_range(size_t ub) {
    return (unsigned int) rand() % ub;
}

string Generator::make_word(const unsigned int len) {
    std::string res = "";

    for (unsigned int i = 0; i < len; i++) {
        if (i % 2 == 0) {
            res += consonants[rnd_range(consonants_len)];
        } else {
            res += vowels[rnd_range(vowels_len)];
        }
    }

    return res;
}

string Generator::make_uword(const unsigned int len) {
    auto res = Generator::make_word(len);
    
    if (!res.empty()) {
        res[0] = toupper(res[0]);   
    }

    return res;
}

string Generator::make_digits(const unsigned int len) {
    std::string res = "";

    for (unsigned int i = 0; i < len; i++) {
        res += digits[rnd_range(digits_len)];
    }

    return res;
}

string Generator::make_special(const unsigned int len) {
    std::string res = "";

    for (unsigned int i = 0; i < len; i++) {
        res += special[rnd_range(special_len)];
    }

    return res;
}

string Generator::generate(Password::Tmpl& v) {
    string password;

    for (auto elem : v) {
        switch (elem.first) {
            case Password::Word:
                password += make_word(elem.second);
                break;
            case Password::UWord:
                password += make_uword(elem.second);
                break;
            case Password::Digits:
                password += make_digits(elem.second);
                break;
            case Password::Special:
                password += make_special(elem.second);
                break;
            default:
                password += std::string(elem.second, '*');
                break;
        }
    }

    return password;
}