#ifndef NINOThresholds_h
#define NINOThresholds_h

#include <iostream>

namespace PPSTimingMB
{
  /**
   * \brief Thresholds for all 8-channel NINO boards on a PPS motherboard
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date 30 Jun 2016
   */
  struct NINOThresholds
  {
    /// Construct the object out of the four threshold values
    NINOThresholds(unsigned int,unsigned int,unsigned int,unsigned int);
    /// Dump the threshold for all 4 groups into the output stream
    void Dump(std::ostream& os=std::cout);

    /// NINO threshold for channels 0-7
    unsigned int group0;
    /// NINO threshold for channels 8-15
    unsigned int group1;
    /// NINO threshold for channels 16-23
    unsigned int group2;
    /// NINO threshold for channels 24-31
    unsigned int group3;
  };
}

#endif
