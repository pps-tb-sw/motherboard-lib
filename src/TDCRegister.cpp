#include "TDCRegister.h"
 
void
TDCRegister::DumpRegister(unsigned short verb, std::ostream& os, const bit max_bits) const
{
  switch (verb) {
  case 1: case 2: default:
    {
      const unsigned short spacing = 5;
      for (unsigned int i=0; i<fNumWords; i++) {
        if (i%spacing==0) {
          if (i!=0) os << " << Word " << std::setfill(' ') << std::setw(2) << std::dec << i-1;
          os << std::endl << "  Word " << std::setw(2) << std::dec << i << " >> |";
        }
        os << " 0x" << std::hex << std::setw(3) << std::setfill('0') << fWord[i] << " |";
      }
      os << std::setfill(' ') << std::dec << std::endl;
    }
    break;
  case 3:
    {
      os << std::endl;
      for (unsigned int i=0; i<fNumWords; i++) {
        os << " Word " << std::setw(2) << i << ":  "
           << std::setw(3) << std::dec << (i+1)*WORD_SIZE-1 << "-> |";
        for(int8_t j=WORD_SIZE-1; j>=0; j--) {
          uint16_t bit = j+i*WORD_SIZE;
          // bits values
          if (bit>fWordSize or (max_bits>0 and bit>=max_bits)) os << "x";
          else os << static_cast<bool>((fWord[i] & static_cast<word_t>(1<<j))>>j);
          // delimiters
          if (j%16==0 && j!=0) os << "| |";
          else if (j%8==0) os << "|";
          else if (j%4==0) os << " ";
        }
        os << " <-" << std::setw(3) << i*WORD_SIZE 
           << " -=- 0x" << std::hex << std::setw(4) << std::setfill('0') << fWord[i] << std::dec << std::endl;
      }
    }
    break;
  }
  os << std::endl;
}
  
void
TDCRegister::SetBits(uint16_t lsb, uint16_t word, uint8_t size)
{
  if (size<=0 or size>16) return;
  //FIXME FIXME FIXME burp...
  // See http://www.ioccc.org/ for more information
  for (uint8_t i=0; i<size; i++) {
    uint16_t bit = lsb+i;
    uint8_t bit_rel = bit % WORD_SIZE;
    uint8_t word_id = (bit-bit_rel)/WORD_SIZE;
    fWord[word_id] &=~(1<<bit_rel); // first we clear the bit
    fWord[word_id] |= (((word>>i)&0x1)<<bit_rel); // then we set it
  }
}

uint16_t
TDCRegister::GetBits(uint16_t lsb, uint8_t size) const
{
  if (size<=0 or size>16) return -1;
  uint16_t out = 0x0;
  for (uint8_t i=0; i<size; i++) {
    uint16_t bit = lsb+i;
    uint8_t bit_rel = bit % WORD_SIZE;
    uint8_t word_id = (bit-bit_rel)/WORD_SIZE;
    out |= (((fWord[word_id]>>bit_rel)&0x1)<<i);
  }
  return out;
}
