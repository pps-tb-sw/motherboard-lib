#include <fstream>

#include "TDCControl.h"
#include "TDCSetup.h"
#include "TDCStatus.h"
#include "NINOThresholds.h"

#include "xml/XMLHandler.h"
#include <boost/regex.hpp>

using namespace std;

int main(int argc, char* argv[])
{
  string input_file = "test_input.xml";
  if (argc>1) input_file = argv[1];
  // readout part
  ostringstream os; ifstream xml_in(input_file.c_str()); os << xml_in.rdbuf(); xml_in.close();
  PPSTimingMB::XMLHandler h;

  //PPSTimingMB::NINOThresholds n;
  //cout << "Reading NINO thresholds..." << endl;
  PPSTimingMB::TDCSetup setup;
  cerr << "Reading setup word..." << endl;
  //h.ReadRegister(os.str(), &setup, PPSTimingMB::BoardAddress(0x07, 0x40, 0x18));
  h.ReadRegister(os.str(), &setup, PPSTimingMB::BoardAddress(0x0, 0x0, 0x0));
//  setup.SetDLLAdjustment(10, 5);
//  setup.SetDLLAdjustment(28, 4);
//  setup.SetDLLAdjustment(29, 4);
//  setup.SetDLLAdjustment(31, 5);
  setup.Dump();
  /*for (unsigned short i=0; i<4; i++) {
    cout << "group " << i << ": " << n.GetValue(i) << endl;
  }*/
  //cout << h.WriteRegister(setup, 0, 0, 0) << endl;

  return 0;
}
