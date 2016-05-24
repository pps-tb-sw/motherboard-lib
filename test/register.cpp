#include "TDCControl.h"
#include "TDCSetup.h"
#include "TDCStatus.h"

using namespace std;

int main(int argc, char* argv[])
{
  PPSTimingMB::TDCSetup s;
  s.Dump(2);

  PPSTimingMB::TDCControl c;
  c.SetEnablePattern(PPSTimingMB::TDCControl::OutputDisabled);
  c.DumpRegister(3);
  c.SetEnablePattern(PPSTimingMB::TDCControl::OutputEnabled);
  c.DisableAllChannels();
  c.DumpRegister(3);

  PPSTimingMB::TDCStatus st;
  st.Dump(3);
  PPSTimingMB::TDCStatus::ErrorType err = st.Error();
  cout << "Global error? " << err.GlobalError() << endl;

  for (unsigned int i=0; i<s.GetNumRegisters(); i++) {
    PPSTimingMB::TDCSetup::RegisterName reg = static_cast<PPSTimingMB::TDCSetup::RegisterName>(i);
    std::cout << "register " << reg << ": " << s.GetValue(reg) << std::endl;
  }

  return 0;
}
