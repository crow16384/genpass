#ifndef PASSWORD_H
#define PASSWORD_H

#include <vector>
#include <string>

using std::pair;
using std::string;
using std::vector;

#ifdef _MSC_VER
typedef unsigned int uint;
#endif

#ifdef __APPLE__
typedef unsigned int uint;
#endif

class Password
{
public:
    // Password Template Part
    enum PTP
    {
        Error,
        UWord,  // Uppercase word     'W'
        Word,   // Lowcase word       'w'
        Digits, // Digits             'd'
        Special // Special characters 's'
    };

    typedef pair<PTP, uint> PwdTmpl;
    typedef vector<PwdTmpl> Tmpl;

    Tmpl parts;
};

#endif
