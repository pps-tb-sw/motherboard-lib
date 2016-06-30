#ifndef BoardAddress_h
#define BoardAddress_h

#include <iostream>

namespace PPSTimingMB
{
  struct BoardAddress
  {
    inline BoardAddress(unsigned int mfec, unsigned int ccu, unsigned int i2c) :
      mfec(mfec), ccu(ccu), i2c(i2c) {;}
    inline void Dump(std::ostream& out=std::cout) const {
      out << " * MFEC = 0x" << std::hex << mfec << std::endl
          << " * CCU  = 0x" << std::hex << ccu << std::endl
          << " * I2C  = 0x" << std::hex << i2c << std::dec << std::endl;
    }
    unsigned int mfec;
    unsigned int ccu;
    unsigned int i2c;
  };
}

#endif
