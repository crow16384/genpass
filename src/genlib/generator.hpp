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
    static constexpr std::size_t n_digits = 10;
    static constexpr std::size_t n_special = 28;
    // English digraphs for pronounceable passwords
    static constexpr const char* consonant_digraphs[] = {"th", "sh", "ch", "qu", "wh", "ph", "ck", "ng"};
    static constexpr const char* vowel_digraphs[] = {"oo", "ee", "ea", "ai", "oa"};
    static constexpr std::size_t n_consonant_digraphs = sizeof(consonant_digraphs) / sizeof(consonant_digraphs[0]);
    static constexpr std::size_t n_vowel_digraphs = sizeof(vowel_digraphs) / sizeof(vowel_digraphs[0]);
    static constexpr std::size_t n_consonant_units = n_consonant_digraphs + (sizeof(consonants) - 1);
    static constexpr std::size_t n_vowel_units = n_vowel_digraphs + (sizeof(vowels) - 1);

    Rand consonants_r{sizeof(consonants) - 1};
    Rand vowels_r{sizeof(vowels) - 1};
    Rand digits_r{n_digits};
    Rand special_r{n_special};
    Rand cons_unit_r{n_consonant_units};
    Rand vowel_unit_r{n_vowel_units};

    std::string make_part(const PasswordPart& part);
    std::string make_word(std::size_t len);
    std::string make_upcased_word(std::size_t len);
    std::string make_pronounceable_word(std::size_t len);
    std::string make_pronounceable_upcased(std::size_t len);
    std::string make_digits(std::size_t len);
    std::string make_special(std::size_t len);

    static inline const std::map<PasswordPartType, std::string (PasswordGenerator::*)(std::size_t)> funs{
        {PasswordPartType::UWord, &PasswordGenerator::make_upcased_word},
        {PasswordPartType::Word, &PasswordGenerator::make_word},
        {PasswordPartType::PronounceableU, &PasswordGenerator::make_pronounceable_upcased},
        {PasswordPartType::Pronounceable, &PasswordGenerator::make_pronounceable_word},
        {PasswordPartType::Digits, &PasswordGenerator::make_digits},
        {PasswordPartType::Special, &PasswordGenerator::make_special},
    };

public:
    std::string generate(const PasswordTemplate& tpl);
};
