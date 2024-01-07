#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <string.h>
#include <time.h>
#include <cstdlib>

#include "password.hpp"

using std::string;

class Generator {
private:
    const char* vowels = "aeiouy";
    const char* consonants = "bcdfghjklmnpqrsvwxz";
    const char* special = "!@#$%^&*~><(),\\=/;:+-.[]_";
    const char* digits = "0123456789";

    const size_t vowels_len = strlen(vowels);
    const size_t consonants_len = strlen(consonants);
    const size_t special_len = strlen(special);
    const size_t digits_len = strlen(digits);

    uint rnd_range(size_t); // Generate random number in range from 0 to given len

    string make_word(const uint len);
    string make_uword(const uint len);
    string make_digits(const uint len);
    string make_special(const uint len);
public:
    Generator() { srand(time(0)); } // Initialize RND generator

    string generate(Password::Tmpl&);
};

#endif