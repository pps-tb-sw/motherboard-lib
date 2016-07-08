#include <fstream>

#include "TDCControl.h"
#include "TDCSetup.h"
#include "TDCStatus.h"
#include "NINOThresholds.h"

#include "XMLHandler.h"

using namespace std;

int main(int argc, char* argv[])
{
  PPSTimingMB::TDCControl c;
  PPSTimingMB::TDCSetup s;
  //s.Dump(3);
  PPSTimingMB::NINOThresholds n;
  n.SetValue(PPSTimingMB::BoardAddress(1, 3, 1), 1); // lol, just kidding
  n.SetValue(PPSTimingMB::BoardAddress(1, 3, 2), 2); // lol, just kidding
  n.SetValue(PPSTimingMB::BoardAddress(1, 3, 3), 3); // lol, just kidding
  n.SetValue(PPSTimingMB::BoardAddress(1, 3, 4), 4); // lol, just kidding
  n.Dump();
  PPSTimingMB::XMLHandler h; 
 
  // writeout part
  ofstream xml_out("test_output.xml");
  xml_out << h.WriteRegister(c, s, n, 1, 1, 2);
  xml_out.close();

  string input_file = "test_input.xml";
  if (argc>1) input_file = argv[1];
  // readout part
  ostringstream os; ifstream xml_in(input_file.c_str()); os << xml_in.rdbuf(); xml_in.close();

  cout << "Reading setup register..." << endl;
  h.ReadRegister(os.str(), &s, PPSTimingMB::BoardAddress(3, 1, 1));
  cout << "Reading control register..." << endl;
  h.ReadRegister(os.str(), &c, 1, 1, 1);
  cout << "Reading NINO thresholds..." << endl;

  cout << "--> before:" << endl;
  n.Dump();
  h.ReadRegister(os.str(), &n);
  cout << "--> after:" << endl;
  n.Dump();

  const PPSTimingMB::BoardAddress address_to_retrieve(1, 3, 3);
  cout << "NINO threshold for address " << address_to_retrieve.mfec << ":" << address_to_retrieve.ccu << ":" << address_to_retrieve.i2c << ": " << n.GetValue(address_to_retrieve) << endl;

  s.Dump();

  return 0;
}
