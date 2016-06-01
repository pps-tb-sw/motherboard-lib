#include <fstream>

#include "TDCControl.h"
#include "TDCSetup.h"
#include "TDCStatus.h"

#include "XMLHandler.h"

using namespace std;

int main(int argc, char* argv[])
{
  //TDCControl r;
  PPSTimingMB::TDCSetup r;
  r.Dump(3);
  PPSTimingMB::XMLHandler h;

  // writeout part
  ofstream xml_out("test_output.xml");
  xml_out << h.WriteRegister(r);
  xml_out.close();

  // readout part
  std::ostringstream os; ifstream xml_in("test_input.xml"); os << xml_in.rdbuf(); xml_in.close();
  h.ReadRegister(os.str(), &r);

  r.Dump();

  return 0;
}
