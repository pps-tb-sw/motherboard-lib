#ifndef TDCRegister_h
#define TDCRegister_h

#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h> // ceil
#include <stdint.h>

#define WORD_SIZE 8

#include "TDCConstants.h"

namespace PPSTimingMB
{
  /**
   * \brief General register object to interact with a HPTDC chip
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date 24 Apr 2015
   *
   * \ingroup HPTDC
   */
  class TDCRegister
  {
    public:
      /// LSB index
      typedef uint16_t bit;
      /// Unit of the TDC register word to be successfully contained on any machine
      typedef uint32_t word_t;

    public:
      /// Initialise an empty register
      inline TDCRegister(const unsigned int size) :
        fNumWords(ceil(size/WORD_SIZE)+1), fWordSize(size) {
        if (size%WORD_SIZE==0) fNumWords = size/WORD_SIZE;
        fWord = new word_t[fNumWords];
        Clear();
      }
      /// Initialise and fill a register
      inline TDCRegister(const unsigned int size, const TDCRegister& r) :
        fNumWords(ceil(size/WORD_SIZE)+1), fWordSize(size) {
        if (size%WORD_SIZE==0) fNumWords = size/WORD_SIZE;
        fWord = new word_t[fNumWords];
        for (unsigned int i=0; i<GetNumWords(); i++) { fWord[i] = r.fWord[i]; }
      }
      /// Initialise and fill a register
      inline TDCRegister(const unsigned int size, const std::vector<uint8_t>& words, bool reversed=false) :
        fNumWords(ceil(size/WORD_SIZE)+1), fWordSize(size) {
        if (size%WORD_SIZE==0) fNumWords = size/WORD_SIZE;
        fWord = new word_t[fNumWords];
        if (reversed) { for (unsigned int i=0; i<fNumWords; i++) { SetWord(i, words[fNumWords-1-i]); } }
        else { for (unsigned int i=0; i<fNumWords; i++) { SetWord(i, words[i]); } }
      }
      /// Destroy the register and its content
      inline virtual ~TDCRegister() {
        if (fWord) delete [] fWord;
      }
      /// Assign values from another register to this one
      inline TDCRegister& operator=(const TDCRegister& r) {
        if (&r!=this) {
          fWordSize = r.fWordSize;
          fNumWords = r.fNumWords;
          word_t* newWord = fNumWords ? new word_t[fNumWords] : 0;
          std::copy(r.fWord, r.fWord+fNumWords, newWord);
          // replace the old data (all are non-throwing)
          delete [] fWord;
          fWord = newWord;
        }
        return *this;
      }
      
      /// Set one bit(s) subset in the register word
      inline void SetWord(const unsigned int i, const word_t word) {
        if (i<0 or i>=fNumWords) return;
        fWord[i] = word;
      }
      /// Retrieve one subset from the register word
      inline word_t GetWord(const unsigned int i) const {
        if (i<0 or i>=fNumWords) return -1;
        return fWord[i];
      }
      /// Retrieve the whole array of sub-words composing this register
      inline word_t* GetWords() const { return fWord; }
      /// Retrieve a vector of 8-bit words composing this register
      inline std::vector<uint8_t> GetBytesVector() const { //FIXME more complicated if != 8-bit words!
        return std::vector<uint8_t>(fWord, fWord+fNumWords);
      }
      /**
       * Return the number of words making up the full register word.
       * \brief Number of words in the register
       */
      inline uint8_t GetNumWords() const { return fNumWords; }

      /// Printout all useful information handled by the register
      void DumpRegister(unsigned short verb=1, std::ostream& os=std::cout, const bit max_bits=-1) const;
      /// Ensure that the critical constant values are properly set in the register word
      inline void SetConstantValues() {;}
      /// Return a given value as a 32-bit word
      template<class T> inline uint32_t GetValue(const T&) { return 0; }

      /// Compute the parity bit of the full register word
      inline bool ComputeParityBit(unsigned short begin=0, short end=-1) const {
        if (end<0) end = fWordSize;
        unsigned short parity = 0;
        for (unsigned short i=begin; i<end; i++) { parity += GetBits(i, 1); }
        return (parity%2!=0);
      }
    protected:
      /**
       * Set a fixed amount of bits in the full register word
       * \brief Set bits in the register word
       * \param[in] lsb Least significant bit of the word to set
       * \param[in] word Word to set
       * \param[in] size Size of the word to set
       */
      void SetBits(uint16_t lsb, uint16_t word, uint8_t size);
      /**
       * Extract a fixed amount of bits from the full register word
       * \brief Extract bits from the register word
       * \param[in] lsb Least significant bit of the word to retrieve
       * \param[in] size Size of the word to retrieve
       */
      uint16_t GetBits(uint16_t lsb, uint8_t size) const;
      /// Set all bits in this register to '0'
      inline void Clear() {
        for (uint8_t i=0; i<fNumWords; i++) { fWord[i] = 0; }
      }

      /*inline bool ComputeParityBit(unsigned short begin=0, unsigned short end=-1) const {
        if (end<0) end = fWordSize;
        bool parity = false;
        for (uint8_t i=begin; i<end; i++) { parity += GetBits(i, 1); }
        return (parity%2);
      }*/

      /// Pointer to this register's word
      word_t* fWord;
      /// Number of words to fit the \a fWordSize bits of this register to this object
      unsigned int fNumWords;
      /// Number of bits in this register
      unsigned int fWordSize;
  };
}

#endif
