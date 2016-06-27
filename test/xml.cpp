#include <fstream>

#include "TDCControl.h"
#include "TDCSetup.h"
#include "TDCStatus.h"

#include "XMLHandler.h"

using namespace std;

int main(int argc, char* argv[])
{
  PPSTimingMB::TDCControl c;
  PPSTimingMB::TDCSetup s;
  //s.Dump(3);
  PPSTimingMB::XMLHandler h;

  // writeout part
  ofstream xml_out("test_output.xml");
  xml_out << h.WriteRegister(c, s, 1, 1, 2);
  xml_out.close();

  string input_file = "test_input.xml";
  if (argc>1) input_file = argv[1];
  // readout part
  ostringstream os; ifstream xml_in(input_file.c_str()); os << xml_in.rdbuf(); xml_in.close();

  cout << "Reading setup register..." << endl;
  h.ReadRegister(os.str(), &s, 3, 1, 1);
  cout << "Reading control register..." << endl;
  h.ReadRegister(os.str(), &c, 1, 1, 1);

  s.Dump();

  return 0;
}
