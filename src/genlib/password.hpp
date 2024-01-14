#ifndef PASSWORD_H
#define PASSWORD_H

#include <vector>
#include <string>

using std::pair;
using std::string;
using std::vector;

enum class PTP
{
    Error,
    UWord,  // Uppercase word     'W'
    Word,   // Lowcase word       'w'
    Digits, // Digits             'd'
    Special // Special characters 's'
};

typedef pair<PTP, unsigned int> PwdTmpl;
typedef vector<PwdTmpl> Tmpl;

struct PasswordTemplate
{
    Tmpl parts;
};

#endif
