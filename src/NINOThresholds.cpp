#include "NINOThresholds.h"

namespace PPSTimingMB
{
  NINOThresholds::NINOThresholds(unsigned int g0, unsigned int g1, unsigned int g2, unsigned int g3) :
      group0(g0), group1(g1), group2(g2), group3(g3)
  {}

  void
  NINOThresholds::Dump(std::ostream& out)
  {
    out << "NINO Thresholds:" << std::endl
        << " * group 0 (ch.  0- 7): " << group0 << std::endl
        << " * group 1 (ch.  8-15): " << group1 << std::endl
        << " * group 2 (ch. 16-23): " << group2 << std::endl
        << " * group 3 (ch. 24-31): " << group3 << std::endl;
  }
}
