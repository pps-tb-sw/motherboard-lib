#ifndef TDCControl_h
#define TDCControl_h

#include "TDCRegister.h"
#include "TDCConstants.h"

namespace PPSTimingMB
{
  typedef enum TDCControlRegister {
    rEnablePattern=0, rGlobalReset,
    rEnableChannel0, rEnableChannel1,
    rDLLReset, rPLLReset, rControlParity,
    rNumControlRegisters
  } TDCControlRegister;
  std::ostream& operator<<(std::ostream& out, const TDCControlRegister& sp);
  inline unsigned short GetNumTDCControlRegisters() { return rNumControlRegisters; }
  /**
   * Object handling the control word provided by/to the HPTDC chip
   * \brief Control word to be sent to the HPTDC chip
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \author Lara Lloret Iglesias <lara@cern.ch>
   * \date 24 Apr 2015
   * \ingroup HPTDC
   */
  class TDCControl : public TDCRegister
  {
    public:
      typedef enum EnablePattern { OutputEnabled=0x5, OutputDisabled=0x4 } EnablePattern;

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
      inline void DisableAllChannels() { 
        //SetBits(kEnableChannel, 0, TDC_NUM_CHANNELS);
        for (unsigned int i=0; i<TDC_NUM_CHANNELS; i++) DisableChannel(i);
      }
      inline bool IsChannelEnabled(unsigned int id) const {
        if (id<0 or id>=TDC_NUM_CHANNELS) return false;
        return GetBits(kEnableChannel+id, 1);
      }
      inline void SetEnabledChannels(uint32_t ch) {
        SetEnabledChannels(ch&0xffff, (ch>>16)&0xffff);
      }
      inline void SetEnabledChannels(uint16_t group0, uint16_t group1) {
        SetEnabledChannelsGroup0(group0); SetEnabledChannelsGroup1(group1);
      }
      inline void SetEnabledChannelsGroup0(uint16_t poi) { SetBits(kEnableChannel, poi&0xffff, 16); }
      inline void SetEnabledChannelsGroup1(uint16_t poi) { SetBits(kEnableChannel+16, poi&0xffff, 16); }
      inline uint16_t GetEnabledChannelsGroup0() const {
        return GetBits(kEnableChannel, 16);
      }
      inline uint16_t GetEnabledChannelsGroup1() const {
        return GetBits(kEnableChannel+16, 16);
      }
      inline uint32_t GetEnabledChannels() const {
        uint16_t word1 = GetEnabledChannelsGroup0(), word2 = GetEnabledChannelsGroup1();
        return static_cast<uint32_t>(word1|(word2<<16));
      }

      void SetParity(const bool cp=true) { SetBits(kControlParity, cp, 1); }
      inline bool GetParity() const { return GetBits(kControlParity, 1); }
      void ComputeParity() { SetParity(TDCRegister::ComputeParityBit(0, TDC_CONTROL_BITS_NUM-1)); }

      /// Printout all useful values of this control register into an output stream
      void Dump(int verb=1, std::ostream& os=std::cout) const;
      //inline std::string GetXML() const { return XMLHandler::WriteRegister(this); }
      void SetConstantValues();
      uint32_t GetValue(const TDCControlRegister& v);

    private:
      static const bit kEnablePattern = 0;
      static const bit kGlobalReset = 4;
      static const bit kEnableChannel = 5;
      static const bit kDLLReset = 37;
      static const bit kPLLReset = 38;
      static const bit kControlParity = 39;
  };
}

#endif
