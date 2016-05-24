#include <iostream>
#include <sstream>
#include <map>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
//#include <xercesc/framework/StdOutFormatTarget.hpp> //FIXME for debugging
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

#include "TDCControl.h"
#include "TDCSetup.h"

XERCES_CPP_NAMESPACE_USE

class XMLHandler
{
 public:
  XMLHandler();
  ~XMLHandler();

  class PropertiesMap
  {
   public:
    inline PropertiesMap() { fMap.clear(); }
    inline ~PropertiesMap() { fMap.clear(); }

    inline void AddProperty(const char* name, const char* value) { fMap.insert(std::pair<std::string,std::string>(std::string(name), std::string(value))); }
    inline bool HasProperty(const char* name) { return (fMap.count(std::string(name))>0); }
    std::string GetProperty(const char* name);
    unsigned int GetUIntProperty(const char* name);
   private:
    std::map<std::string,std::string> fMap;
  };

  /*static std::string WriteRegister(const TDCControl& r);
  static std::string WriteRegister(const TDCSetup& r);*/
  std::string WriteRegister(const TDCControl& r);
  std::string WriteRegister(const TDCSetup& r);
  void ReadRegister(std::string, TDCControl* c);
  void ReadRegister(std::string, TDCSetup* s);

 private:
  void Initialize();
  void Terminate();
  void AddProperty(const char*, const char*);
  void AddProperty(const char* name, unsigned int value) {
    std::ostringstream os; os << value;
    AddProperty(name, os.str().c_str());
  }
  std::string GetProperty(const char* name);
  unsigned int GetUIntProperty(const char* name);
  std::string XMLString();
  PropertiesMap ParseRegister(std::string);
  /*static DOMImplementation* fImpl;
  static DOMDocument* fDocument;*/
  DOMImplementation* fImpl;
  DOMDocument* fDocument;
  DOMElement* fROOT;
};
