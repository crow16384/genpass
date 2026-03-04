#pragma once

#include <vector>

enum class PasswordPartType {
  Error,
  UWord,        // Uppercase word           'W'
  Word,         // Lowercase word            'w'
  PronounceableU,  // Pronounceable uppercase 'P' (th, sh, ch, etc.)
  Pronounceable,   // Pronounceable lowercase 'p'
  Digits,       // Digits                    'd'
  Special       // Special characters        's'
};

using PasswordPart = std::pair<PasswordPartType, unsigned int>;
using PasswordTemplate = std::vector<PasswordPart>;
