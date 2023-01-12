#include <fstream>
#include <iostream>
#include <string>

#include "Grammar.hpp"
#include "Token.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream ifile(argv[1]);
  
  Token t;
  ifile >> t;

  while (ifile)
    {
      cout << t << ": " << t.stype() << "(" << t.type() << ")" << endl;
      ifile >> t;
    }
 /* 
  int val = expr(ifile);

  cout << val << endl;
*/  
  return 0;
}
