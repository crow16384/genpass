#pragma once

#include <string>
#include <cstring>
#include "randomer.hpp"
#include "password.hpp"

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

public:
    string generate(Template &);
};
