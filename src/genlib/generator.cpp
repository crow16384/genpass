#include "generator.hpp"

size_t Generator::rnd_range(const size_t ub) {
    Randomer r{0, ub};
    return r();
}

string Generator::make_word(const unsigned int len) {
    std::string res;

    for (unsigned int i = 0; i < len; i++) {
        if (i % 2 == 0) {
            res += consonants[rnd_range(consonants_len)];
        } else {
            res += vowels[rnd_range(vowels_len)];
        }
    }

    return res;
}

string Generator::make_Uword(const unsigned int len) {
    auto res = Generator::make_word(len);
    
    if (!res.empty()) {
        res[0] = toupper(res[0]);   
    }

    return res;
}

string Generator::make_digits(const unsigned int len) {
    std::string res;

    for (unsigned int i = 0; i < len; i++) {
        res += digits[rnd_range(digits_len)];
    }

    return res;
}

string Generator::make_special(const unsigned int len) {
    std::string res;

    for (unsigned int i = 0; i < len; i++) {
        res += special[rnd_range(special_len)];
    }

    return res;
}

string Generator::generate(Template& v) {
    string password;

    for (auto elem : v) {
        switch (elem.first) {
            case PasswordPartType::Word:
                password += make_word(elem.second);
                break;
            case PasswordPartType::UWord:
                password += make_Uword(elem.second);
                break;
            case PasswordPartType::Digits:
                password += make_digits(elem.second);
                break;
            case PasswordPartType::Special:
                password += make_special(elem.second);
                break;
            default:
                password += std::string(elem.second, '*');
                break;
        }
    }

    return password;
}