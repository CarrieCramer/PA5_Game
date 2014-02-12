#include <iostream>
using namespace std;

class Invalid_Input
{
public:
 
 Invalid_Input(char * in_ptr): msg_ptr(in_ptr) {}
  const char * const msg_ptr;
 
private:
  Invalid_Input(); //No default construction
};
