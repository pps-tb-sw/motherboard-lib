#include "TDCControl.h"
#include "TDCSetup.h"

int main(int argc, char* argv[])
{
  TDCSetup s;

  // dump the register content before reverting it
  std::cout << "--- Before reversing the register:" << std::endl;
  s.DumpRegister(2);
  std::vector<uint8_t> s_vec = s.GetBytesVector();
  
  TDCSetup s_rev(s_vec, true);
  // dump the register content after reverting it
  std::cout << "--- After reversing the register:" << std::endl;
  s_rev.DumpRegister();

  return 0;
}
