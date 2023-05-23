// Error checking code - check for valid integer

#include <iostream>

using namespace std;

int main()
{
   int num = 0;
   
   cout << "Please enter an integer: ";
   
   // Notes:
   //      1.  cin >> num   returns a true/false value
   //      2.  peek is used to make sure they didn't type 'extra stuff'
   //      3.  clear is used to take the stream out of 'fail state'
   //      4.  ignore is used to remove chars from stream   
   while(!(cin >> num) || cin.peek() != '\n')
   {
     cout << "Please enter an INTEGER: ";
     cin.clear();
     cin.ignore(30000, '\n');            
   }
         
   cout << "You finally listened!  You entered: " << num << endl;

   system("PAUSE");
   return 0;   
}
