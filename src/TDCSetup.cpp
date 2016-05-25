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

  std::ostream&
  operator<<(std::ostream& os, const TDCSetup::RegisterName& reg) {
    switch (reg) {
      case TDCSetup::rTestSelect:                            os << "test_select"; break;
      case TDCSetup::rEnableErrorMark:                       os << "enable_error_mark"; break;
      case TDCSetup::rEnableErrorBypass:                     os << "enable_error_bypass"; break;
      case TDCSetup::rEnableError:                           os << "enable_error"; break;
      case TDCSetup::rReadoutSingleCycleSpeed:               os << "readout_single_cycle_speed"; break;
      case TDCSetup::rSerialDelay:                           os << "serial_delay"; break;
      case TDCSetup::rStrobeSelect:                          os << "strobe_select"; break;
      case TDCSetup::rReadoutSpeedSelect:                    os << "readout_speed_select"; break;
      case TDCSetup::rTokenDelay:                            os << "token_delay"; break;
      case TDCSetup::rEnableLocalTrailer:                    os << "enable_local_trailer"; break;
      case TDCSetup::rEnableLocalHeader:                     os << "enable_local_header"; break;
      case TDCSetup::rEnableGlobalTrailer:                   os << "enable_global_trailer"; break;
      case TDCSetup::rEnableGlobalHeader:                    os << "enable_global_header"; break;
      case TDCSetup::rKeepToken:                             os << "keep_token"; break;
      case TDCSetup::rMaster:                                os << "master"; break;
      case TDCSetup::rEnableBytewise:                        os << "enable_bytewise"; break;
      case TDCSetup::rEnableSerial:                          os << "enable_serial"; break;
      case TDCSetup::rEnableJTAGReadout:                     os << "enable_jtag_readout"; break;
      case TDCSetup::rTDCId:                                 os << "tdc_id"; break;
      case TDCSetup::rSelectBypassInputs:                    os << "select_bypass_inputs"; break;
      case TDCSetup::rReadoutFIFOSize:                       os << "readout_fifo_size"; break;
      case TDCSetup::rRejectCountOffset:                     os << "reject_count_offset"; break;
      case TDCSetup::rSearchWindow:                          os << "search_window"; break;
      case TDCSetup::rMatchWindow:                           os << "match_window"; break;
      case TDCSetup::rLeadingResolution:                     os << "leading_resolution"; break;
      case TDCSetup::rMaxEventSize:                          os << "max_event_size"; break;
      case TDCSetup::rRejectFIFOFull:                        os << "reject_fifo_full"; break;
      case TDCSetup::rEnableReadoutOccupancy:                os << "enable_readout_occupancy"; break;
      case TDCSetup::rEnableReadoutSeparator:                os << "enable_readout_separator"; break;
      case TDCSetup::rEnableOverflowDetect:                  os << "enable_overflow_detect"; break;
      case TDCSetup::rEnableRelative:                        os << "enable_relative"; break;
      case TDCSetup::rEnableAutomaticReject:                 os << "enable_automatic_reject"; break;
      case TDCSetup::rEventCountOffset:                      os << "event_count_offset"; break;
      case TDCSetup::rTriggerCountOffset:                    os << "trigger_count_offset"; break;
      case TDCSetup::rEnableSetCountersOnBunchReset:         os << "enable_set_counters_on_bunch_reset"; break;
      case TDCSetup::rEnableMasterResetCode:                 os << "enable_master_reset_code"; break;
      case TDCSetup::rEnableMasterResetOnEventReset:         os << "enable_master_reset_on_event_reset"; break;
      case TDCSetup::rEnableResetChannelBufferWhenSeparator: os << "enable_reset_channel_buffer_when_separator"; break;
      case TDCSetup::rEnableSeparatorOnEventReset:           os << "enable_separator_on_event_reset"; break;
      case TDCSetup::rEnableSeparatorOnBunchReset:           os << "enable_separator_on_bunch_reset"; break;
      case TDCSetup::rEnableDirectEventReset:                os << "enable_direct_event_reset"; break;
      case TDCSetup::rEnableDirectBunchReset:                os << "enable_direct_bunch_reset"; break;
      case TDCSetup::rEnableDirectTrigger:                   os << "enable_direct_trigger"; break;
      case TDCSetup::rOffset:                                os << "channels_offset"; break;
      case TDCSetup::rCoarseCountOffset:                     os << "coarse_count_offset"; break;
      case TDCSetup::rDLLTapAdjust:                          os << "dll_tap_adjust"; break;
      case TDCSetup::rRCAdjust:                              os << "rc_adjust"; break;
      case TDCSetup::rLowPowerMode:                          os << "low_power_mode"; break;
      case TDCSetup::rWidthSelect:                           os << "width_select"; break;
      case TDCSetup::rVernierOffset:                         os << "vernier_offset"; break;
      case TDCSetup::rDLLControl:                            os << "dll_control"; break;
      case TDCSetup::rDeadTime:                              os << "dead_time"; break;
      case TDCSetup::rTestInvert:                            os << "test_invert"; break;
      case TDCSetup::rTestMode:                              os << "test_mode"; break;
      case TDCSetup::rTrailing:                              os << "trailing"; break;
      case TDCSetup::rLeading:                               os << "leading"; break;
      case TDCSetup::rModeRCCompression:                     os << "mode_rc_compression"; break;
      case TDCSetup::rModeRC:                                os << "mode_rc"; break;
      case TDCSetup::rDLLMode:                               os << "dll_mode"; break;
      case TDCSetup::rPLLControl:                            os << "pll_control"; break;
      case TDCSetup::rSerialClockDelay:                      os << "serial_clock_delay"; break;
      case TDCSetup::rIOClockDelay:                          os << "io_clock_delay"; break;
      case TDCSetup::rCoreClockDelay:                        os << "core_clock_delay"; break;
      case TDCSetup::rDLLClockDelay:                         os << "dll_clock_delay"; break;
      case TDCSetup::rSerialClockSource:                     os << "serial_clock_source"; break;
      case TDCSetup::rIOClockSource:                         os << "io_clock_source"; break;
      case TDCSetup::rCoreClockSource:                       os << "core_clock_source"; break;
      case TDCSetup::rDLLClockSource:                        os << "dll_clock_source"; break;
      case TDCSetup::rRollOver:                              os << "roll_over"; break;
      case TDCSetup::rEnableMatching:                        os << "enable_matching"; break;
      case TDCSetup::rEnablePair:                            os << "enable_pair"; break;
      case TDCSetup::rEnableTTLSerial:                       os << "enable_tll_serial"; break;
      case TDCSetup::rEnableTTLControl:                      os << "enable_ttl_control"; break;
      case TDCSetup::rEnableTTLReset:                        os << "enable_tll_reset"; break;
      case TDCSetup::rEnableTTLClock:                        os << "enable_tll_clock"; break;
      case TDCSetup::rEnableTTLHit:                          os << "enable_tll_hit"; break;
      case TDCSetup::rSetupParity:                           os << "setup_parity"; break;
      default: break;
    }
    return os;
  }
}
