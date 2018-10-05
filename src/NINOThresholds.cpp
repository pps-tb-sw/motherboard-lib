#include "NINOThresholds.h"

namespace PPSTimingMB
{
  void
  NINOThresholds::SetValue(unsigned short group, unsigned int value)
  {
    fThresholds[group] = value;
  }

  void
  NINOThresholds::Dump(std::ostream& out) const
  {
    out << "NINO Thresholds:" << std::endl;
    for (Register::const_iterator it=fThresholds.begin(); it!=fThresholds.end(); it++) {
      out << " * group: " << it->first << " --> value: " << it->second << std::endl;
    }
  }
}
