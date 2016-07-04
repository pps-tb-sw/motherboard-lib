#ifndef NINOThresholds_h
#define NINOThresholds_h

#include "BoardAddress.h"
#include <iostream>
#include <map>

namespace PPSTimingMB
{
  /**
   * \brief Thresholds for all 8-channel NINO boards on a PPS motherboard
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date 30 Jun 2016
   */
  struct NINOThresholds
  {
    typedef std::map<BoardAddress, unsigned int> Register;

    /// Construct the object out of the four threshold values
    inline NINOThresholds() {;}
    //
    void SetValue(const BoardAddress&, unsigned int);
    /// Dump the threshold for all 4 groups into the output stream
    void Dump(std::ostream& os=std::cout) const;

    /// NINO threshold for channels 0-7
    Register thresholds;
  };
}

#endif
