#include "TDCControl.h"

void
TDCControl::Dump(int verb, std::ostream& os) const
{
  os << "===================="
     << " TDC Control register dump "
     << "===================" << std::endl;
  if (verb>1) DumpRegister(verb, os);
  os << " EnablePattern: " << GetEnablePattern() << std::endl
     << " Enabled channels: " << std::endl/*;
  uint32_t channels = GetEnabledChannels();
  os << "  0-15: " << (channels&0xffff) << std::endl
     << " 16-31: " << (channels>>16) << std::endl*/
     << "  --> In: ";
  for (unsigned int i=0; i<TDC_NUM_CHANNELS; i++) { if (IsChannelEnabled(i)) os << " " << i; }
  os << std::endl << "  --> Out:";
  for (unsigned int i=0; i<TDC_NUM_CHANNELS; i++) { if (!IsChannelEnabled(i)) os << " " << i; }
  os << std::endl
     << " Global reset: " << GetGlobalReset() << std::endl
     << " DLL reset: " << GetDLLReset() << std::endl
     << " PLL reset: " << GetPLLReset() << std::endl;
}

void
TDCControl::SetConstantValues()
{
  EnableAllChannels();
}
