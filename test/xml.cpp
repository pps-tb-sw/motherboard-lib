#include <fstream>

#include "TDCControl.h"
#include "TDCSetup.h"
#include "TDCStatus.h"
#include "NINOThresholds.h"

#include "XMLHandler.h"

using namespace std;

int main(int argc, char* argv[])
{
  string input_file = "test_input.xml";
  if (argc>1) input_file = argv[1];
  // readout part
  ostringstream os; ifstream xml_in(input_file.c_str()); os << xml_in.rdbuf(); xml_in.close();
  PPSTimingMB::XMLHandler h;

  PPSTimingMB::NINOThresholds n;
  cout << "Reading NINO thresholds..." << endl;
  h.ReadRegister(os.str(), &n, PPSTimingMB::BoardAddress(0x08, 0x40, 0x12));
  n.Dump();
  for (unsigned short i=0; i<4; i++) {
    std::cout << "group " << i << ": " << n.GetValue(i) << std::endl;
  }

  return 0;
}
