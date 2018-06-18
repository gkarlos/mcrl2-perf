#include <iostream>

#include "mcrl2/atermpp/aterm_int.h"

using namespace std;
using namespace atermpp;

int main()
{
  aterm_int anint(10);
  cout << "Created an aterm_int: " << anint << endl;
  return 0;
}
