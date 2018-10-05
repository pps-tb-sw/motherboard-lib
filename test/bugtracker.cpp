#include <fstream>

#include "TDCSetup.h"
#include "XMLHandler.h"

using namespace std;

int main(int argc, char* argv[])
{
  PPSTimingMB::TDCSetup s;
  PPSTimingMB::XMLHandler h; 
 
  string input_file = "test_input.xml";
  if (argc>1) input_file = argv[1];
  // readout part
  ostringstream os; ifstream xml_in(input_file.c_str()); os << xml_in.rdbuf(); xml_in.close();

  cout << "Reading setup register..." << endl;
  bool status = h.ReadRegister(os.str(), &s, PPSTimingMB::BoardAddress(0x3, 0x1, 0x17));
  if (!status) {
    cerr << "Failed to find the proper register... aborting..." << endl;
    return -1;
  }

  cout << "---> event count offset: " << s.GetEventCountOffset() << endl;
  cout << "---> DLL clock source: " << s.GetDLLClockSource() << endl;
  s.Dump(3);

  return 0;
}
