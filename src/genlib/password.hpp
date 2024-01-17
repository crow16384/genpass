#pragma once

#include <vector>
#include <string>

using std::pair;
using std::string;
using std::vector;

enum class PasswordPartType
{
    Error,
    UWord,  // Uppercase word     'W'
    Word,   // Lowercase word     'w'
    Digits, // Digits             'd'
    Special // Special characters 's'
};

typedef pair<PasswordPartType, unsigned int> PasswordPart;
typedef vector<PasswordPart> Template;

struct PasswordTemplate
{
    Template parts;
};
