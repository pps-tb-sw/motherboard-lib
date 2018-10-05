#include "TDCControl.h"
#include "TDCSetup.h"
#include "TDCStatus.h"
#include "TDCInternalCoreTest.h"

using namespace std;

int main(int argc, char* argv[])
{
  {
    vector<unsigned char> word;
    word.push_back(0xe0);
    word.push_back(0xff);
    word.push_back(0xff);
    word.push_back(0xff);
    word.push_back(0x1f);
    PPSTimingMB::TDCControl control(word);
    control.ComputeParity();
    control.Dump(3);
  }

  /*{
    vector<unsigned char> words;
    //words.push_back(0x55); // 01010101
    words.push_back(0x57); // 01010111
    PPSTimingMB::TDCRegister r(8, words);
    r.DumpRegister(3);
    cout << "parity=" << r.ComputeParityBit() << endl;

    return 0;
  }*/

  {
    PPSTimingMB::TDCSetup s;
    s.Dump(3);

    PPSTimingMB::TDCControl c;
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
  }

  {
    PPSTimingMB::TDCSetupRegister reg[] = { PPSTimingMB::rPLLControl, PPSTimingMB::rEnableMatching };
    cout << reg[0] << " -- " << reg[1] << endl;

    PPSTimingMB::TDCInternalCoreTest ict;
    ict.Dump();
  }

  return 0;
}
