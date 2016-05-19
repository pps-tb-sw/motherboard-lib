#include "TDCStatus.h"

void
TDCStatus::Dump(int verb, std::ostream& os) const
{
  os << "===================="
     << " TDC Status register dump "
     << "====================" << std::endl;
  if (verb>1) DumpRegister(verb, os);
  os << " Error? " << Error() << std::endl
     << " Have token? " << HaveToken() << std::endl
     << " FIFO full? " << FIFOFull() << std::endl
     << " FIFO empty? " << FIFOEmpty() << std::endl
     << " L1 occupancy: " << static_cast<unsigned int>(L1Occupancy()) << std::endl
     << " TriggerFIFO occupancy: " << static_cast<unsigned int>(TriggerFIFOOccupancy()) << std::endl
     << " TriggerFIFO full? " << TriggerFIFOFull() << std::endl
     << " TriggerFIFO empty? " << TriggerFIFOEmpty() << std::endl
     << " DLL lock? " << DLLLock() << std::endl;
}
