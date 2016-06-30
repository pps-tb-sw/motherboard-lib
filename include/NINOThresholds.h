#ifndef NINOThresholds_h
#define NINOThresholds_h

#include <iostream>

namespace PPSTimingMB
{
  struct NINOThresholds
  {
    NINOThresholds(unsigned int,unsigned int,unsigned int,unsigned int);
    void Dump(std::ostream& os=std::cout);

    unsigned int group0;
    unsigned int group1;
    unsigned int group2;
    unsigned int group3;
  };
}

#endif
