#include "XMLHandler.h"

XERCES_CPP_NAMESPACE_USE

/*DOMDocument* XMLHandler::fDocument = NULL;
DOMImplementation* XMLHandler::fImpl = NULL;*/

XMLHandler::XMLHandler()
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
  //XMLCh tempStr[100];
  //XMLString::transcode("root", tempStr, 99);
  //DOMDocument* doc = impl->createDocument(0, tempStr, 0);
}

void
XMLHandler::Terminate()
{
  fDocument->release();
  XMLPlatformUtils::Terminate();
}

std::string
XMLHandler::WriteRegister(const TDCControl& r)
{
  XMLCh str[100];

  XMLString::transcode("TDCControl", str, 99);
  fDocument = fImpl->createDocument(0, str, 0);
  fROOT = fDocument->getDocumentElement();

  AddProperty("control_parity", r.GetControlParity());
  AddProperty("pll_reset", r.GetPLLReset());
  AddProperty("dll_reset", r.GetDLLReset());
  AddProperty("enable_channel", r.GetEnabledChannels());
  AddProperty("global_reset", r.GetGlobalReset());
  AddProperty("enable_pattern", static_cast<unsigned int>(r.GetEnablePattern()));

  return XMLString();
}

std::string
XMLHandler::WriteRegister(const TDCSetup& r)
{
  XMLCh str[100];

  XMLString::transcode("TDCSetup", str, 99);
  fDocument = fImpl->createDocument(0, str, 0);
  fROOT = fDocument->getDocumentElement();

  AddProperty("setup_parity", r.GetSetupParity());
  AddProperty("enable_ttl_hit", r.GetEnableTTLHit());
  AddProperty("enable_ttl_clock", r.GetEnableTTLClock());
  AddProperty("enable_ttl_reset", r.GetEnableTTLReset());
  AddProperty("enable_ttl_control", r.GetEnableTTLControl());
  AddProperty("enable_ttl_serial", r.GetEnableTTLSerial());
  AddProperty("enable_pair", r.GetEdgesPairing());
  AddProperty("enable_matching", r.GetTriggerMatchingMode());
  AddProperty("roll_over", r.GetRollOver());
  AddProperty("pll_control", r.GetPLLControlWord());
  AddProperty("dll_mode", static_cast<unsigned int>(r.GetDLLMode()));
  AddProperty("mode_rc", r.GetModeRC());
  AddProperty("mode_rc_compression", r.GetModeRCCompression());
  AddProperty("enable_leading", r.GetLeadingMode());
  AddProperty("enable_trailing", r.GetTrailingMode());
  AddProperty("rc_adjust", r.GetRCAdjustmentWord());
  AddProperty("coarse_count_offset", r.GetCoarseCountOffset());
  AddProperty("trigger_count_offset", r.GetTriggerCountOffset());
  AddProperty("enable_relative", r.GetEnableRelative());
  AddProperty("match_window", r.GetMatchWindow());
  AddProperty("search_window", r.GetSearchWindow());
  AddProperty("reject_count_offset", r.GetRejectCountOffset());
  AddProperty("tdc_id", r.GetTDCId());

  return XMLString();
}

void
XMLHandler::AddProperty(const char* name, const char* value)
{
  if (!fDocument) return;
  XMLCh str[100];

  XMLString::transcode(name, str, 99);
  DOMElement* first = fDocument->createElement(str);

  XMLString::transcode(value, str, 99);
  DOMText* textNode = fDocument->createTextNode(str);
  first->appendChild(textNode);
  fROOT->appendChild(first);
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
  for (unsigned int i=0; i<ft.getLen(); i++) {
    os << (char)w[i];
  }
  return os.str();
}

