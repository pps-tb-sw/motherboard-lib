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
}

#endif
