#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <iostream>

#define ERROR -1
#define NONE 0
#define INTEGER 1
#define LPAREN 2
#define RPAREN 3
#define PLUS 4
#define MINUS 5
#define MULTIPLY 6
#define DIVIDE 7

class Token
{
private :
  int _type;
  std::string _value;
public:

  Token(): _type(NONE), _value() {}

  int type() const {return _type;}
  const std::string stype() const;
  const std::string& value() const {return _value;}

  std::ostream& print(std::ostream &os) const;
  std::istream& read(std::istream &is);

  friend std::ostream& operator<<(std::ostream &os, const Token &t);
  friend std::istream& operator>>(std::istream &is, Token &t);
};
#endif
