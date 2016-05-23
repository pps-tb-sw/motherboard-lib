#include <iostream>
#include <sstream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp> //FIXME for debugging
#include <xercesc/framework/MemBufFormatTarget.hpp>

#include "TDCControl.h"
#include "TDCSetup.h"

XERCES_CPP_NAMESPACE_USE

class XMLHandler
{
 public:
  XMLHandler();
  ~XMLHandler();

  /*static std::string WriteRegister(const TDCControl& r);
  static std::string WriteRegister(const TDCSetup& r);*/
  std::string WriteRegister(const TDCControl& r);
  std::string WriteRegister(const TDCSetup& r);

 private:
  void Initialize();
  void Terminate();
  void AddProperty(const char*, const char*);
  void AddProperty(const char* name, unsigned int value) {
    std::ostringstream os; os << value;
    AddProperty(name, os.str().c_str());
  }
  std::string XMLString();
  /*static DOMImplementation* fImpl;
  static DOMDocument* fDocument;*/
  DOMImplementation* fImpl;
  DOMDocument* fDocument;
  DOMElement* fROOT;
};
