#include "NINOThresholds.h"

namespace PPSTimingMB
{
  void
  NINOThresholds::SetValue(const BoardAddress& addr, unsigned int value)
  {
    fThresholds[addr] = value;
  }

  void
  NINOThresholds::Dump(std::ostream& out) const
  {
    out << "NINO Thresholds:" << std::endl;
    for (Register::const_iterator it=fThresholds.begin(); it!=fThresholds.end(); it++) {
      out << " * I2C address: " << it->first.i2c << " --> value: " << it->second << std::endl;
    }
  }
}
