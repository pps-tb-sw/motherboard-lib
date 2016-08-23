#ifndef TDCStatus_h
#define TDCStatus_h

#include "TDCRegister.h"

namespace PPSTimingMB
{
  /**
   *
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \author Lara Lloret Iglesias <lara@cern.ch>
   * \date 27 Apr 2015
   * \date May 2016
   * \ingroup HPTDC
   */
  class TDCStatus : public TDCRegister
  {
    public:
      /// Initialise a status register with all hardcoded values
      inline TDCStatus() : TDCRegister(TDC_STATUS_BITS_NUM) { SetConstantValues(); }
      /// Initialise a status register from a vector of 8-bit words
      inline TDCStatus(const std::vector<uint8_t>& words) : TDCRegister(TDC_STATUS_BITS_NUM, words) {;}

      /// Set the hardcoded values to the register
      void SetConstantValues();

      /// Type of error encountered by the HPTDC
      typedef struct ErrorType {
        ErrorType(uint16_t word) {
          Vernier              =  word     &0x1;
          Coarse               = (word>> 1)&0x1;
          ChannelSelect        = (word>> 2)&0x1;
          L1BufferParity       = (word>> 3)&0x1;
          TriggerFIFOParity    = (word>> 4)&0x1;
          TriggerMatchingState = (word>> 5)&0x1;
          ReadoutFIFOParity    = (word>> 6)&0x1;
          ReadoutState         = (word>> 7)&0x1;
          SetupParity          = (word>> 8)&0x1;
          ControlParity        = (word>> 9)&0x1;
          JTAGInstruction      = (word>>10)&0x1;
        }
        /// Error related on the parity of any register/buffer
        bool ParityError() const { return (L1BufferParity or TriggerFIFOParity or ReadoutFIFOParity or SetupParity or ControlParity); }
        /// Error related to the Vernier or Coarse measurement
        bool MeasurementError() const { return (Vernier or Coarse); }
        /// Has any error occured?
        bool GlobalError() const { return (MeasurementError() or ChannelSelect or ParityError() or JTAGInstruction); }

        bool Vernier, Coarse, ChannelSelect;
        bool L1BufferParity;
        bool TriggerFIFOParity, TriggerMatchingState;
        bool ReadoutFIFOParity, ReadoutState;
        bool SetupParity, ControlParity, JTAGInstruction;
      } ErrorType;
      /// Printout the error type(s) into the output stream
      friend std::ostream& operator<<(std::ostream& out, const ErrorType& err);

      /// Retrieve the list of errors monitored
      inline ErrorType Error() const {
        return ErrorType(static_cast<uint16_t>(GetBits(kError, 11)));
      }
      /// TDC have read-out token
      inline bool HasToken() const { return static_cast<bool>(GetBits(kHaveToken, 1)); }
      /// Occupancy of readout FIFO
      inline uint16_t FIFOOccupancy() const { return static_cast<uint16_t>(GetBits(kReadoutFIFOOccupancy, 8)); }
      /// It the readout FIFO full?
      inline bool FIFOFull() const { return static_cast<bool>(GetBits(kReadoutFIFOFull, 1)); }
      /// It the readout FIFO empty?
      inline bool FIFOEmpty() const { return static_cast<bool>(GetBits(kReadoutFIFOEmpty, 1)); }
      /// Occupancy of L1 buffer in channels of a group (or all groups)
      inline uint32_t L1Occupancy(unsigned short group=-1) const {
        uint32_t out = static_cast<uint32_t>(GetBits(kL1Occupancy, 32));
        if (group<0 or group>3) return out; // whole 32-bit word combining all groups
        return static_cast<uint32_t>((out>>group)&0xff); // only 8 bits of selected group
      }
      /// Occupancy of trigger FIFO
      inline uint16_t TriggerFIFOOccupancy() const { return static_cast<uint16_t>(GetBits(kTriggerFIFOOccupancy, 4)); }
      /// Is the trigger FIFO full?
      inline bool TriggerFIFOFull() const { return static_cast<bool>(GetBits(kTriggerFIFOFull, 1)); }
      /// Is the trigger FIFO empty?
      inline bool TriggerFIFOEmpty() const { return static_cast<bool>(GetBits(kTriggerFIFOEmpty, 1)); }
      /// Is the DLL in lock state?
      inline bool DLLLock() const { return static_cast<bool>(GetBits(kDLLLock, 1)); }
      /// Check if the SETUP sequence is correct
      inline bool InvertedSetup() const { return static_cast<bool>(GetBits(kInvertedSetup, 1)); }

      /// Printout all useful values of this status register into an output stream
      void Dump(int verb=1, std::ostream& os=std::cout) const;

    private:
      static const bit kError = 0;
      static const bit kHaveToken = 11;
      static const bit kReadoutFIFOOccupancy = 12;
      static const bit kReadoutFIFOFull = 20;
      static const bit kReadoutFIFOEmpty = 21;
      static const bit kL1Occupancy = 22;
      static const bit kTriggerFIFOOccupancy = 54;
      static const bit kTriggerFIFOFull = 58;
      static const bit kTriggerFIFOEmpty = 59;
      static const bit kDLLLock = 60;
      static const bit kInvertedSetup = 61;
  };
}

#endif
