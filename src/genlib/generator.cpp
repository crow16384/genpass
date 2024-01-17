#include "generator.hpp"

string PasswordGenerator::make_part(PasswordPart part) {
    std::string res;
    auto [password_type, len] = part;

    switch (password_type) {
        case PasswordPartType::Word:
            res += make_word(len);
            break;
        case PasswordPartType::UWord:
            res += make_upcased_word(len);
            break;
        case PasswordPartType::Digits:
            res += make_digits(len);
            break;
        case PasswordPartType::Special:
            res += make_special(len);
            break;
        default:
            res += std::string(len, '*');
            break;
    }
    return res;
}

string PasswordGenerator::make_word(const size_t len) {
    std::string res;
    Rand consonants_r{consonants_len};
    Rand vowels_r{vowels_len};

    for (unsigned int i = 0; i < len; i++) {
        if (i % 2 == 0) res += consonants[consonants_r()];
        else res += vowels[vowels_r()];
    }
    return res;
}

string PasswordGenerator::make_upcased_word(const size_t len) {
    auto res = PasswordGenerator::make_word(len);
    
    if (!res.empty())
        res[0] = static_cast<char>(std::toupper(res[0]));

    return res;
}

string PasswordGenerator::make_digits(const size_t len) {
    std::string res;
    Rand digits_r{digits_len};

    for (unsigned int i = 0; i < len; i++) {
        res += digits[digits_r()];
    }

    return res;
}

string PasswordGenerator::make_special(const size_t len) {
    std::string res;
    Rand special_r{special_len};

    for (unsigned int i = 0; i < len; i++) {
        res += special[special_r()];
    }

    return res;
}

string PasswordGenerator::generate(Template& v) {
    string password;

    for (auto elem: v) {
        password += make_part(elem);
    }

    return password;
}