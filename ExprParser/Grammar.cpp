#include "Grammar.hpp"

#include <cstdlib>

#include "Token.hpp"

int expr(istream &is)
{
  int tval = term(is);

  int pos = is.tellg();

  Token op;
  is >> op;

  if (op.type() != PLUS && op.type()!=MINUS) // no op, must need expr->term
    {
      is.seekg(pos);
      return tval;
    }

  int eval=expr(is);

  if (op.type()==PLUS)
    return tval+eval;
  else // op.type()==MINUS
    return tval-eval;
}

int term(istream &is)
{
  int fval = factor(is);

  int pos = is.tellg();

  Token op;
  is >> op;

  if (op.type() != MULTIPLY && op.type()!=DIVIDE) // no op, must need term->factor
    {
      is.seekg(pos);
      return fval;
    }

  int tval=term(is);

  if (op.type()==MULTIPLY)
    return fval*tval;
  else // op.type()==DIVIDE
    return fval/tval;  
}

int factor(istream &is)
{
  Token next;
  is >> next;

  if (next.type()==INTEGER)
    return atoi(next.value().c_str());

  if (next.type()!=LPAREN)
    {
      cout << "Missing \"(\"" << endl;
      return 0;
    }

  int eval = expr(is);

  is >> next;
  if (next.type()!=RPAREN)
    {
      cout << "Missing \")\"" << endl;
      return 0;
    }

  return eval;
}

 
