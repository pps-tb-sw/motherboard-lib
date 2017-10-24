#include "XMLHandler.h"

XERCES_CPP_NAMESPACE_USE

namespace PPSTimingMB
{
  /*DOMDocument* XMLHandler::fDocument = NULL;
  DOMImplementation* XMLHandler::fImpl = NULL;*/

  XMLHandler::XMLHandler() :
    fROOT(0), fImpl(0), fDocument(0)
  {
    Initialize();
  }

  XMLHandler::~XMLHandler()
  {
    Terminate();
  }

  void
  XMLHandler::Initialize()
  {
    XMLCh str[100];

    try { XMLPlatformUtils::Initialize(); } catch (const XMLException& toCatch) {
      char* message = XMLString::transcode(toCatch.getMessage());
      std::cerr << "Error during initialization! :\n"
                << message << "\n";
      XMLString::release(&message);
      return;
    }

    XMLString::transcode("core", str, 99);
    fImpl = DOMImplementationRegistry::getDOMImplementation(str);
  }

  void
  XMLHandler::Terminate()
  {
    try { if (fDocument) fDocument->release(); } catch (const DOMException& e) {
      char* message = XMLString::transcode(e.getMessage());
      std::cerr << "Error during termination! :\n"
                << message << "\n";
      XMLString::release(&message);
      return;
    }
    try { XMLPlatformUtils::Terminate(); } catch (const XMLException& e) {
      char* message = XMLString::transcode(e.getMessage());
      std::cerr << "Error during termination! :\n"
                << message << "\n";
      XMLString::release(&message);
      return;
    }
  }

  std::string
  XMLHandler::WriteRegister(const TDCControl& r, const BoardAddress& addr)
  {
    XMLCh str[100];

    XMLString::transcode("TDCRegister", str, 99);
    fDocument = fImpl->createDocument(0, str, 0);
    
    PopulateControlRegister(r, addr);

    return XMLString();
  }

  std::string
  XMLHandler::WriteRegister(const TDCSetup& r, const BoardAddress& addr)
  {
    XMLCh str[100];

    XMLString::transcode("TDCRegister", str, 99);
    fDocument = fImpl->createDocument(0, str, 0);

    PopulateSetupRegister(r, addr);

    return XMLString();
  }

  std::string
  XMLHandler::WriteRegister(const NINOThresholds& n, const BoardAddress& addr)
  {
    XMLCh str[100];

    XMLString::transcode("TDCRegister", str, 99);
    fDocument = fImpl->createDocument(0, str, 0);

    PopulateNINOThresholds(n, addr);

    return XMLString();
  }

  std::string
  XMLHandler::WriteRegister(const TDCControl& c, const TDCSetup& s, const BoardAddress& addr)
  {
    XMLCh str[100];

    XMLString::transcode("TDCRegister", str, 99);
    fDocument = fImpl->createDocument(0, str, 0);

    PopulateControlRegister(c, addr);
    PopulateSetupRegister(s, addr);
    
    return XMLString();
  }

  std::string
  XMLHandler::WriteRegister(const TDCControl& c, const TDCSetup& s, const NINOThresholds& n, const BoardAddress& addr)
  {
    XMLCh str[100];

    XMLString::transcode("TDCRegister", str, 99);
    fDocument = fImpl->createDocument(0, str, 0);

    PopulateControlRegister(c, addr);
    PopulateSetupRegister(s, addr);
    PopulateNINOThresholds(n, addr);
    
    return XMLString();
  }

  void
  XMLHandler::PopulateControlRegister(const TDCControl& r, const BoardAddress& addr)
  {
    XMLCh str[100];

    XMLString::transcode("TDCControl", str, 99);
    DOMElement* elem = fDocument->createElement(str);
    fROOT = fDocument->getDocumentElement();

    SetAddressAttributes(elem, addr);

    AddProperty(elem, "pll_reset",             r.GetPLLReset());
    AddProperty(elem, "dll_reset",             r.GetDLLReset());
    /*AddProperty(elem, "enable_channel", r.GetEnabledChannels());*/
    AddProperty(elem, "enable_channel_group0", r.GetEnabledChannelsGroup0());
    AddProperty(elem, "enable_channel_group1", r.GetEnabledChannelsGroup1());
    AddProperty(elem, "global_reset",          r.GetGlobalReset());
    AddProperty(elem, "enable_pattern",        static_cast<unsigned int>(r.GetEnablePattern()));

    fROOT->appendChild(elem);
  }

  void
  XMLHandler::PopulateNINOThresholds(const NINOThresholds& r, const BoardAddress& addr)
  {
    XMLCh str[100];

    XMLString::transcode("NINOThresholds", str, 99);
    DOMElement* elem = fDocument->createElement(str);
    fROOT = fDocument->getDocumentElement();

    SetAddressAttributes(elem, addr);

    /* Bug
    for (NINOThresholds::Register::const_iterator it=r.GetValues().begin(); it!=r.GetValues().end(); it++) {
      std::ostringstream os; os << "group" << std::dec << it->first;
      AddProperty(elem, os.str().c_str(), it->second);
    }
    */
    
    AddProperty(elem, "group0", r.GetValue(0));
    AddProperty(elem, "group1", r.GetValue(1));
    AddProperty(elem, "group2", r.GetValue(2));
    AddProperty(elem, "group3", r.GetValue(3));
    AddProperty(elem, "group4", r.GetValue(4));
    AddProperty(elem, "group5", r.GetValue(5));
    AddProperty(elem, "group6", r.GetValue(6));
    AddProperty(elem, "group7", r.GetValue(7));
    
    fROOT->appendChild(elem);
  }

  void
  XMLHandler::PopulateSetupRegister(const TDCSetup& r, const BoardAddress& addr)
  {
    XMLCh str[100];

    XMLString::transcode("TDCSetup", str, 99);
    DOMElement* elem = fDocument->createElement(str);
    fROOT = fDocument->getDocumentElement();

    SetAddressAttributes(elem, addr);

    AddProperty(elem, "enable_ttl_hit",                      r.GetEnableTTLHit());
    AddProperty(elem, "enable_ttl_clock",                    r.GetEnableTTLClock());
    AddProperty(elem, "enable_ttl_reset",                    r.GetEnableTTLReset());
    AddProperty(elem, "enable_ttl_control",                  r.GetEnableTTLControl());
    AddProperty(elem, "enable_ttl_serial",                   r.GetEnableTTLSerial());
    AddProperty(elem, "enable_pair",                         r.GetEdgesPairing());
    AddProperty(elem, "enable_matching",                     r.GetTriggerMatchingMode());
    AddProperty(elem, "roll_over",                           r.GetRollOver());
    AddProperty(elem, "dll_clock_source",                    static_cast<unsigned int>(r.GetDLLClockSource()));
    AddProperty(elem, "core_clock_source",                   static_cast<unsigned int>(r.GetCoreClockSource()));
    AddProperty(elem, "io_clock_source",                     static_cast<unsigned int>(r.GetIOClockSource()));
    AddProperty(elem, "serial_clock_source",                 static_cast<unsigned int>(r.GetSerialClockSource()));
    AddProperty(elem, "dll_clock_delay",                     static_cast<unsigned int>(r.GetDLLClockDelay()));
    AddProperty(elem, "core_clock_delay",                    static_cast<unsigned int>(r.GetCoreClockDelay()));
    AddProperty(elem, "io_clock_delay",                      static_cast<unsigned int>(r.GetIOClockDelay()));
    AddProperty(elem, "serial_clock_delay",                  static_cast<unsigned int>(r.GetSerialClockDelay()));
    AddProperty(elem, "pll_control",                         r.GetPLLControlWord());
    AddProperty(elem, "dll_mode",                            static_cast<unsigned int>(r.GetDLLMode()));
    AddProperty(elem, "mode_rc",                             r.GetModeRC());
    AddProperty(elem, "mode_rc_compression",                 r.GetModeRCCompression());
    AddProperty(elem, "enable_leading",                      r.GetLeadingMode());
    AddProperty(elem, "enable_trailing",                     r.GetTrailingMode());
    AddProperty(elem, "test_mode",                           r.GetTestMode());
    AddProperty(elem, "test_invert",                         r.GetTestInvert());
    AddProperty(elem, "dead_time",                           r.GetDeadTime());
    AddProperty(elem, "dll_control",                         r.GetDLLControl());
    AddProperty(elem, "vernier_offset",                      r.GetVernierOffset());
    AddProperty(elem, "width_resolution",                    static_cast<unsigned int>(r.GetWidthResolution()));
    AddProperty(elem, "low_power_mode",                      r.GetLowPowerMode());
    AddProperty(elem, "rc_adjust",                           r.GetRCAdjustmentWord());
    //AddProperty(elem, "dll_tap_adjust",                      r.GetDLLAdjustmentWord());
    AddRangeProperty(elem, "dll_tap_adjust",                 r.GetDLLAdjustmentWord(), 3);
    AddProperty(elem, "coarse_count_offset",                 r.GetCoarseCountOffset());
    for (unsigned short i=0; i<32; ++i) {
      std::ostringstream os; os << "offset" << i;
      AddProperty(elem, os.str().c_str(),                    r.GetChannelOffset(i));
    }
    AddProperty(elem, "direct_trigger",                      r.GetEnableDirectTrigger());
    AddProperty(elem, "direct_bunch_reset",                  r.GetEnableDirectBunchReset());
    AddProperty(elem, "direct_event_reset",                  r.GetEnableDirectEventReset());
    AddProperty(elem, "separator_on_bunch_reset",            r.GetEnableSeparatorOnBunchReset());
    AddProperty(elem, "separator_on_event_reset",            r.GetEnableSeparatorOnEventReset());
    AddProperty(elem, "reset_channel_buffer_when_separator", r.GetEnableResetChannelBufferWhenSeparator());
    AddProperty(elem, "master_reset_on_event_reset",         r.GetEnableMasterResetOnEventReset());
    AddProperty(elem, "master_reset_code",                   r.GetEnableMasterResetCode());
    AddProperty(elem, "set_counters_on_bunch_reset",         r.GetEnableSetCountersOnBunchReset());
    AddProperty(elem, "trigger_count_offset",                r.GetTriggerCountOffset());
    AddProperty(elem, "event_count_offset",                  r.GetEventCountOffset());
    AddProperty(elem, "automatic_reject",                    r.GetEnableAutomaticReject());
    AddProperty(elem, "enable_relative",                     r.GetEnableRelative());
    AddProperty(elem, "overflow_detection",                  r.GetEnableOverflowDetect());
    AddProperty(elem, "readout_separator",                   r.GetEnableReadoutSeparator());
    AddProperty(elem, "readout_occupancy",                   r.GetEnableReadoutOccupancy());
    AddProperty(elem, "reject_fifo_full",                    r.GetRejectFIFOFull());
    AddProperty(elem, "max_event_size",                      r.GetMaxEventSize());
    AddProperty(elem, "edge_resolution",                     static_cast<unsigned int>(r.GetEdgeResolution()));
    AddProperty(elem, "match_window",                        r.GetMatchWindow());
    AddProperty(elem, "search_window"               ,        r.GetSearchWindow());
    AddProperty(elem, "reject_count_offset",                 r.GetRejectCountOffset());
    AddProperty(elem, "readout_fifo_size",                   r.GetReadoutFIFOSize());
    AddProperty(elem, "bypass_inputs",                       r.GetBypassInputs());
    AddProperty(elem, "tdc_id",                              r.GetTDCId());
    AddProperty(elem, "jtag_readout",                        r.GetEnableJTAGReadout());
    AddProperty(elem, "serial",                              r.GetEnableSerial());
    AddProperty(elem, "bytewise",                            r.GetEnableBytewise());
    AddProperty(elem, "master",                              r.GetMaster());
    AddProperty(elem, "keep_token",                          r.GetKeepToken());
    AddProperty(elem, "global_header",                       r.GetEnableGlobalHeader());
    AddProperty(elem, "global_trailer",                      r.GetEnableGlobalTrailer());
    AddProperty(elem, "local_header",                        r.GetEnableLocalHeader());
    AddProperty(elem, "local_trailer",                       r.GetEnableLocalTrailer());
    AddProperty(elem, "token_delay",                         r.GetTokenDelay());
    AddProperty(elem, "readout_speed",                       static_cast<unsigned int>(r.GetReadoutSpeedSelect()));
    AddProperty(elem, "strobe_select",                       static_cast<unsigned int>(r.GetStrobeSelect()));
    AddProperty(elem, "serial_delay",                        r.GetSerialDelay());
    AddProperty(elem, "readout_speed_single_cycle",          static_cast<unsigned int>(r.GetReadoutSingleCycleSpeed()));
    AddProperty(elem, "enable_error",                        r.GetEnableError());
    AddProperty(elem, "enable_error_bypass",                 r.GetEnableErrorBypass());
    AddProperty(elem, "enable_error_mark",                   r.GetEnableErrorMark());
    AddProperty(elem, "test_select",                         r.IsTest());

    fROOT->appendChild(elem);
  }

  bool
  XMLHandler::ReadRegister(std::string s, TDCControl* c, const BoardAddress& addr)
  {
    std::vector<PropertiesMap> maps = ParseRegister(s, addr);
    if (!maps.size()) {
      std::cerr << "FAILED to retrieve a TDCControl register with" << std::endl;
      addr.Dump(std::cerr);
      return false;
    }
    for (std::vector<PropertiesMap>::iterator map=maps.begin(); map!=maps.end(); map++) {
      if (map->GetProperty("register_name")!="TDCControl") { continue; }

      if (map->HasProperty("pll_reset"))             c->SetPLLReset(map->GetUIntProperty("pll_reset"));
      if (map->HasProperty("dll_reset"))             c->SetDLLReset(map->GetUIntProperty("dll_reset"));
      if (map->HasProperty("enable_channel"))        c->SetEnabledChannels(map->GetUIntProperty("enable_channel"));
      if (map->HasProperty("enable_channel_group0")) c->SetEnabledChannelsGroup0(map->GetUIntProperty("enable_channel_group0"));
      if (map->HasProperty("enable_channel_group1")) c->SetEnabledChannelsGroup1(map->GetUIntProperty("enable_channel_group1"));
      if (map->HasProperty("global_reset"))          c->SetGlobalReset(map->GetUIntProperty("global_reset"));
      if (map->HasProperty("enable_pattern"))        c->SetEnablePattern(static_cast<TDCControl::EnablePattern>(map->GetUIntProperty("enable_pattern")));
    }

    c->ComputeParity();
    return true;
  }

  bool
  XMLHandler::ReadRegister(std::string s, TDCSetup* r, const BoardAddress& addr)
  {
    std::vector<PropertiesMap> maps = ParseRegister(s, addr);
    if (!maps.size()) {
      std::cerr << "FAILED to retrieve a TDCSetup register with" << std::endl;
      addr.Dump(std::cerr);
      return false;
    }
    for (std::vector<PropertiesMap>::iterator map=maps.begin(); map!=maps.end(); map++) {
      if (map->GetProperty("register_name")!="TDCSetup") { continue; }

      if (map->HasProperty("enable_ttl_hit"))               r->SetEnableTTLHit(map->GetUIntProperty("enable_ttl_hit"));
      if (map->HasProperty("enable_ttl_clock"))             r->SetEnableTTLClock(map->GetUIntProperty("enable_ttl_clock"));
      if (map->HasProperty("enable_ttl_reset"))             r->SetEnableTTLReset(map->GetUIntProperty("enable_ttl_reset"));
      if (map->HasProperty("enable_ttl_control"))           r->SetEnableTTLControl(map->GetUIntProperty("enable_ttl_control"));
      if (map->HasProperty("enable_ttl_serial"))            r->SetEnableTTLSerial(map->GetUIntProperty("enable_ttl_serial"));
      if (map->HasProperty("enable_pair"))                  r->SetEdgesPairing(map->GetUIntProperty("enable_pair"));
      if (map->HasProperty("enable_matching"))              r->SetTriggerMatchingMode(map->GetUIntProperty("enable_matching"));
      if (map->HasProperty("roll_over"))                    r->SetRollOver(map->GetUIntProperty("roll_over"));
      if (map->HasProperty("dll_clock_source"))             r->SetDLLClockSource(static_cast<TDCSetup::DLLClockSource>(map->GetUIntProperty("dll_clock_source")));
      if (map->HasProperty("core_clock_source"))            r->SetCoreClockSource(static_cast<TDCSetup::CoreClockSource>(map->GetUIntProperty("core_clock_source")));
      if (map->HasProperty("io_clock_source"))              r->SetIOClockSource(static_cast<TDCSetup::IOClockSource>(map->GetUIntProperty("io_clock_source")));
      if (map->HasProperty("serial_clock_source"))          r->SetSerialClockSource(static_cast<TDCSetup::SerialClockSource>(map->GetUIntProperty("serial_clock_source")));
      if (map->HasProperty("dll_clock_delay"))              r->SetDLLClockDelayWord(map->GetUIntProperty("dll_clock_delay"));
      if (map->HasProperty("core_clock_delay"))             r->SetCoreClockDelayWord(map->GetUIntProperty("core_clock_delay"));
      if (map->HasProperty("io_clock_delay"))               r->SetIOClockDelayWord(map->GetUIntProperty("io_clock_delay"));
      if (map->HasProperty("serial_clock_delay"))           r->SetSerialClockDelayWord(map->GetUIntProperty("serial_clock_delay"));
      if (map->HasProperty("pll_control"))                  r->SetPLLControlWord(map->GetUIntProperty("pll_control"));
      if (map->HasProperty("dll_mode"))                     r->SetDLLMode(static_cast<TDCSetup::DLLSpeedMode>(map->GetUIntProperty("dll_mode")));
      if (map->HasProperty("mode_rc"))                      r->SetModeRC(map->GetUIntProperty("mode_rc"));
      if (map->HasProperty("mode_rc_compression"))          r->SetModeRCCompression(map->GetUIntProperty("mode_rc_compression"));
      if (map->HasProperty("enable_leading"))               r->SetLeadingMode(map->GetUIntProperty("enable_leading"));
      if (map->HasProperty("enable_trailing"))              r->SetTrailingMode(map->GetUIntProperty("enable_trailing"));
      if (map->HasProperty("test_mode"))                    r->SetTestMode(map->GetUIntProperty("test_mode"));
      if (map->HasProperty("test_invert"))                  r->SetTestInvert(map->GetUIntProperty("test_invert"));
      if (map->HasProperty("dead_time"))                    r->SetDeadTime(static_cast<TDCSetup::DeadTime>(map->GetUIntProperty("dead_time")));
      if (map->HasProperty("dll_control"))                  r->SetDLLControl(map->GetUIntProperty("dll_control"));
      if (map->HasProperty("vernier_offset"))               r->SetVernierOffset(map->GetUIntProperty("vernier_offset"));
      if (map->HasProperty("width_resolution"))             r->SetWidthResolution(static_cast<TDCSetup::WidthResolution>(map->GetUIntProperty("width_resolution")));
      if (map->HasProperty("low_power_mode"))               r->SetLowPowerMode(map->GetUIntProperty("low_power_mode"));
      if (map->HasProperty("rc_adjust"))                    r->SetRCAdjustmentWord(map->GetUIntProperty("rc_adjust"));
      if (map->HasProperty("dll_tap_adjust"))               r->SetDLLAdjustmentWord(map->GetUIntProperty("dll_tap_adjust"));
      if (map->HasProperty("coarse_count_offset"))          r->SetCoarseCountOffset(map->GetUIntProperty("coarse_count_offset"));
      for (unsigned short i=0; i<32; ++i) {
        std::ostringstream os; os << "offset" << i;
        if (map->HasProperty(os.str().c_str()))             r->SetChannelOffset(i, map->GetUIntProperty(os.str().c_str()));
      }
      if (map->HasProperty("direct_trigger"))               r->SetEnableDirectTrigger(map->GetUIntProperty("direct_trigger"));
      if (map->HasProperty("direct_bunch_reset"))           r->SetEnableDirectBunchReset(map->GetUIntProperty("direct_bunch_reset"));
      if (map->HasProperty("direct_event_reset"))           r->SetEnableDirectEventReset(map->GetUIntProperty("direct_event_reset"));
      if (map->HasProperty("separator_on_bunch_reset"))     r->SetEnableSeparatorOnBunchReset(map->GetUIntProperty("separator_on_bunch_reset"));
      if (map->HasProperty("separator_on_event_reset"))     r->SetEnableSeparatorOnEventReset(map->GetUIntProperty("separator_on_event_reset"));
      if (map->HasProperty("reset_channel_buffer_when_separator")) r->SetEnableResetChannelBufferWhenSeparator(map->GetUIntProperty("reset_channel_buffer_when_separator"));
      if (map->HasProperty("master_reset_on_event_reset"))  r->SetEnableMasterResetOnEventReset(map->GetUIntProperty("master_reset_on_event_reset"));
      if (map->HasProperty("master_reset_code"))            r->SetEnableMasterResetCode(map->GetUIntProperty("master_reset_code"));
      if (map->HasProperty("set_counters_on_bunch_reset"))  r->SetEnableSetCountersOnBunchReset(map->GetUIntProperty("set_counters_on_bunch_reset"));
      if (map->HasProperty("trigger_count_offset"))         r->SetTriggerCountOffset(map->GetUIntProperty("trigger_count_offset"));
      if (map->HasProperty("event_count_offset"))           r->SetEventCountOffset(map->GetUIntProperty("event_count_offset"));
      if (map->HasProperty("automatic_reject"))             r->SetEnableAutomaticReject(map->GetUIntProperty("automatic_reject"));
      if (map->HasProperty("enable_relative"))              r->SetEnableRelative(map->GetUIntProperty("enable_relative"));
      if (map->HasProperty("overflow_detection"))           r->SetEnableOverflowDetect(map->GetUIntProperty("overflow_detection"));
      if (map->HasProperty("readout_separator"))            r->SetEnableReadoutSeparator(map->GetUIntProperty("readout_separator"));
      if (map->HasProperty("readout_occupancy"))            r->SetEnableReadoutOccupancy(map->GetUIntProperty("readout_occupancy"));
      if (map->HasProperty("reject_fifo_full"))             r->SetRejectFIFOFull(map->GetUIntProperty("reject_fifo_full"));
      if (map->HasProperty("max_event_size"))               r->SetMaxEventSize(map->GetUIntProperty("max_event_size"));
      if (map->HasProperty("edge_resolution"))              r->SetEdgeResolution(static_cast<TDCSetup::EdgeResolution>(map->GetUIntProperty("edge_resolution")));
      if (map->HasProperty("match_window"))                 r->SetMatchWindow(map->GetUIntProperty("match_window"));
      if (map->HasProperty("search_window"))                r->SetSearchWindow(map->GetUIntProperty("search_window"));
      if (map->HasProperty("reject_count_offset"))          r->SetRejectCountOffset(map->GetUIntProperty("reject_count_offset"));
      if (map->HasProperty("readout_fifo_size"))            r->SetReadoutFIFOSize(map->GetUIntProperty("readout_fifo_size"));
      if (map->HasProperty("bypass_inputs"))                r->SetBypassInputs(map->GetUIntProperty("bypass_inputs"));
      if (map->HasProperty("tdc_id"))                       r->SetTDCId(map->GetUIntProperty("tdc_id"));
      if (map->HasProperty("jtag_readout"))                 r->SetEnableJTAGReadout(map->GetUIntProperty("jtag_readout"));
      if (map->HasProperty("serial"))                       r->SetEnableSerial(map->GetUIntProperty("serial"));
      if (map->HasProperty("bytewise"))                     r->SetEnableBytewise(map->GetUIntProperty("bytewise"));
      if (map->HasProperty("master"))                       r->SetMaster(map->GetUIntProperty("master"));
      if (map->HasProperty("keep_token"))                   r->SetKeepToken(map->GetUIntProperty("keep_token"));
      if (map->HasProperty("global_header"))                r->SetEnableGlobalHeader(map->GetUIntProperty("global_header"));
      if (map->HasProperty("global_trailer"))               r->SetEnableGlobalTrailer(map->GetUIntProperty("global_trailer"));
      if (map->HasProperty("local_header"))                 r->SetEnableLocalHeader(map->GetUIntProperty("local_header"));
      if (map->HasProperty("local_trailer"))                r->SetEnableLocalTrailer(map->GetUIntProperty("local_trailer"));
      if (map->HasProperty("token_delay"))                  r->SetTokenDelay(map->GetUIntProperty("token_delay"));
      if (map->HasProperty("readout_speed"))                r->SetReadoutSpeedSelect(static_cast<TDCSetup::ReadoutSpeed>(map->GetUIntProperty("readout_speed")));
      if (map->HasProperty("strobe_select"))                r->SetStrobeSelect(static_cast<TDCSetup::SerialStrobeType>(map->GetUIntProperty("strobe_select")));
      if (map->HasProperty("serial_delay"))                 r->SetSerialDelay(map->GetUIntProperty("serial_delay"));
      if (map->HasProperty("readout_speed_single_cycle"))   r->SetReadoutSingleCycleSpeed(static_cast<TDCSetup::ReadoutSingleCycleSpeed>(map->GetUIntProperty("readout_speed_single_cycle")));
      if (map->HasProperty("enable_error"))                 r->SetEnableError(map->GetUIntProperty("enable_error"));
      if (map->HasProperty("enable_error_bypass"))          r->SetEnableErrorBypass(map->GetUIntProperty("enable_error_bypass"));
      if (map->HasProperty("enable_error_mark"))            r->SetEnableErrorMark(map->GetUIntProperty("enable_error_mark"));
      if (map->HasProperty("test_select"))                  r->SetTest(map->GetUIntProperty("test_select"));
    }

    r->ComputeParity();
    return true;
  }

  bool
  XMLHandler::ReadRegister(std::string s, NINOThresholds* n, const BoardAddress& addr)
  {
    std::vector<PropertiesMap> maps = ParseRegister(s, addr);
    if (!maps.size()) {
      std::cerr << "FAILED to retrieve a NINO thresholds register" << std::endl;
      return false;
    }
    for (std::vector<PropertiesMap>::iterator map=maps.begin(); map!=maps.end(); map++) {
      if (map->GetProperty("register_name")!="NINOThresholds") { continue; }
      if (map->HasProperty("group0")) { n->SetValue(0, map->GetUIntProperty("group0")); }
      if (map->HasProperty("group1")) { n->SetValue(1, map->GetUIntProperty("group1")); }
      if (map->HasProperty("group2")) { n->SetValue(2, map->GetUIntProperty("group2")); }
      if (map->HasProperty("group3")) { n->SetValue(3, map->GetUIntProperty("group3")); }
      if (map->HasProperty("group4")) { n->SetValue(4, map->GetUIntProperty("group4")); }
      if (map->HasProperty("group5")) { n->SetValue(5, map->GetUIntProperty("group5")); }
      if (map->HasProperty("group6")) { n->SetValue(6, map->GetUIntProperty("group6")); }
      if (map->HasProperty("group7")) { n->SetValue(7, map->GetUIntProperty("group7")); }
    }

    return true;
  }

  DOMNode*
  XMLHandler::AddProperty(DOMNode* elem, const char* name, const char* value)
  {
    if (!elem) return 0;
    XMLCh str[100];

    XMLString::transcode(name, str, 99);
    /*DOMAttr* att = fDocument->createAttribute(str);
    elem->setAttributeNode(att);*/
    DOMNode* child = fDocument->createElement(str);
    elem->appendChild(child);

    XMLString::transcode(value, str, 99);
    DOMText* textNode = fDocument->createTextNode(str);
    child->appendChild(textNode);
    //fROOT->appendChild(first);
    //
    return child;
  }

  void
  XMLHandler::AddRangeProperty(DOMNode* elem, const char* name, unsigned long value, unsigned short num_bits)
  {
    if (!elem) return;
std::cerr << num_bits << std::endl;

    const unsigned short num_words = 32/num_bits;
    unsigned short prev_word = 0, prev_chan = 0;
    for (unsigned short i=0; i<num_words; ++i) {
      const unsigned short word = (value>>(i*num_bits))&((1<<(num_bits+1))-1);
      if (word!=prev_word || i==num_words-1) {
        std::ostringstream os; os << name << prev_chan << "-" << i-1;
        AddProperty(elem, os.str().c_str(), prev_word);

        prev_chan = i;
        prev_word = word;
      }
    }
  }

  void
  XMLHandler::SetAddressAttributes(DOMElement* elem, const BoardAddress& addr)
  {
    XMLCh key[100], value[100];
    std::stringstream mfec_addr, ccu_addr, i2c_addr;
    mfec_addr << "0x" << std::setfill ('0') << std::setw(4) << std::hex << addr.mfec;
    ccu_addr << "0x" << std::setfill ('0') << std::setw(4) << std::hex << addr.ccu;
    i2c_addr << "0x" << std::setfill ('0') << std::setw(4) << std::hex << addr.i2c;
    XMLString::transcode("mfec", key, 99); XMLString::transcode(mfec_addr.str().c_str(), value, 99); elem->setAttribute(key, value);
    XMLString::transcode("ccu", key, 99); XMLString::transcode(ccu_addr.str().c_str(), value, 99); elem->setAttribute(key, value);
    XMLString::transcode("i2c", key, 99); XMLString::transcode(i2c_addr.str().c_str(), value, 99); elem->setAttribute(key, value);
  }

  std::string
  XMLHandler::XMLString()
  {
    if (!fImpl) return "ERROR";
    DOMLSSerializer* serial = static_cast<DOMImplementationLS*>(fImpl)->createLSSerializer();
    XMLCh str[100];
    XMLString::transcode("format-pretty-print", str, 99);
    if (serial->getDomConfig()->canSetParameter(str, true))
      serial->getDomConfig()->setParameter(str, true);

    DOMLSOutput* out = fImpl->createLSOutput();
    if (!out) return "ERROR";

    MemBufFormatTarget ft;
    out->setByteStream(&ft);
    serial->write(fDocument, out);
    const XMLByte* w = ft.getRawBuffer();

    std::ostringstream os;
    for (unsigned int i=0; i<ft.getLen(); i++) { os << (char)w[i]; }
    return os.str();
  }

  std::vector<XMLHandler::PropertiesMap>
  XMLHandler::ParseRegister(std::string reg, const BoardAddress& addr)
  {
    XercesDOMParser* parser = new XercesDOMParser;
    parser->setValidationScheme(XercesDOMParser::Val_Never);
    /*parser->setDoSchema(false);
    parser->setLoadExternalDTD(false);*/
    parser->useScanner(XMLUni::fgWFXMLScanner);
    parser->setDoNamespaces(true);

    std::vector<PropertiesMap> out;

    try {
      MemBufInputSource reg_buf((const XMLByte*)reg.c_str(), reg.size(), "reg (in memory)", false);
      parser->parse(reg_buf);
      DOMDocument* document = parser->getDocument();
      DOMElement* root = document->getDocumentElement(); // TDCRegister root element
      if (!root) return out;

      DOMNodeList* registers = root->getChildNodes();
      for (unsigned int i=0; i<registers->getLength(); i++) {
        if (registers->item(i)->getNodeType()!=DOMNode::ELEMENT_NODE) continue;

        DOMNamedNodeMap* attr = registers->item(i)->getAttributes();
        bool found_mfec = false, found_ccu = false, found_i2c = false;
        for (unsigned int j=0; j<attr->getLength(); j++) {
          char* key = XMLString::transcode(attr->item(j)->getNodeName()), *value = XMLString::transcode(attr->item(j)->getNodeValue());
          if ((strcmp(key, "mfec")==0)) {
            unsigned int mfec_addr = (strcspn(value, "0x")==0) ? static_cast<unsigned long>(strtol(value, NULL, 0)) : static_cast<unsigned int>(atoi(value));
            if (mfec_addr==addr.mfec) found_mfec = true;
          }
          if ((strcmp(key, "ccu")==0)) {
            unsigned int ccu_addr = (strcspn(value, "0x")==0) ? static_cast<unsigned long>(strtol(value, NULL, 0)) : static_cast<unsigned int>(atoi(value));
            if (ccu_addr==addr.ccu) found_ccu = true;
          }
          if ((strcmp(key, "i2c")==0)) {
            unsigned int i2c_addr = (strcspn(value, "0x")==0) ? static_cast<unsigned long>(strtol(value, NULL, 0)) : static_cast<unsigned int>(atoi(value));
            if (i2c_addr==addr.i2c) found_i2c = true;
          }
        }

        PropertiesMap map;

        char* key = XMLString::transcode(registers->item(i)->getNodeName()); map.AddProperty("register_name", key); XMLString::release(&key);
        DOMNodeList* children = registers->item(i)->getChildNodes();

        if (!found_mfec or !found_ccu or !found_i2c) continue;

        //std::cout << "Found a " << map.GetProperty("register_name") << " for mfec=" << addr.mfec << ", ccu=" << addr.ccu << ", i2c=" << addr.i2c << std::endl;

        if (!children) return out;
        const XMLSize_t nodeCount = children->getLength();
        for (unsigned int j=0; j<nodeCount; j++) {
          DOMNode* currentNode = children->item(j);
          if (!currentNode->getNodeType() or currentNode->getNodeType()!=DOMNode::ELEMENT_NODE) continue;
          char* key = XMLString::transcode(currentNode->getNodeName());
          DOMText* prop = dynamic_cast<DOMText*>(currentNode->getFirstChild());
          char* value = XMLString::transcode(prop->getWholeText());
          DOMNamedNodeMap* attr = currentNode->getAttributes();
          std::ostringstream os_val; os_val << value;
          for (unsigned int k=0; k<attr->getLength(); k++) {
            char* att_key = XMLString::transcode(attr->item(k)->getNodeName()), *att_value = XMLString::transcode(attr->item(k)->getNodeValue());
            os_val << "\n" << att_key << ":" << att_value;
          }
          map.AddProperty(key, os_val.str().c_str());
          XMLString::release(&key); XMLString::release(&value);
        }

        out.push_back(map);
      }
      document->release();
    } catch (XMLException& e) {
      char* message = XMLString::transcode(e.getMessage());
      std::cout << "[XML] Error parsing file: " << message << std::endl;
      XMLString::release(&message);
    } catch (DOMException& e) {
      char* message = XMLString::transcode(e.getMessage());
      std::cout << "[DOM] Error parsing file: " << message << std::endl;
      XMLString::release(&message);
    }
    //delete parser;
    return out;
  }

  std::string
  XMLHandler::PropertiesMap::GetProperty(const char* name)
  {
    if (!HasProperty(name)) return "";
    std::map<std::string,std::string>::iterator it = fMap.find(name);
    return it->second;
  }

  unsigned int
  XMLHandler::PropertiesMap::GetUIntProperty(const char* name)
  {
    std::string prop = GetProperty(name);
    if (prop.empty()) return 0;
    return atoi(prop.c_str());
  }

  std::map<std::string,std::string>
  XMLHandler::PropertiesMap::GetStructuredProperty(const char* name)
  {
    std::map<std::string,std::string> out;
    std::string prop = GetProperty(name);
    if (prop.empty()) return out;
    size_t pos;
    std::stringstream ss(prop);
    while (getline(ss, prop, '\n')) {
      if (prop.empty()) continue;
      if ((pos=prop.find(":"))!=std::string::npos) { out.insert(std::pair<std::string,std::string>(prop.substr(0, pos), prop.substr(pos+1, prop.size()))); }
      else { out.insert(std::pair<std::string,std::string>("value", prop)); }
    }
    return out;
  }

  std::pair<BoardAddress, unsigned int>
  XMLHandler::PropertiesMap::GetNINOThresholdValue(const char* name)
  {
    BoardAddress addr(0, 0, 0);
    std::pair<BoardAddress, unsigned int> out(addr, 0);

    std::map<std::string,std::string> prop = GetStructuredProperty(name);
    //if (prop.size()!=4) return out;
    const char* mfec_str = prop["mfec"].c_str(), *ccu_str = prop["ccu"].c_str(), *i2c_str = prop["i2c"].c_str(), *value_str = prop["value"].c_str();
    unsigned int mfec_addr = (strcspn(mfec_str, "0x")==0) ? static_cast<unsigned long>(strtol(mfec_str, NULL, 0)) : static_cast<unsigned int>(atoi(mfec_str)),
                 ccu_addr = (strcspn(ccu_str, "0x")==0) ? static_cast<unsigned long>(strtol(ccu_str, NULL, 0)) : static_cast<unsigned int>(atoi(ccu_str)),
                 i2c_addr = (strcspn(i2c_str, "0x")==0) ? static_cast<unsigned long>(strtol(i2c_str, NULL, 0)) : static_cast<unsigned int>(atoi(i2c_str)),
                 value = (strcspn(value_str, "0x")==0) ? static_cast<unsigned long>(strtol(value_str, NULL, 0)) : static_cast<unsigned int>(atoi(value_str));

    addr = BoardAddress(mfec_addr, ccu_addr, i2c_addr);
    return std::pair<BoardAddress, unsigned int>(addr, value);
  }
}
