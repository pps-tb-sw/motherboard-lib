#include "TDCControl.h"

void
TDCControl::Dump(int verb, std::ostream& os) const
{
  os << "===================="
     << " TDC Control register dump "
     << "===================" << std::endl;
  if (verb>1) DumpRegister(verb, os);
  os << " EnablePattern: " << GetEnablePattern() << std::endl
     << " Global reset: " << GetGlobalReset() << std::endl
     << " DLL reset: " << GetDLLReset() << std::endl
     << " PLL reset: " << GetPLLReset() << std::endl;
}

void
TDCControl::SetConstantValues()
{
  EnableAllChannels();
}
