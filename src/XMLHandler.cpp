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
  XMLHandler::WriteRegister(const TDCControl& r, unsigned int mfec, unsigned int ccu, unsigned int i2c)
  {
    XMLCh str[100];

    XMLString::transcode("TDCRegister", str, 99);
    fDocument = fImpl->createDocument(0, str, 0);
    
    PopulateControlRegister(r, mfec, ccu, i2c);

    return XMLString();
  }

  std::string
  XMLHandler::WriteRegister(const TDCSetup& r, unsigned int mfec, unsigned int ccu, unsigned int i2c)
  {
    XMLCh str[100];

    XMLString::transcode("TDCRegister", str, 99);
    fDocument = fImpl->createDocument(0, str, 0);

    PopulateSetupRegister(r, mfec, ccu, i2c);

    return XMLString();
  }

  std::string
  XMLHandler::WriteRegister(const TDCControl& c, const TDCSetup& s, unsigned int mfec, unsigned int ccu, unsigned int i2c)
  {
    XMLCh str[100];

    XMLString::transcode("TDCRegister", str, 99);
    fDocument = fImpl->createDocument(0, str, 0);

    PopulateControlRegister(c, mfec, ccu, i2c);
    PopulateSetupRegister(s, mfec, ccu, i2c);
    
    return XMLString();
  }

  void
  XMLHandler::PopulateControlRegister(const TDCControl& r, unsigned int mfec, unsigned int ccu, unsigned int i2c)
  {
    XMLCh str[100];

    XMLString::transcode("TDCControl", str, 99);
    DOMElement* elem = fDocument->createElement(str);
    fROOT = fDocument->getDocumentElement();

    {
      XMLCh key[100], value[100];
      XMLString::transcode("mfec", key, 99); XMLString::transcode(std::to_string((int)mfec).c_str(), value, 99); elem->setAttribute(key, value);
      XMLString::transcode("ccu", key, 99); XMLString::transcode(std::to_string((int)ccu).c_str(), value, 99); elem->setAttribute(key, value);
      XMLString::transcode("i2c", key, 99); XMLString::transcode(std::to_string((int)i2c).c_str(), value, 99); elem->setAttribute(key, value);
    }

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
  XMLHandler::PopulateSetupRegister(const TDCSetup& r, unsigned int mfec, unsigned int ccu, unsigned int i2c)
  {
    XMLCh str[100];

    XMLString::transcode("TDCSetup", str, 99);
    DOMElement* elem = fDocument->createElement(str);
    fROOT = fDocument->getDocumentElement();

    {
      XMLCh key[100], value[100];
      XMLString::transcode("mfec", key, 99); XMLString::transcode(std::to_string((int)mfec).c_str(), value, 99); elem->setAttribute(key, value);
      XMLString::transcode("ccu", key, 99); XMLString::transcode(std::to_string((int)ccu).c_str(), value, 99); elem->setAttribute(key, value);
      XMLString::transcode("i2c", key, 99); XMLString::transcode(std::to_string((int)i2c).c_str(), value, 99); elem->setAttribute(key, value);
    }

    AddProperty(elem, "enable_ttl_hit",       r.GetEnableTTLHit());
    AddProperty(elem, "enable_ttl_clock",     r.GetEnableTTLClock());
    AddProperty(elem, "enable_ttl_reset",     r.GetEnableTTLReset());
    AddProperty(elem, "enable_ttl_control",   r.GetEnableTTLControl());
    AddProperty(elem, "enable_ttl_serial",    r.GetEnableTTLSerial());
    AddProperty(elem, "enable_pair",          r.GetEdgesPairing());
    AddProperty(elem, "enable_matching",      r.GetTriggerMatchingMode());
    AddProperty(elem, "roll_over",            r.GetRollOver());
    AddProperty(elem, "pll_control",          r.GetPLLControlWord());
    AddProperty(elem, "dll_mode",             static_cast<unsigned int>(r.GetDLLMode()));
    AddProperty(elem, "mode_rc",              r.GetModeRC());
    AddProperty(elem, "mode_rc_compression",  r.GetModeRCCompression());
    AddProperty(elem, "enable_leading",       r.GetLeadingMode());
    AddProperty(elem, "enable_trailing",      r.GetTrailingMode());
    AddProperty(elem, "rc_adjust",            r.GetRCAdjustmentWord());
    AddProperty(elem, "coarse_count_offset",  r.GetCoarseCountOffset());
    AddProperty(elem, "trigger_count_offset", r.GetTriggerCountOffset());
    AddProperty(elem, "enable_relative",      r.GetEnableRelative());
    AddProperty(elem, "match_window",         r.GetMatchWindow());
    AddProperty(elem, "search_window",        r.GetSearchWindow());
    AddProperty(elem, "reject_count_offset",  r.GetRejectCountOffset());
    AddProperty(elem, "tdc_id",               r.GetTDCId());

    fROOT->appendChild(elem);
  }

  bool
  XMLHandler::ReadRegister(std::string s, TDCControl* c, unsigned int mfec, unsigned int ccu, unsigned int i2c)
  {
    std::vector<PropertiesMap> maps = ParseRegister(s, mfec, ccu, i2c);
    if (!maps.size()) {
      std::cerr << "FAILED to retrieve a TDCControl register with" << "\n\t"
                << "MFEC=" << mfec << "\n\t"
                << "CCU =" << ccu << "\n\t"
                << "I2C =" << i2c << std::endl;
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
  XMLHandler::ReadRegister(std::string s, TDCSetup* r, unsigned int mfec, unsigned int ccu, unsigned int i2c)
  {
    std::vector<PropertiesMap> maps = ParseRegister(s, mfec, ccu, i2c);
    if (!maps.size()) {
      std::cerr << "FAILED to retrieve a TDCSetup register with" << "\n\t"
                << "MFEC=" << mfec << "\n\t"
                << "CCU =" << ccu << "\n\t"
                << "I2C =" << i2c << std::endl;
      return false;
    }
    for (std::vector<PropertiesMap>::iterator map=maps.begin(); map!=maps.end(); map++) {
      if (map->GetProperty("register_name")!="TDCSetup") { continue; }

      if (map->HasProperty("enable_ttl_hit"))       r->SetEnableTTLHit(map->GetUIntProperty("enable_ttl_hit"));
      if (map->HasProperty("enable_ttl_clock"))     r->SetEnableTTLClock(map->GetUIntProperty("enable_ttl_clock"));
      if (map->HasProperty("enable_ttl_reset"))     r->SetEnableTTLReset(map->GetUIntProperty("enable_ttl_reset"));
      if (map->HasProperty("enable_ttl_control"))   r->SetEnableTTLControl(map->GetUIntProperty("enable_ttl_control"));
      if (map->HasProperty("enable_ttl_serial"))    r->SetEnableTTLSerial(map->GetUIntProperty("enable_ttl_serial"));
      if (map->HasProperty("enable_pair"))          r->SetEdgesPairing(map->GetUIntProperty("enable_pair"));
      if (map->HasProperty("enable_matching"))      r->SetTriggerMatchingMode(map->GetUIntProperty("enable_matching"));
      if (map->HasProperty("roll_over"))            r->SetRollOver(map->GetUIntProperty("roll_over"));
      if (map->HasProperty("pll_control"))          r->SetPLLControlWord(map->GetUIntProperty("pll_control"));
      if (map->HasProperty("dll_mode"))             r->SetDLLMode(static_cast<TDCSetup::DLLSpeedMode>(map->GetUIntProperty("dll_mode")));
      if (map->HasProperty("mode_rc"))              r->SetModeRC(map->GetUIntProperty("mode_rc"));
      if (map->HasProperty("mode_rc_compression"))  r->SetModeRCCompression(map->GetUIntProperty("mode_rc_compression"));
      if (map->HasProperty("enable_leading"))       r->SetLeadingMode(map->GetUIntProperty("enable_leading"));
      if (map->HasProperty("enable_trailing"))      r->SetTrailingMode(map->GetUIntProperty("enable_trailing"));
      if (map->HasProperty("rc_adjust"))            r->SetRCAdjustmentWord(map->GetUIntProperty("rc_adjust"));
      if (map->HasProperty("coarse_count_offset"))  r->SetCoarseCountOffset(map->GetUIntProperty("coarse_count_offset"));
      if (map->HasProperty("trigger_count_offset")) r->SetTriggerCountOffset(map->GetUIntProperty("trigger_count_offset"));
      if (map->HasProperty("enable_relative"))      r->SetEnableRelative(map->GetUIntProperty("enable_relative"));
      if (map->HasProperty("match_window"))         r->SetMatchWindow(map->GetUIntProperty("match_window"));
      if (map->HasProperty("search_window"))        r->SetSearchWindow(map->GetUIntProperty("search_window"));
      if (map->HasProperty("reject_count_offset"))  r->SetRejectCountOffset(map->GetUIntProperty("reject_count_offset"));
      if (map->HasProperty("tdc_id"))               r->SetTDCId(map->GetUIntProperty("tdc_id"));
    }

    r->ComputeParity();
    return true;
  }

  void
  XMLHandler::AddProperty(DOMElement* elem, const char* name, const char* value)
  {
    if (!elem) return;
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
  XMLHandler::ParseRegister(std::string reg, unsigned int mfec, unsigned int ccu, unsigned int i2c)
  {
    XercesDOMParser* parser = new XercesDOMParser;
    parser->setValidationScheme(XercesDOMParser::Val_Never);
    parser->setDoNamespaces(false);
    parser->setDoSchema(false);
    parser->setLoadExternalDTD(false);

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
          if ((strcmp(key, "mfec")==0) and static_cast<unsigned int>(atoi(value))==mfec) found_mfec = true;
          if ((strcmp(key, "ccu")==0) and static_cast<unsigned int>(atoi(value))==ccu) found_ccu = true;
          if ((strcmp(key, "i2c")==0) and static_cast<unsigned int>(atoi(value))==i2c) found_i2c = true;
        }
        if (!found_mfec or !found_ccu or !found_i2c) continue;

        PropertiesMap map;

        char* key = XMLString::transcode(registers->item(i)->getNodeName()); map.AddProperty("register_name", key); XMLString::release(&key);
        DOMNodeList* children = registers->item(i)->getChildNodes();

        //std::cout << "Found a " << map.GetProperty("register_name") << " for mfec=" << mfec << ", ccu=" << ccu << ", i2c=" << i2c << std::endl;

        if (!children) return out;
        const XMLSize_t nodeCount = children->getLength();
        for (unsigned int j=0; j<nodeCount; j++) {
          DOMNode* currentNode = children->item(j);
          if (!currentNode->getNodeType() or currentNode->getNodeType()!=DOMNode::ELEMENT_NODE) continue;
          char* key = XMLString::transcode(currentNode->getNodeName());
          DOMText* prop = dynamic_cast<DOMText*>(currentNode->getFirstChild());
          char* value = XMLString::transcode(prop->getWholeText());
          //std::cout << "----->" << key << " = " << value << std::endl;
          map.AddProperty(key, value);
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
    if (prop=="") return 0;
    return atoi(prop.c_str());
  }
}
