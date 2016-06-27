#ifndef XMLHandler_h
#define XMLHandler_h

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

namespace PPSTimingMB
{
  /**
   * \brief XML input/output handler
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date 23 May 2016
   * \ingroup XML
   */
  class XMLHandler
  {
   public:
    XMLHandler();
    ~XMLHandler();

    /// A map of properties retrieved from a parsed XML file
    class PropertiesMap
    {
     public:
      inline PropertiesMap() { fMap.clear(); }
      inline ~PropertiesMap() { fMap.clear(); }

      /// Feed a new key/value property to the map
      inline void AddProperty(const char* name, const char* value) { fMap.insert(std::pair<std::string,std::string>(std::string(name), std::string(value))); }
      /// Check if a key is present in the map
      inline bool HasProperty(const char* name) { return (fMap.count(std::string(name))>0); }
      /// Retrieve the (string) value associated with a key
      std::string GetProperty(const char* name);
      /// Retrieve the (unsigned integer) value associated with a key
      unsigned int GetUIntProperty(const char* name);
     private:
      std::map<std::string,std::string> fMap;
    };

    /*static std::string WriteRegister(const TDCControl& r);
    static std::string WriteRegister(const TDCSetup& r);*/
    std::string WriteRegister(const TDCControl& r, unsigned int mfec, unsigned int ccu, unsigned int i2c);
    std::string WriteRegister(const TDCSetup& r, unsigned int mfec, unsigned int ccu, unsigned int i2c);
    std::string WriteRegister(const TDCControl& c, const TDCSetup& s, unsigned int mfec, unsigned int ccu, unsigned int i2c);
    bool ReadRegister(std::string, TDCControl* c, unsigned int mfec, unsigned int ccu, unsigned int i2c);
    bool ReadRegister(std::string, TDCSetup* s, unsigned int mfec, unsigned int ccu, unsigned int i2c);

   private:
    void Initialize();
    void Terminate();

    void PopulateControlRegister(const TDCControl& c, unsigned int mfec, unsigned int ccu, unsigned int i2c);
    void PopulateSetupRegister(const TDCSetup& s, unsigned int mfec, unsigned int ccu, unsigned int i2c);

    void AddProperty(DOMElement* elem, const char*, const char*);
    void AddProperty(DOMElement* elem, const char* name, unsigned int value) {
      std::ostringstream os; os << value;
      AddProperty(elem, name, os.str().c_str());
    }
    std::string GetProperty(const char* name);
    unsigned int GetUIntProperty(const char* name);
    std::string XMLString();
    std::vector<PropertiesMap> ParseRegister(std::string, unsigned int mfec, unsigned int ccu, unsigned int i2c);
    /*static DOMImplementation* fImpl;
    static DOMDocument* fDocument;*/
    DOMElement* fROOT;
    DOMImplementation* fImpl;
    DOMDocument* fDocument;
  };
}

#endif
