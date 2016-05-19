#include "TDCControl.h"
#include "TDCSetup.h"

int main(int argc, char* argv[])
{
  TDCSetup s;
  s.Dump(2);
  std::vector<uint8_t> s_vec = s.GetBytesVector();
  
  TDCSetup s_rev(s_vec, true);
  s_rev.Dump(2);

  return 0;
}
