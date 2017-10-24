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
#include "NINOThresholds.h"
#include "BoardAddress.h"

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
      std::map<std::string,std::string> GetStructuredProperty(const char* name);
      std::pair<BoardAddress, unsigned int> GetNINOThresholdValue(const char* name);
     private:
      std::map<std::string,std::string> fMap;
    };

    /// Extract a XML output of a TDCControl register
    inline std::string WriteRegister(const TDCControl& r, unsigned int mfec, unsigned int ccu, unsigned int i2c) { return WriteRegister(r, BoardAddress(mfec, ccu, i2c)); }
    /// Extract a XML output of a TDCControl register
    std::string WriteRegister(const TDCControl& r, const BoardAddress& addr);
    /// Parse a TDCControl register out of a XML configuration file
    inline bool ReadRegister(std::string str, TDCControl* c, unsigned int mfec, unsigned int ccu, unsigned int i2c) { return ReadRegister(str, c, BoardAddress(mfec, ccu, i2c)); }
    /// Parse a TDCControl register out of a XML configuration file
    bool ReadRegister(std::string, TDCControl* c, const BoardAddress& addr);

    /// Extract a XML output of a TDCSetup register
    inline std::string WriteRegister(const TDCSetup& r, unsigned int mfec, unsigned int ccu, unsigned int i2c) { return WriteRegister(r, BoardAddress(mfec, ccu, i2c)); }
    /// Extract a XML output of a TDCSetup register
    std::string WriteRegister(const TDCSetup& r, const BoardAddress& addr);
    /// Parse a TDCSetup register out of a XML configuration file
    inline bool ReadRegister(std::string str, TDCSetup* s, unsigned int mfec, unsigned int ccu, unsigned int i2c) { return ReadRegister(str, s, BoardAddress(mfec, ccu, i2c)); }
    /// Parse a TDCSetup register out of a XML configuration file
    bool ReadRegister(std::string, TDCSetup* s, const BoardAddress& addr);

     /// Extract a XML output of a NINO Thresholds register
    inline std::string WriteRegister(const NINOThresholds& n, unsigned int mfec, unsigned int ccu, unsigned int i2c) { return WriteRegister(n, BoardAddress(mfec, ccu, i2c)); }
    /// Extract a XML output of a NINO thresholds register
    std::string WriteRegister(const NINOThresholds& n, const BoardAddress& addr);
    /// Parse a NINO thresholds register out of a XML configuration file
    inline bool ReadRegister(std::string str, NINOThresholds* n, unsigned int mfec, unsigned int ccu, unsigned int i2c) { return ReadRegister(str, n, BoardAddress(mfec, ccu, i2c)); }
    /// Parse a NINO thresholds register out of a XML configuration file
    bool ReadRegister(std::string, NINOThresholds* n, const BoardAddress& addr);

    /// Extract a XML output of a TDCControl and a TDCSetup register
    inline std::string WriteRegister(const TDCControl& c, const TDCSetup& s, unsigned int mfec, unsigned int ccu, unsigned int i2c) { return WriteRegister(c, s, BoardAddress(mfec, ccu, i2c)); }
    /// Extract a XML output of a TDCControl and a TDCSetup register
    std::string WriteRegister(const TDCControl& c, const TDCSetup& s, const BoardAddress& addr);

    /// Extract a XML output of a TDCControl, a TDCSetup, and a NINO thresholds register
    inline std::string WriteRegister(const TDCControl& c, const TDCSetup& s, const NINOThresholds& n, unsigned int mfec, unsigned int ccu, unsigned int i2c) {
      return WriteRegister(c, s, n, BoardAddress(mfec, ccu, i2c));
    }
    /// Extract a XML output of a TDCControl, a TDCSetup, and a NINO thresholds register
    std::string WriteRegister(const TDCControl& c, const TDCSetup& s, const NINOThresholds& n, const BoardAddress& addr);

   private:
    void Initialize();
    void Terminate();

    void PopulateControlRegister(const TDCControl& c, const BoardAddress&);
    void PopulateSetupRegister(const TDCSetup& s, const BoardAddress&);
    void PopulateNINOThresholds(const NINOThresholds& n, const BoardAddress&);

    DOMNode* AddProperty(DOMNode* elem, const char*, const char*);
    DOMNode* AddProperty(DOMNode* elem, const char* name, unsigned int value) {
      std::ostringstream os; os << value;
      return AddProperty(elem, name, os.str().c_str());
    }
    void AddRangeProperty(DOMNode* elem, const char* name, unsigned long value, unsigned short num_bits);
    void SetAddressAttributes(DOMElement* elem, const BoardAddress&);
    std::string GetProperty(const char* name);
    unsigned int GetUIntProperty(const char* name);
    std::string XMLString();
    std::vector<PropertiesMap> ParseRegister(std::string, const BoardAddress&);
    DOMElement* fROOT;
    DOMImplementation* fImpl;
    DOMDocument* fDocument;
  };
}

#endif
