#include "TDCStatus.h"

namespace PPSTimingMB
{
  void
  TDCStatus::SetConstantValues()
  {
  }

  void
  TDCStatus::Dump(int verb, std::ostream& os) const
  {
    os << "===================="
       << " TDC Status register dump "
       << "====================" << std::endl;
    if (verb>1) DumpRegister(verb, os);
    os << " Error flags:               " << std::endl << Error() << std::endl
       << " Has token?                 " << HasToken() << std::endl
       << " FIFO full?                 " << FIFOFull() << std::endl
       << " FIFO empty?                " << FIFOEmpty() << std::endl
       << " L1 occupancy:          " << std::right << static_cast<unsigned int>(L1Occupancy()) << std::left << std::endl
       << " TriggerFIFO occupancy: " << std::right << static_cast<unsigned int>(TriggerFIFOOccupancy()) << std::left << std::endl
       << " TriggerFIFO full?          " << TriggerFIFOFull() << std::endl
       << " TriggerFIFO empty?         " << TriggerFIFOEmpty() << std::endl
       << " DLL lock?                  " << DLLLock() << std::endl
       << "===================================================================" << std::endl;
  }

  std::ostream&
  operator<<(std::ostream& os, const TDCStatus::ErrorType& err)
  {
    os << "  +---------------------------+" << std::endl
       << "  | Vernier:                " << err.Vernier << " |" << std::endl
       << "  | Coarse:                 " << err.Coarse << " |" << std::endl
       << "  | Channel selection:      " << err.ChannelSelect << " |" << std::endl
       << "  | Trigger matching state: " << err.TriggerMatchingState << " |" << std::endl
       << "  | Readout state:          " <<  err.ReadoutState << " |" << std::endl
       << "  | JTAG instruction:       " <<  err.JTAGInstruction << " |" << std::endl
       << "  +------- Parity Bits -------+" << std::endl
       << "  | * L1 buffer:            " << err.L1BufferParity << " |" << std::endl
       << "  | * Trigger FIFO:         " << err.TriggerFIFOParity << " |" << std::endl
       << "  | * Readout FIFO:         " << err.ReadoutFIFOParity << " |" << std::endl
       << "  | * Setup register:       " << err.SetupParity << " |" << std::endl
       << "  | * Control register:     " << err.ControlParity << " |" << std::endl
       << "  +---------------------------+";
    return os;
  }
}
