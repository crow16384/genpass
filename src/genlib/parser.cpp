#include "parser.hpp"
#include <cctype>
#include <sstream>

const std::map<char, PasswordPartType> Parser::pt{
    {'W', PasswordPartType::UWord},
    {'w', PasswordPartType::Word},
    {'P', PasswordPartType::PronounceableU},
    {'p', PasswordPartType::Pronounceable},
    {'d', PasswordPartType::Digits},
    {'s', PasswordPartType::Special},
};

PasswordTemplate Parser::parse(const std::string& s) {
  PasswordTemplate result;
  std::istringstream ss{s};
  char c;
  unsigned int n;
  result.reserve(static_cast<std::size_t>(s.length() / 2) + 1);

  while (ss >> c) {
    n = 1;  // default length when no digits follow
    if (std::isdigit(static_cast<unsigned char>(ss.peek())))
      ss >> n;
    PasswordPart part;
    try {
      part.first = pt.at(c);
      if (n > 255)
        throw std::out_of_range("invalid n value for 'WwPpds' parameter(s)");
      part.second = n;
    } catch (const std::out_of_range&) {
      part.first = PasswordPartType::Error;
      part.second = 1;
    }
    result.push_back(std::move(part));
  }

  return result;
}