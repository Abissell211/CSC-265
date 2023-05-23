#include <iostream>
#include "fraction.h"

using namespace std;

int main(void)
{
  Fraction fraction1;

  fraction1.setsign('+');
  fraction1.setwhole(2);
  fraction1.setnum(3);
  fraction1.setden(4);
  fraction1.display();

  system("PAUSE");
  return 0;
}
