#include "parser.hpp"

const std::map<char, PasswordPartType> Parser::pt{
    {'W', PasswordPartType::UWord},
    {'w', PasswordPartType::Word},
    {'d', PasswordPartType::Digits},
    {'s', PasswordPartType::Special},
};

PasswordTemplate Parser::parse(const std::string& s) {
  PasswordTemplate result;
  std::istringstream ss{s};
  char c;
  unsigned int n;
  result.reserve(static_cast<std::size_t>(s.length() / 2) + 1);

  while (ss >> c >> n) {
    PasswordPart part;
    try {
      part.first = pt.at(c);
      if (n > 255)
        throw std::out_of_range("invalid n value for 'Wwsd' parameter(s)");
      part.second = n;
    } catch (const std::out_of_range&) {
      part.first = PasswordPartType::Error;
      part.second = 1;
    }
    result.push_back(std::move(part));
  }

  return result;
}