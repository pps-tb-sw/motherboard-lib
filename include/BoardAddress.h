#ifndef BoardAddress_h
#define BoardAddress_h

#include <iostream>

namespace PPSTimingMB
{
  /**
   * \brief Content holder for a motherboard address
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date 30 Jun 2016
   */
  struct BoardAddress
  {
    /// Construct an object from the full address content
    inline BoardAddress(unsigned int mfec, unsigned int ccu, unsigned int i2c) :
      mfec(mfec), ccu(ccu), i2c(i2c) {;}

    /// Dump the full address into the output stream
    inline void Dump(std::ostream& out=std::cout) const {
      out << " * MFEC = 0x" << std::hex << mfec << std::endl
          << " * CCU  = 0x" << std::hex << ccu << std::endl
          << " * I2C  = 0x" << std::hex << i2c << std::dec << std::endl;
    }
    /// FEC identifier
    unsigned int mfec;
    /// CCU ring identifier
    unsigned int ccu;
    /// I2C address
    unsigned int i2c;
  };
  /// Comparison operator
  inline bool operator<(const BoardAddress& a, const BoardAddress& b) {
    if (a.mfec<b.mfec) return true;
    else if (a.ccu<b.ccu) return true;
    else if (a.i2c<b.i2c) return true;
    return false;
  }
  inline std::ostream& operator<<(std::ostream& os, const BoardAddress& add) {
    os << std::hex
       << "MFEC=0x" << add.mfec
       << ", CCU=0x" << add.ccu
       << ", I2C=0x" << add.i2c
       << std::dec;
    return os;
  }

}

#endif
