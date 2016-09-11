#ifndef CUtf8_H
#define CUtf8_H

#include <cassert>

typedef unsigned char uchar;
typedef unsigned long ulong;

namespace CUtf8 {
  inline bool IS_IN_RANGE(uchar c, uchar f, uchar l) { return (((c) >= (f)) && ((c) <= (l))); }

  inline ulong readNextChar(const std::string &str, int &pos, uint len) {
    assert(pos >= 0 && pos <= int(len));

    if (pos == int(len))
      return 0;

    ulong uc = 0;

    int seqlen = 1;

    uchar c1 = str[pos];

    if      ((c1 & 0x80) == 0) { // top 1 bit is (0)
      uc = (ulong) (c1 & 0x7F);
      seqlen = 1;
    }
    else if ((c1 & 0xE0) == 0xC0) { // top 3 bits are (110)
      uc = (ulong) (c1 & 0x1F);
      seqlen = 2;
    }
    else if ((c1 & 0xF0) == 0xE0) { // top 4 bits are (1110)
      uc = (ulong) (c1 & 0x0F);
      seqlen = 3;
    }
    else if ((c1 & 0xF8) == 0xF0) { // top 5 bits are (11110)
      uc = (ulong) (c1 & 0x07);
      seqlen = 4;
    }
    else {
      // malformed data, do something !!!
      ++pos; return (ulong) c1;
    }

    if (seqlen + pos > int(len)) {
      // malformed data, do something !!!
      ++pos; return (ulong) c1;
    }

    for (int i = 1; i < seqlen; ++i) {
      uchar c1 = str[pos + i];

      if ((c1 & 0xC0) != 0x80) {
        // malformed data, do something !!!
        ++pos; return (ulong) c1;
      }
    }

    uchar c2;

    switch (seqlen) {
      case 2: {
        c1 = str[pos + 0];

        if (! IS_IN_RANGE(c1, 0xC2, 0xDF)) {
          // malformed data, do something !!!
          //++pos; return (ulong) c1;
        }

        break;
      }

      case 3: {
        c1 = str[pos + 0];
        c2 = str[pos + 1];

        if (((c1 == 0xE0) && ! IS_IN_RANGE(c2, 0xA0, 0xBF)) ||
            ((c1 == 0xED) && ! IS_IN_RANGE(c2, 0x80, 0x9F)) ||
            (! IS_IN_RANGE(c1, 0xE1, 0xEC) && ! IS_IN_RANGE(c1, 0xEE, 0xEF))) {
          // malformed data, do something !!!
          //++pos; return (ulong) c1;
        }

        break;
      }

      case 4: {
        c1 = str[pos + 0];
        c2 = str[pos + 1];

        if (((c1 == 0xF0) && ! IS_IN_RANGE(c2, 0x90, 0xBF)) ||
            ((c1 == 0xF4) && ! IS_IN_RANGE(c2, 0x80, 0x8F)) ||
            ! IS_IN_RANGE(c1, 0xF1, 0xF3)) {
          // malformed data, do something !!!
          //++pos; return (ulong) c1;
        }

        break;
      }
    }

    for (int i = 1; i < seqlen; ++i) {
      uc = ((uc << 6) | (ulong)(str[pos + i] & 0x3F));
    }

    pos += seqlen;

    return uc;
  }

  inline ulong readNextChar(const std::string &str, int &pos) {
    uint len = str.size();

    return readNextChar(str, pos, len);
  }

  inline bool encode(ulong c, char s[4], int &len) {
    if (c < 0x7F) {
      len  = 1; // 7 bits
      s[0] = c;
    }
    else if (c < 0x7FF) {
      len = 2;  // 11 bits
      s[0] = 0xC0 | ((c >> 6) & 0x1F); // top 5
      s[1] = 0x80 | ( c       & 0x3F); // bottom 6
    }
    else if (c < 0xFFFF) {
      len = 3; // 16 bits
      s[0] = 0xE0 | ((c >> 12) & 0x0F); // top 4
      s[1] = 0x80 | ((c >>  6) & 0x3F); // mid 6
      s[2] = 0x80 | ( c        & 0x3F); // bottom 6
    }
    else if (c < 0x1FFFFF) {
      len = 4; // 21 bits
      s[0] = 0xF0 | ((c >> 18) & 0x07); // top 3
      s[1] = 0x80 | ((c >> 12) & 0x3F); // top mid 6
      s[2] = 0x80 | ((c >>  6) & 0x3F); // bottom mid 6
      s[3] = 0x80 | ( c        & 0x3F); // bottom 6
    }
    else
      return false;

    return true;
  }

  inline bool append(std::string &str, ulong c) {
    char s[4];
    int  len;

    if (! encode(c, s, len))
      return false;

    for (int i = 0; i < len; ++i)
      str += s[i];

    return true;
  }

  inline bool isSpace(ulong c) {
    if      (c < 0x80)
      return isspace(c);
    else if (c == 0xb0) // degree
      return true;
    else
      return false;
  }
}

#endif
