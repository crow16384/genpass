#pragma once

#include "randomer.hpp"
#include "password.hpp"

#include <string>
#include <cstring>
#include <map>

using std::string;

class PasswordGenerator
{
private:
    const char *vowels = "aeiouy";
    const char *consonants = "bcdfghjklmnpqrsvwxz";
    const char *special = "!@#$%^&*~><(),\\=/;:+-.[]_";
    const char *digits = "0123456789";

    // Random number generators
    Rand consonants_r{strlen(consonants)};
    Rand vowels_r{strlen(vowels)};
    Rand digits_r{strlen(digits)};
    Rand special_r{strlen(special)};

    string make_part(PasswordPart);

    string make_word(size_t);
    string make_upcased_word(size_t);
    string make_digits(size_t);
    string make_special(size_t);

    static inline std::map<PasswordPartType, string (PasswordGenerator::*)(size_t)> funs {
        {PasswordPartType::UWord, &PasswordGenerator::make_upcased_word},
        {PasswordPartType::Word, &PasswordGenerator::make_word},
        {PasswordPartType::Digits, &PasswordGenerator::make_digits}, 
        {PasswordPartType::Special, &PasswordGenerator::make_special} 
    };
public:
    string generate(PasswordTemplate &);

};
