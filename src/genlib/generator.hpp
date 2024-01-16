#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <cstring>
#include <cstdlib>
#include "randomer.hpp"
#include "password.hpp"

using std::string;

class Generator
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

    static size_t rnd_range(size_t); // Generate random number in range from 0 to given len

    string make_word(unsigned int);
    string make_Uword(unsigned int);
    string make_digits(unsigned int);
    string make_special(unsigned int);

public:
    string generate(Template &);
};

#endif