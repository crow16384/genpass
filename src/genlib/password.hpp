// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <vector>

enum class PasswordPartType {
  Error,
  UWord,        // Uppercase word           'W'
  Word,         // Lowercase word            'w'
  Digits,       // Digits                    'd'
  Special       // Special characters        's'
};

using PasswordPart = std::pair<PasswordPartType, unsigned int>;
using PasswordTemplate = std::vector<PasswordPart>;
