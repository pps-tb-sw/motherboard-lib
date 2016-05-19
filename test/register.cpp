#include "TDCControl.h"
#include "TDCSetup.h"

int main(int argc, char* argv[])
{
  TDCControl c;
  c.Dump();

  TDCSetup s;
  s.Dump(2);

  return 0;
}
