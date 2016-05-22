#include "TDCControl.h"
#include "TDCSetup.h"
#include "TDCStatus.h"

int main(int argc, char* argv[])
{
  TDCSetup s;
  s.Dump(2);

  TDCControl c;
  c.SetEnablePattern(TDCControl::OutputDisabled);
  c.DumpRegister(3);
  c.SetEnablePattern(TDCControl::OutputEnabled);
  c.DisableAllChannels();
  c.DumpRegister(3);

  TDCStatus st;
  st.Dump(3);

  return 0;
}
