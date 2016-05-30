#include "TDCControl.h"
#include "TDCSetup.h"
#include "TDCStatus.h"
#include "TDCInternalCoreTest.h"

using namespace std;

int main(int argc, char* argv[])
{
  PPSTimingMB::TDCSetup s;
  s.Dump(2);

  PPSTimingMB::TDCControl c;
  /*c.SetEnablePattern(PPSTimingMB::TDCControl::OutputDisabled);
  c.DumpRegister(3);
  c.SetEnablePattern(PPSTimingMB::TDCControl::OutputEnabled);*/
  cout << "Enabled channels: " << c.GetEnabledChannels() << endl;
  c.DisableAllChannels();
  cout << "Enabled channels: " << c.GetEnabledChannels() << endl;
  c.DumpRegister(3);

  PPSTimingMB::TDCStatus st;
  st.Dump(3);
  PPSTimingMB::TDCStatus::ErrorType err = st.Error();
  cout << "Global error? " << err.GlobalError() << endl;

  for (unsigned int i=0; i<PPSTimingMB::GetNumTDCSetupRegisters(); i++) {
    PPSTimingMB::TDCSetupRegister reg = static_cast<PPSTimingMB::TDCSetupRegister>(i);
    //cout << "register " << reg << ": " << s.GetValue(reg) << endl;
  }

  PPSTimingMB::TDCSetupRegister reg[] = { PPSTimingMB::rPLLControl, PPSTimingMB::rEnableMatching };
  cout << reg[0] << " -- " << reg[1] << endl;

  PPSTimingMB::TDCInternalCoreTest ict;
  ict.Dump();

  return 0;
}
