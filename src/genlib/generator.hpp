#pragma once

#include "password.hpp"
#include "randomer.hpp"

#include <cstddef>
#include <map>
#include <string>

class PasswordGenerator {
    static constexpr const char vowels[] = "aeiouy";
    static constexpr const char consonants[] = "bcdfghjklmnpqrsvwxz";
    static constexpr const char special[] = "!@#$%^&*~><(),\\=/;:+-.[]_";
    static constexpr const char digits[] = "0123456789";

    Rand consonants_r{sizeof(consonants) - 1};
    Rand vowels_r{sizeof(vowels) - 1};
    Rand digits_r{sizeof(digits) - 1};
    Rand special_r{sizeof(special) - 1};

    std::string make_part(const PasswordPart& part);
    std::string make_word(std::size_t len);
    std::string make_upcased_word(std::size_t len);
    std::string make_digits(std::size_t len);
    std::string make_special(std::size_t len);

    static inline const std::map<PasswordPartType, std::string (PasswordGenerator::*)(std::size_t)> funs{
        {PasswordPartType::UWord, &PasswordGenerator::make_upcased_word},
        {PasswordPartType::Word, &PasswordGenerator::make_word},
        {PasswordPartType::Digits, &PasswordGenerator::make_digits},
        {PasswordPartType::Special, &PasswordGenerator::make_special},
    };

public:
    std::string generate(const PasswordTemplate& tpl);
};
