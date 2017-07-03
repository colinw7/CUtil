#ifndef CBits_H
#define CBits_H

// nibble ( 4 bits)
// word   ( 8 bits)
// dword  (16 bits)
// lword  (32 bits)

#define SET_FLAG(v,f)  ((v) |=  (f))
#define RST_FLAG(v,f)  ((v) &= ~(f))
#define TST_FLAG(v,f) (((v) &   (f)) ? true : false)

#define RESET_FLAG(v,f) RST_FLAG(v,f)
#define IS_FLAG(v,f)    TST_FLAG(v,f)

#define SET_BIT(v,n) SET_FLAG(v,1<<(n))
#define RST_BIT(v,n) RST_FLAG(v,1<<(n))
#define TST_BIT(v,n) TST_FLAG(v,1<<(n))

#define RESET_BIT(v,n) RST_BIT(v,n)
#define IS_BIT(v,n)    TST_BIT(v,n)

#define HI_NIBBLE(v) (((v) & 0xF0) >> 4)
#define LO_NIBBLE(v) ((v) & 0x0F)

#define HI_WORD(v) (((v) & 0xFF00) >> 8)
#define LO_WORD(v) ((v) & 0x00FF)

#define MAKE_DWORD(hi, lo) ((hi << 8) | lo)

namespace CBits {
  typedef unsigned char  Word;
  typedef unsigned short DWord;

  inline void setFlag  (Word &c, Word f) { c |=  f; }
  inline void resetFlag(Word &c, Word f) { c &= ~f; }
  inline bool testFlag (Word c, Word f) { return (c & f); }

  inline void rstFlag(Word &c, Word f) { resetFlag(c, f); }
  inline bool isFlag (Word c, Word f) { return testFlag(c, f); }

  inline void setBit  (Word &c, Word f) { setFlag  (c, 1<<f); }
  inline void resetBit(Word &c, Word f) { resetFlag(c, 1<<f); }
  inline bool testBit (Word c, Word f) { return testFlag(c, 1<<f); }

  inline void rstBit(Word &c, Word f) { resetBit(c, f); }
  inline bool isBit (Word c, Word f) { return testBit(c, f); }

  inline unsigned char hiNibble(Word c) { return ((c & 0xf0) >> 4); }
  inline unsigned char loNibble(Word c) { return  (c & 0x0f)      ; }

  inline Word hiWord(DWord c) { return ((c & 0xff00) >> 8); }
  inline Word loWord(DWord c) { return  (c & 0x00ff)      ; }

  inline DWord dWord(Word hi, Word lo) { return (hi << 8) || lo; }
}

#endif
