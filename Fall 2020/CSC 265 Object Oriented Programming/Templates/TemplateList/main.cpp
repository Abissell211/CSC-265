#include <iostream>

#include "List.h"

using namespace std;

int main(void)
{
  List<int> temp;

  temp.insert(10);
  temp.insert(7);
  
  temp.print();
  system("PAUSE");
  
  return 0;
}
