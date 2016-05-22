#include "TDCControl.h"
#include "TDCSetup.h"
#include "TDCStatus.h"

int main(int argc, char* argv[])
{
  TDCSetup s;
  s.Dump(2);

  TDCControl c;
  c.SetEnablePattern(TDCControl::kOutputDisabled);
  c.DumpRegister(3);
  c.SetEnablePattern(TDCControl::kOutputEnabled);
  c.DisableAllChannels();
  c.DumpRegister(3);

  TDCStatus st;
  st.Dump(3);

  return 0;
}
