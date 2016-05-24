#ifndef TDCControl_h
#define TDCControl_h

#include "TDCRegister.h"
#include "TDCConstants.h"

//#include "XMLHandler.h"

/**
 * Object handling the control word provided by/to the HPTDC chip
 * \brief Control word to be sent to the HPTDC chip
 * \author Laurent Forthomme <laurent.forthomme@cern.ch>
 * \author Lara Lloret <lara@cern.ch>
 * \date 24 Apr 2015
 * \ingroup HPTDC
 */
class TDCControl : public TDCRegister
{
  public:
    typedef enum { OutputEnabled=0x5, OutputDisabled=0x4 } EnablePattern;
    //typedef enum { EnablePattern, GlobalReset, DLLReset, PLLReset } RegisterName;
  
  public:
    inline TDCControl() : TDCRegister(TDC_CONTROL_BITS_NUM) { SetConstantValues(); }
    inline TDCControl(const TDCControl& c) : TDCRegister(TDC_CONTROL_BITS_NUM, c) { SetConstantValues(); }
    inline TDCControl(const std::vector<uint8_t>& words) : TDCRegister(TDC_CONTROL_BITS_NUM, words) {;}
    
    inline void SetEnablePattern(const EnablePattern& ep=OutputEnabled) {
      SetBits(kEnablePattern, static_cast<unsigned int>(ep), 4);
    }
    inline EnablePattern GetEnablePattern() const { 
      return static_cast<EnablePattern>(GetBits(kEnablePattern, 4));
    }
    inline void SetGlobalReset(const bool gr=true) { SetBits(kGlobalReset, gr, 1); }
    inline bool GetGlobalReset() const { return GetBits(kGlobalReset, 1); }
    
    inline void SetDLLReset(const bool dr=true) { SetBits(kDLLReset, dr, 1); }
    inline bool GetDLLReset() const { return GetBits(kDLLReset, 1); }
    inline void SetPLLReset(const bool pr=true) { SetBits(kPLLReset, pr, 1); }
    inline bool GetPLLReset() const { return GetBits(kPLLReset, 1); }
    
    inline void EnableChannel(unsigned int id) {
      if (id<0 or id>=TDC_NUM_CHANNELS) return;
      SetBits(kEnableChannel+id, 1, 1);
    }
    inline void EnableAllChannels() {
      //SetBits(kEnableChannel, (unsigned long)0xffffffff, TDC_NUM_CHANNELS);
      for (unsigned int i=0; i<TDC_NUM_CHANNELS; i++) EnableChannel(i);
    }
    inline void DisableChannel(unsigned int id) {
      if (id<0 or id>=TDC_NUM_CHANNELS) return;
      SetBits(kEnableChannel+id, 0, 1);
    }
    inline void DisableAllChannels() { SetBits(kEnableChannel, 0, TDC_NUM_CHANNELS); }
    inline bool IsChannelEnabled(unsigned int id) const {
      if (id<0 or id>=TDC_NUM_CHANNELS) return false;
      return GetBits(kEnableChannel+id, 1);
    }
    inline void SetEnabledChannels(uint32_t ch) {
      SetBits(kEnableChannel, ch&0xffff, 16);
      SetBits(kEnableChannel+16, (ch>>16), 16);
    }
    inline uint32_t GetEnabledChannels() const { return static_cast<uint32_t>(GetBits(kEnableChannel, 32)); }

    void SetControlParity(const bool cp=true) { SetBits(kControlParity, cp, 1); }
    inline bool GetControlParity() const { return GetBits(kControlParity, 1); }
    
    /// Printout all useful values of this control register into an output stream
    void Dump(int verb=1, std::ostream& os=std::cout) const;
    //inline std::string GetXML() const { return XMLHandler::WriteRegister(this); }
    void SetConstantValues();
    
  private:
    static const bit kEnablePattern = 0;
    static const bit kGlobalReset = 4;
    static const bit kEnableChannel = 5;
    static const bit kDLLReset = 37;
    static const bit kPLLReset = 38;
    static const bit kControlParity = 39;
};

#endif
