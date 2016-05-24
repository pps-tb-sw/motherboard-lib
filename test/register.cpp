#include "TDCControl.h"
#include "TDCSetup.h"
#include "TDCStatus.h"

using namespace std;

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
  TDCStatus::ErrorType err = st.Error();
  cout << "Global error? " << err.GlobalError() << endl;

  for (unsigned int i=0; i<c.GetNumRegisters(); i++) {
    TDCControl::RegisterName reg = static_cast<TDCControl::RegisterName>(i);
    std::cout << "register " << reg << ": " << c.GetValue(reg) << std::endl;
  }

  return 0;
}
