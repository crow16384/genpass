// SPDX-License-Identifier: GPL-3.0-only

#include "generator.hpp"
#include <cctype>

std::string PasswordGenerator::make_part(const PasswordPart& part) {
    const auto [password_type, len] = part;
    try {
        const auto fn = funs.at(password_type);
        return (this->*fn)(len);
    } catch (...) {
        return std::string(len, '*');
    }
}

std::string PasswordGenerator::make_word(std::size_t len) {
    std::string res;
    res.reserve(len);
    for (std::size_t i = 0; i < len; ++i) {
        res += (i % 2 == 0) ? consonants[consonants_r()] : vowels[vowels_r()];
    }
    return res;
}

std::string PasswordGenerator::make_upcased_word(std::size_t len) {
    auto res = make_word(len);
    if (!res.empty())
        res[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(res[0])));
    return res;
}

std::string PasswordGenerator::make_pronounceable_word(std::size_t len) {
    std::string res;
    res.reserve(len + 2);
    bool consonant_next = true;
    while (res.size() < len) {
        if (consonant_next) {
            const std::size_t idx = cons_unit_r();
            if (idx < n_consonant_digraphs)
                res += consonant_digraphs[idx];
            else
                res += consonants[idx - n_consonant_digraphs];
        } else {
            const std::size_t idx = vowel_unit_r();
            if (idx < n_vowel_digraphs)
                res += vowel_digraphs[idx];
            else
                res += vowels[idx - n_vowel_digraphs];
        }
        consonant_next = !consonant_next;
    }
    res.resize(len);
    return res;
}

std::string PasswordGenerator::make_pronounceable_upcased(std::size_t len) {
    auto res = make_pronounceable_word(len);
    if (!res.empty())
        res[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(res[0])));
    return res;
}

std::string PasswordGenerator::make_digits(std::size_t len) {
    std::string res;
    res.reserve(len);
    for (std::size_t i = 0; i < len; ++i)
        res += digits[digits_r()];
    return res;
}

std::string PasswordGenerator::make_special(std::size_t len) {
    std::string res;
    res.reserve(len);
    for (std::size_t i = 0; i < len; ++i)
        res += special[special_r()];
    return res;
}

std::string PasswordGenerator::generate(const PasswordTemplate& tpl) {
    std::string password;
    for (const auto& part : tpl)
        password += make_part(part);
    return password;
}