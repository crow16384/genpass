#include "generator.hpp"

using std::string;

string PasswordGenerator::make_part(PasswordPart part) {
    string res;
    auto [password_type, len] = part;

    switch (password_type) {
        case PasswordPartType::Word:
            res.append(make_word(len));
            break;
        case PasswordPartType::UWord:
            res.append(make_upcased_word(len));
            break;
        case PasswordPartType::Digits:
            res.append(make_digits(len));
            break;
        case PasswordPartType::Special:
            res.append(make_special(len));
            break;
        default:
            res.append(string(len, '*'));
            break;
    }
    return res;
}

string PasswordGenerator::make_word(const size_t len) {
    string res;

    for (unsigned int i = 0; i < len; i++) {
        if (i % 2 == 0) res.push_back(consonants[consonants_r()]);
        else res += vowels[vowels_r()];
    }
    return res;
}

string PasswordGenerator::make_upcased_word(const size_t len) {
    auto res = PasswordGenerator::make_word(len);
    
    if (!res.empty())
        res[0] = static_cast<char>(toupper(res[0]));

    return res;
}

string PasswordGenerator::make_digits(const size_t len) {
    string res;

    for (unsigned int i = 0; i < len; i++) {
        res.push_back(digits[digits_r()]);
    }

    return res;
}

string PasswordGenerator::make_special(const size_t len) {
    string res;

    for (unsigned int i = 0; i < len; i++) {
        res.push_back(special[special_r()]);
    }

    return res;
}

string PasswordGenerator::generate(Template& v) {
    string password;

    for (auto elem: v) {
        password.append(make_part(elem));
    }

    return password;
}