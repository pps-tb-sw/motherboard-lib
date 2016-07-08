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
  class NINOThresholds
  {
   public:
    typedef std::map<BoardAddress, unsigned int> Register;

    /// Construct the object out of the four threshold values
    inline NINOThresholds() {;}
    /// Retrieve the number of threshold values held in this container
    inline size_t NumThresholds() const { return fThresholds.size(); }

    /// Set the NINO threshold value associated to an addressed module
    void SetValue(const BoardAddress&, unsigned int);
    /// Retrieve the NINO threshold value associated to an addressed module
    inline unsigned int GetValue(const BoardAddress& addr) const {
      Register::const_iterator it = fThresholds.find(addr);
      if (it!=fThresholds.end()) return it->second;
      return 0;
    }
    inline Register GetValues() const { return fThresholds; }
    /// Dump the threshold for all 4 groups into the output stream
    void Dump(std::ostream& os=std::cout) const;

   private:
    /// NINO threshold for channels 0-7
    Register fThresholds;
  };
}

#endif
