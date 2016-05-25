#include "TDCSetup.h"

namespace PPSTimingMB
{
  void
  TDCSetup::SetConstantValues()
  {
    SetTest(false);
    SetEnableErrorMark(true);
    SetEnableErrorBypass(false);
    SetEnableError(0x7ff); // 11 bits of '1'

    SetStrobeSelect(SS_NoStrobe);

    SetEnableGlobalTrailer(false); // FIXME not yet discussed...
    SetEnableGlobalHeader(false); // FIXME not yet discussed...

    SetReadoutSingleCycleSpeed(RSC_40Mbits_s); // FIXME don't care...
    SetSerialDelay(0x0); // FIXME maybe affected by the realistic tests
    SetReadoutSpeedSelect(RO_Fixed);
    SetTokenDelay(0x0); // FIXME maybe affected by the realistic tests

    SetEnableLocalTrailer(true); // FIXME not yet discussed...
    SetEnableLocalHeader(true); // FIXME not yet discussed...
    SetMaster(false);
    SetEnableBytewise(false);

    SetBypassInputs(false); // bit 44
    SetReadoutFIFOSize(256); // maximum
    SetMaxEventSize(-1); // no limit
    SetRejectFIFOFull(true);
    SetEnableReadoutOccupancy(false);
    SetEnableReadoutSeparator(false);
    SetEnableOverflowDetect(true);

    SetKeepToken(true);

    SetEnableRelative(true);
    SetEnableAutomaticReject(false);

    /*SetEventCountOffset(0); // FIXME needs confirmation
    SetTriggerCountOffset(0);*/

    SetEnableSetCountersOnBunchReset(false); // FIXME not yet discussed...
    SetEnableMasterResetCode(false);
    SetEnableMasterResetOnEventReset(false);
    SetEnableResetChannelBufferWhenSeparator(false); // FIXME not yet discussed...
    SetEnableSeparatorOnEventReset(false);
    SetEnableSeparatorOnBunchReset(false);
    SetEnableDirectEventReset(true);
    SetEnableDirectBunchReset(true);
    SetEnableDirectTrigger(true);

    SetLowPowerMode(true);
    SetDLLControl(0x1);

    //SetDeadTime(DT_5ns); // FIXME do we force the dead time value?
    //SetTestInvert(false);
    //SetTestMode(false);

    SetModeRCCompression(true);
    SetModeRC(true);
    SetDLLMode(DLL_320MHz);
    SetPLLControl(0x4, false, false, false);

    SetSerialClockDelay(false, 0x0);
    SetIOClockDelay(false, 0x0);
    SetCoreClockDelay(false, 0x0);
    SetDLLClockDelay(false, 0x0);
    SetSerialClockSource(Serial_pll_clock_80);

    SetIOClockSource(IO_clock_40);
    SetCoreClockSource(Core_clock_40);
    SetDLLClockSource(DLL_clock_40);

    SetRollOver(0xfff); // 4095
    SetEnableTTLSerial(true);
    SetEnableTTLControl(true);
    SetEnableTTLReset(true);
    SetEnableTTLClock(false);
    SetEnableTTLHit(false);

    SetEdgesPairing(false);
    SetTriggerMatchingMode(true);
    SetLeadingMode(true);
    SetTrailingMode(true);

    SetRCAdjustment(0, 0x7);
    SetRCAdjustment(1, 0x7);
    SetRCAdjustment(2, 0x4);
    SetRCAdjustment(3, 0x2);

    SetCoarseCountOffset(0);
    SetTriggerCountOffset(0);
    SetMatchWindow(198);
    SetSearchWindow(198);
    SetRejectCountOffset(0);
    SetTDCId(0);

    SetEnableJTAGReadout(false);

    SetSetupParity(true);
  }

  void
  TDCSetup::Dump(int verb, std::ostream& os) const
  {
    os << "====================="
       << " TDC Setup register dump "
       << "====================" << std::endl;
    if (verb>1) DumpRegister(verb, os);
    os << " Enabled errors:             ";
    for (unsigned int i=0; i<11; i++) {
      if (static_cast<bool>((GetEnableError()>>i)&0x1)) os << i << " ";
    }
    os << std::endl;
    os << " Edge resolution:            " << GetEdgeResolution() << std::endl
       << " Maximal event size:         " << GetMaxEventSize() << std::endl
       << " Reject events if FIFO full? " << GetRejectFIFOFull() << std::endl
       << " Channels offset/DLL adjustments:" << std::endl
       << "   +---------------------------------------------------------+" << std::endl;
    for (unsigned int i=0; i<TDC_NUM_CHANNELS/2; i++ ) {
      os << "   |  Ch.  " << std::setw(2) << i
         << ":   0x" << std::setfill('0')
         << std::setw(3) << std::hex << static_cast<int>(GetChannelOffset(i))
         << " / 0x"
         << std::setw(3) << static_cast<int>(GetDLLAdjustment(i)) << std::dec << std::setfill(' ')
         << "   |  Ch.  " << std::setw(2) << i+TDC_NUM_CHANNELS/2
         << ":   0x" << std::setfill('0')
         << std::setw(3) << std::hex << static_cast<int>(GetChannelOffset(i+TDC_NUM_CHANNELS/2))
         << " / 0x"
         << std::setw(3) << static_cast<int>(GetDLLAdjustment(i+TDC_NUM_CHANNELS/2)) << std::dec << std::setfill(' ')
         << " |" << std::endl;
    }
    os << "   +---------------------------------------------------------+" << std::endl
       << " Width resolution:           " << GetWidthResolution() << std::endl
       << " Dead time:                  " << GetDeadTime() << std::endl
       << " Leading/trailing mode:      " << GetLeadingMode() << " / " << GetTrailingMode() << std::endl
       << " Trigger matching mode:      " << GetTriggerMatchingMode() << std::endl
       << " Edges pairing:              " << GetEdgesPairing() << std::endl;
    os << "================================="
       << "=================================" << std::endl;
  }

  std::string
  TDCSetup::GetXML() const
  {
    std::string out;
    return out;
  }

  uint32_t
  TDCSetup::GetValue(const RegisterName& reg)
  {
    switch (reg) {
      case rTestSelect:                            return IsTest();
      case rEnableErrorMark:                       return GetEnableErrorMark();
      case rEnableErrorBypass:                     return GetEnableErrorBypass();
      case rEnableError:                           return GetEnableError();
      case rReadoutSingleCycleSpeed:               return GetReadoutSingleCycleSpeed();
      case rSerialDelay:                           return GetSerialDelay();
      case rStrobeSelect:                          return GetStrobeSelect();
      case rReadoutSpeedSelect:                    return GetReadoutSpeedSelect();
      case rTokenDelay:                            return GetTokenDelay();
      case rEnableLocalTrailer:                    return GetEnableLocalTrailer();
      case rEnableLocalHeader:                     return GetEnableLocalHeader();
      case rEnableGlobalTrailer:                   return GetEnableGlobalTrailer();
      case rEnableGlobalHeader:                    return GetEnableGlobalHeader();
      case rKeepToken:                             return GetKeepToken();
      case rMaster:                                return GetMaster();
      case rEnableBytewise:                        return GetEnableBytewise();
      case rEnableSerial:                          return GetEnableSerial();
      case rEnableJTAGReadout:                     return GetEnableJTAGReadout();
      case rTDCId:                                 return GetTDCId();
      case rSelectBypassInputs:                    return GetBypassInputs();
      case rReadoutFIFOSize:                       return GetReadoutFIFOSize();
      case rRejectCountOffset:                     return GetRejectCountOffset();
      case rSearchWindow:                          return GetSearchWindow();
      case rMatchWindow:                           return GetMatchWindow();
      case rLeadingResolution:                     return GetEdgeResolution();
      case rMaxEventSize:                          return GetMaxEventSize();
      case rRejectFIFOFull:                        return GetRejectFIFOFull();
      case rEnableReadoutOccupancy:                return GetEnableReadoutOccupancy();
      case rEnableReadoutSeparator:                return GetEnableReadoutSeparator();
      case rEnableOverflowDetect:                  return GetEnableOverflowDetect();
      case rEnableRelative:                        return GetEnableRelative();
      case rEnableAutomaticReject:                 return GetEnableAutomaticReject();
      case rEventCountOffset:                      return GetEventCountOffset();
      case rTriggerCountOffset:                    return GetTriggerCountOffset();
      case rEnableSetCountersOnBunchReset:         return GetEnableSetCountersOnBunchReset();
      case rEnableMasterResetCode:                 return GetEnableMasterResetCode();
      case rEnableMasterResetOnEventReset:         return GetEnableMasterResetOnEventReset();
      case rEnableResetChannelBufferWhenSeparator: return GetEnableResetChannelBufferWhenSeparator();
      case rEnableSeparatorOnEventReset:           return GetEnableSeparatorOnEventReset();
      case rEnableSeparatorOnBunchReset:           return GetEnableSeparatorOnBunchReset();
      case rEnableDirectEventReset:                return GetEnableDirectEventReset();
      case rEnableDirectBunchReset:                return GetEnableDirectBunchReset();
      case rEnableDirectTrigger:                   return GetEnableDirectTrigger();
      case rOffset:                                return 0; //FIXME!
      case rCoarseCountOffset:                     return GetCoarseCountOffset();
      case rDLLTapAdjust:                          return GetDLLAdjustmentWord();
      case rRCAdjust:                              return GetRCAdjustmentWord();
      case rLowPowerMode:                          return GetLowPowerMode();
      case rWidthSelect:                           return GetWidthResolution();
      case rVernierOffset:                         return GetVernierOffset();
      case rDLLControl:                            return GetDLLControl();
      case rDeadTime:                              return GetDeadTime();
      case rTestInvert:                            return GetTestInvert();
      case rTestMode:                              return GetTestMode();
      case rTrailing:                              return GetTrailingMode();
      case rLeading:                               return GetLeadingMode();
      case rModeRCCompression:                     return GetModeRCCompression();
      case rModeRC:                                return GetModeRC();
      case rDLLMode:                               return GetDLLMode();
      case rPLLControl:                            return GetPLLControlWord();
      case rSerialClockDelay:                      return GetSerialClockDelay();
      case rIOClockDelay:                          return GetIOClockDelay();
      case rCoreClockDelay:                        return GetCoreClockDelay();
      case rDLLClockDelay:                         return GetDLLClockDelay();
      case rSerialClockSource:                     return GetSerialClockSource();
      case rIOClockSource:                         return GetIOClockSource();
      case rCoreClockSource:                       return GetCoreClockSource();
      case rDLLClockSource:                        return GetDLLClockSource();
      case rRollOver:                              return GetRollOver();
      case rEnableMatching:                        return GetTriggerMatchingMode();
      case rEnablePair:                            return GetEdgesPairing();
      case rEnableTTLSerial:                       return GetEnableTTLSerial();
      case rEnableTTLControl:                      return GetEnableTTLControl();
      case rEnableTTLReset:                        return GetEnableTTLReset();
      case rEnableTTLClock:                        return GetEnableTTLClock();
      case rEnableTTLHit:                          return GetEnableTTLHit();
      case rSetupParity:                           return GetSetupParity();
      default: return 0;
    }
  }
}
