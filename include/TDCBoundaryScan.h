#ifndef TDCBoundaryScan_h
#define TDCBoundaryScan_h

#include "TDCRegister.h"

/**
 * 
 * \author Laurent Forthomme <laurent.forthomme@cern.ch>
 * \date 24 Apr 2015
 * \date May 2016
 * \ingroup HPTDC
 */
class TDCBoundaryScan : public TDCRegister
{
  public:
    inline TDCBoundaryScan() : TDCRegister(TDC_BS_BITS_NUM) {
      SetConstantValues(); }
    inline TDCBoundaryScan(const TDCBoundaryScan& bs) :
      TDCRegister(TDC_BS_BITS_NUM, bs) { SetConstantValues(); }

    inline bool IsTokenOut() const { return GetBits(kTokenOut, 1); }
    inline bool IsStrobeOut() const { return GetBits(kStrobeOut, 1); }
    inline bool IsSerialOut() const { return GetBits(kSerialOut, 1); }
    inline bool IsTest() const { return GetBits(kTest, 1); }
    inline bool IsError() const { return GetBits(kError, 1); }
    inline bool IsDataReady() const { return GetBits(kDataReady, 1); }
    inline bool IsParallelEnabled() const { return GetBits(kParallelEnable, 1); }
    inline bool HasParallelDataOut(unsigned short channel_id) const {
      if (channel_id<0 or channel_id>31) return false;
      return GetBits(kParallelDataOut+channel_id, 1);
    }
    inline bool IsEncodedControl() const { return GetBits(kEncodedControl, 1); }
    inline bool IsTrigger() const { return GetBits(kTrigger, 1); }
    inline bool HasTrigger() const { return GetBits(kTrigger, 1); }
    inline bool HasEventReset() const { return GetBits(kEventReset, 1); }
    inline bool HasBunchReset() const { return GetBits(kBunchReset, 1); }
    inline bool IsGettingData() const { return GetBits(kGetData, 1); }
    inline bool IsSerialBypassIn() const { return GetBits(kSerialBypassIn, 1); }
    inline bool IsSerialIn() const { return GetBits(kSerialIn, 1); }
    inline bool IsTokenBypassIn() const { return GetBits(kTokenBypassIn, 1); }
    inline bool IsTokenIn() const { return GetBits(kTokenIn, 1); }
    inline bool IsReset() const { return GetBits(kReset, 1); }
    inline bool HasAuxiliaryClock() const { return GetBits(kAuxClock, 1); }
    inline bool HasClock() const { return GetBits(kClk, 1); }
    inline bool HasHit(unsigned short channel_id) const {
      if (channel_id<0 or channel_id>31) return false;
      return GetBits(kHit+channel_id, 1);
    }
    
    /// Set all hardcoded values to this register
    void SetConstantValues();
    /// Printout all useful values of this status register into an output stream
    void Dump() const;

  private:
    static const bit kTokenOut = 0;
    static const bit kStrobeOut = 1;
    static const bit kSerialOut = 2;
    static const bit kTest = 3;
    static const bit kError = 4;
    static const bit kDataReady = 5;
    static const bit kParallelEnable = 6;
    static const bit kParallelDataOut = 7;
    static const bit kEncodedControl = 39;
    static const bit kTrigger = 40;
    static const bit kEventReset = 41;
    static const bit kBunchReset = 42;
    static const bit kGetData = 43;
    static const bit kSerialBypassIn = 44;
    static const bit kSerialIn = 45;
    static const bit kTokenBypassIn = 46;
    static const bit kTokenIn = 47;
    static const bit kReset = 48;
    static const bit kAuxClock = 49;
    static const bit kClk = 50;
    static const bit kHit = 51;
};

#endif
