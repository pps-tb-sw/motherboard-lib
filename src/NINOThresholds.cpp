#include "NINOThresholds.h"

namespace PPSTimingMB
{
  void
  NINOThresholds::SetValue(const BoardAddress& addr, unsigned int value)
  {
    thresholds[addr] = value;
  }

  void
  NINOThresholds::Dump(std::ostream& out) const
  {
    out << "NINO Thresholds:" << std::endl;
    for (Register::const_iterator it=thresholds.begin(); it!=thresholds.end(); it++) {
      out << " * I2C address: " << it->first.i2c << " --> value: " << it->second << std::endl;
    }
  }
}
