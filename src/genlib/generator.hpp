#ifndef GENERATOR_H
#define GENERATOR_H

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

    const size_t vowels_len = strlen(vowels);
    const size_t consonants_len = strlen(consonants);
    const size_t special_len = strlen(special);
    const size_t digits_len = strlen(digits);

    string make_part(PasswordPart);

    string make_word(size_t);
    string make_upcased_word(size_t);
    string make_digits(size_t);
    string make_special(size_t);

public:
    string generate(Template &);
};

#endif