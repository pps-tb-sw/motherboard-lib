#ifndef TDCInternalCoreTest_h
#define TDCInternalCoreTest_h

#include "TDCRegister.h"

namespace PPSTimingMB
{
  class TDCInternalCoreTest : public TDCRegister
  {
   public:
    inline TDCInternalCoreTest() : TDCRegister(TDC_ICT_BITS_NUM) {;}
    inline TDCInternalCoreTest(const TDCInternalCoreTest& c) : TDCRegister(TDC_ICT_BITS_NUM, c) {;}
    inline TDCInternalCoreTest(const std::vector<uint8_t>& words) : TDCRegister(TDC_ICT_BITS_NUM, words) {;}
    inline ~TDCInternalCoreTest() {;}

    typedef enum {
      cmsIdle = 0x1, cmsHeader = 0x2, cmsLostHeader = 0x4, cmsError = 0x8,
      cmsTrailer = 0x10, cmsLostTrailer = 0x20, cmsSeparator = 0x40,
      cmsOccupancy = 0x80, cmsMatching = 0x100
    } CommonMatchingState;
    inline CommonMatchingState GetCommonMatchingState() const {
      return static_cast<CommonMatchingState>(GetBits(kCommonMatchingState, 9));
    }

    typedef struct {
      uint16_t bunch_id, event_id;
      bool separator, trigger_lost, parity;
    } TriggerData;
    inline TriggerData GetTriggerData() const {
      uint32_t word = GetBits(kTriggerData, 27);
      TriggerData out;
      out.bunch_id =      word     &0xfff;
      out.event_id =     (word>>12)&0xfff;
      out.separator =    (word>>24)&0x1;
      out.trigger_lost = (word>>25)&0x1;
      out.parity =       (word>>26)&0x1;
      return out;
    }

    typedef enum {
      msInvalid = 0x0, msIdle = 0x1, msWriteOccupancy = 0x2, msActive = 0x4,
      msWaitingForSeparator = 0x8, msWaitEnd = 0x10
    } MatchingState;
    inline MatchingState GetMatchingState(unsigned short group_id) const {
      if (group_id<0 or group_id>3) return msInvalid;
      const bit to_read_lsb = kGroup0MatchingState-group_id*(6+35+2);
      return static_cast<MatchingState>(GetBits(to_read_lsb, 5));
    }
    inline MatchingState GetMatchingStateGroup3() const { return GetMatchingState(3); }
    inline MatchingState GetMatchingStateGroup2() const { return GetMatchingState(2); }
    inline MatchingState GetMatchingStateGroup1() const { return GetMatchingState(1); }
    inline MatchingState GetMatchingStateGroup0() const { return GetMatchingState(0); }

    typedef struct {
      uint16_t edge_fine_time, edge_coarse_time;
      bool edge_type;
      uint16_t width, channel;
      bool error, overflow_start, overflow_stop, separator, parity;
    } L1Data;
    inline L1Data GetL1Data(unsigned short group_id) const {
      L1Data out;
      if (group_id<0 or group_id>3) return out;
      const bit to_read_lsb = kGroup0L1Data-group_id*(6+35+2);
      uint32_t word1 = GetBits(to_read_lsb, 32), word2 = GetBits(to_read_lsb+32, 3);
      out.edge_fine_time =    word1     &0xff;
      out.edge_coarse_time = (word1>> 8)&0xfff;
      out.width =            (word1>>20)&0x7f;
      out.edge_type =        (word1>>20)&0x1;
      out.channel =          (word1>>27)&0x3;
      out.error =            (word1>>30)&0x1;
      out.overflow_start =   (word1>>31)&0x1;
      out.overflow_stop =     word2     &0x1;
      out.separator =        (word2>>1) &0x1;
      out.parity =           (word2>>2) &0x1;
      return out;
    }
    inline L1Data GetL1DataGroup3() const { return GetL1Data(3); }
    inline L1Data GetL1DataGroup2() const { return GetL1Data(2); }
    inline L1Data GetL1DataGroup1() const { return GetL1Data(1); }
    inline L1Data GetL1DataGroup0() const { return GetL1Data(0); }

    inline bool GetL1Empty(unsigned short group_id) const {
      if (group_id<0 or group_id>3) return false; //FIXME
      return static_cast<bool>(GetBits(kGroup0L1Empty-group_id*(6+35+2), 1));
    }
    inline bool GetL1EmptyGroup3() const { return GetL1Empty(3); }
    inline bool GetL1EmptyGroup2() const { return GetL1Empty(2); }
    inline bool GetL1EmptyGroup1() const { return GetL1Empty(1); }
    inline bool GetL1EmptyGroup0() const { return GetL1Empty(0); }

    inline bool GetL1Ready(unsigned short group_id) const {
      if (group_id<0 or group_id>3) return false; //FIXME
      return static_cast<bool>(GetBits(kGroup0L1Ready-group_id*(6+35+2), 1));
    }
    inline bool GetL1ReadyGroup3() const { return GetL1Ready(3); }
    inline bool GetL1ReadyGroup2() const { return GetL1Ready(2); }
    inline bool GetL1ReadyGroup1() const { return GetL1Ready(1); }
    inline bool GetL1ReadyGroup0() const { return GetL1Ready(0); }

    typedef struct {
      uint32_t first_vernier, first_coarse1, first_coarse2;
      bool first_coarse1_parity, first_coarse2_parity, first_edge_type;
      uint32_t second_vernier, second_coarse1, second_coarse2;
      bool second_coarse1_parity, second_coarse2_parity, second_edge_type;
    } HitData;
    inline HitData GetHitData(unsigned short group_id) const {
      HitData out;
      if (group_id<0 or group_id>3) return out;
      const bit to_read_lsb = kGroup0HitData-group_id*135;
      // first vernier
      uint32_t word1 = GetBits(to_read_lsb, 32);
      uint32_t word2 = GetBits(to_read_lsb+32, 32), word3 = GetBits(to_read_lsb+64, 1);
      // second vernier
      uint32_t word4 = GetBits(to_read_lsb+65, 32);
      uint32_t word5 = GetBits(to_read_lsb+97, 32), word6 = GetBits(to_read_lsb+129, 1);
      out.first_vernier =          word1     &0xffffffff;
      out.first_coarse1 =          word2     &0x7fff;
      out.first_coarse1_parity =  (word2>>15)&0x1;
      out.first_coarse2 =         (word2>>16)&0x7fff;
      out.first_coarse2_parity =  (word2>>31)&0x1;
      out.first_edge_type =        word3     &0x1;
      out.second_vernier =         word4     &0xffffffff;
      out.second_coarse1 =         word5     &0x7fff;
      out.second_coarse1_parity = (word5>>15)&0x1;
      out.second_coarse2 =        (word5>>16)&0x7fff;
      out.second_coarse2_parity = (word5>>31)&0x1;
      out.second_edge_type =       word6     &0x1;
      return out;
    }
    inline HitData GetHitDataGroup3() const { return GetHitData(3); }
    inline HitData GetHitDataGroup2() const { return GetHitData(2); }
    inline HitData GetHitDataGroup1() const { return GetHitData(1); }
    inline HitData GetHitDataGroup0() const { return GetHitData(0); }

    inline uint16_t GetHitChannel(unsigned short group_id) const {
      if (group_id<0 or group_id>3) return 0;
      return GetBits(kGroup0HitChannel-group_id*135, 3);
    }
    inline uint16_t GetHitChannelGroup3() const { return GetHitChannel(3); }
    inline uint16_t GetHitChannelGroup2() const { return GetHitChannel(2); }
    inline uint16_t GetHitChannelGroup1() const { return GetHitChannel(1); }
    inline uint16_t GetHitChannelGroup0() const { return GetHitChannel(0); }


    inline bool GetHitSelectError(unsigned short group_id) const {
      if (group_id<0 or group_id>3) return 0;
      return GetBits(kGroup0HitSelectError-group_id*135, 3);
    }
    inline bool GetHitSelectErrorGroup3() const { return GetHitSelectError(3); }
    inline bool GetHitSelectErrorGroup2() const { return GetHitSelectError(2); }
    inline bool GetHitSelectErrorGroup1() const { return GetHitSelectError(1); }
    inline bool GetHitSelectErrorGroup0() const { return GetHitSelectError(0); }

    inline bool GetHitLoad(unsigned short group_id) const {
      if (group_id<0 or group_id>3) return 0;
      return GetBits(kGroup0HitLoad-group_id*135, 3);
    }
    inline bool GetHitLoadGroup3() const { return GetHitLoad(3); }
    inline bool GetHitLoadGroup2() const { return GetHitLoad(2); }
    inline bool GetHitLoadGroup1() const { return GetHitLoad(1); }
    inline bool GetHitLoadGroup0() const { return GetHitLoad(0); }

    void Dump(int verb=1, std::ostream& os=std::cout) const;
    inline void SetConstantValues() {;}

   private:
    static const bit kCommonMatchingState = 0;
    static const bit kTriggerData = 9;
    static const bit kTriggerReady = 36;
    /*static const bit kGroup3MatchingState = 37;
    static const bit kGroup3L1Data = 43;
    static const bit kGroup3L1Empty = 78;
    static const bit kGroup3L1Ready = 79;
    static const bit kGroup2MatchingState = 80;
    static const bit kGroup2L1Data = 86;
    static const bit kGroup2L1Empty = 121;
    static const bit kGroup2L1Ready = 122;
    static const bit kGroup1MatchingState = 123;
    static const bit kGroup1L1Data = 129;
    static const bit kGroup1L1Empty = 164;
    static const bit kGroup1L1Ready = 165;*/
    static const bit kGroup0MatchingState = 166;
    static const bit kGroup0L1Data = 172;
    static const bit kGroup0L1Empty = 207;
    static const bit kGroup0L1Ready = 208;
    /*static const bit kGroup3HitData = 209;
    static const bit kGroup3HitChannel = 339;
    static const bit kGroup3HitSelectError = 342;
    static const bit kGroup3HitLoad = 343;
    static const bit kGroup2HitData = 344;
    static const bit kGroup2HitChannel = 474;
    static const bit kGroup2HitSelectError = 477;
    static const bit kGroup2HitLoad = 478;
    static const bit kGroup1HitData = 479;
    static const bit kGroup1HitChannel = 609;
    static const bit kGroup1HitSelectError = 612;
    static const bit kGroup1HitLoad = 613;*/
    static const bit kGroup0HitData = 614;
    static const bit kGroup0HitChannel = 744;
    static const bit kGroup0HitSelectError = 747;
    static const bit kGroup0HitLoad = 748;
  };
}

#endif
