#include "Token.hpp"

using namespace std;

// skips over all whitespace characters before next lexeme
void skipWS(istream &is)
{
  char ch;
  is >> ch;  // a bit of trick here ... reads next non-WS char
  if (is)
    is.putback(ch);
}

static int **DFA=nullptr;

istream&
Token::read(istream &is)
{
  // DFA not built yet? build it!
  if (DFA==nullptr)
    {
      // build 2-D array for DFA.
      DFA = new int*[DIVIDE+1];
      for (int state=0; state<=DIVIDE; state++)
	{
	  DFA[state]=new int[256];
	  for (int ch=0; ch<256; ch++)
	    DFA[state][ch]=-1;
	}

      // state 0 (start) transitions
      for (char ch='0'; ch<='9'; ch++)
	{
	  DFA[0][(int) ch]=INTEGER;
	}

      DFA[0][(int) '('] = LPAREN;
      DFA[0][(int) ')'] = RPAREN;
      DFA[0][(int) '+'] = PLUS;
      DFA[0][(int) '-'] = MINUS;
      DFA[0][(int) '*'] = MULTIPLY;
      DFA[0][(int) '/'] = DIVIDE;
      
      // state 1 (INTEGER) transitions
      for (char ch='0'; ch<='9'; ch++)
	{
	  DFA[INTEGER][(int) ch]=INTEGER;
	}
      
    }

  _value=""; // start token val as empty
  char ch; // character to consider adding to Token. 
  
  skipWS(is);
  if (!is)
    return is;
  
  int curr=0;  // current state - initialized as start state
  int prev=-1; // previous state; when starting, we don't have one. 

  // keep following transitions until we can't legally do so 
  while(curr!=-1)
    {
      // read next character (without skipping whitespace)
      ch=is.get();

      //      cout << "ch=" << ch << ", as int = " << (int) ch << endl;
      
      // update state(s)
      prev=curr;
      curr=DFA[curr][(int)ch];

      // add char to Token value if still in legal state. 
      if (curr!=-1)
        _value+=ch;
    }
  // last char read was not part of this token, so put it back ...
  if (is)
    
    is.putback(ch);

  _type=prev;

  return is;
}

const string 
Token::stype() const
{
  switch(_type)
  {
    case INTEGER:
      return "INTEGER";
    case LPAREN:
      return "LPAREN";
    case RPAREN:
      return "RPAREN";
    case PLUS:
      return "PLUS";
    case MINUS:
      return "MINUS";
    case MULTIPLY:
      return "MULTIPLY"; 
    case DIVIDE:
      return "DIVIDE"; 
    default: 
      return "ERROR";
  }
}
ostream& Token::print(std::ostream &os) const
{
  os<< _value; 
  return os;
}

ostream& operator<<(ostream &os, const Token &t)
{
  return t.print(os);
}

istream& operator>>(istream &is, Token &t)
{
  return t.read(is);
}
