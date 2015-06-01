#ifndef CUtf8_H
#define CUtf8_H

typedef unsigned char uchar;

namespace CUtf8 {
  bool IS_IN_RANGE(uchar c, uchar f, uchar l) { return (((c) >= (f)) && ((c) <= (l))); }

  ulong readNextChar(const std::string &str, int &pos) {
    uint len = str.size();
    assert(pos >= 0 && pos < int(len));

    ulong uc = 0;

    int seqlen = 1;

    uchar c1 = str[pos];

    if      ((c1 & 0x80) == 0) {
      uc = (ulong) (c1 & 0x7F);
      seqlen = 1;
    }
    else if ((c1 & 0xE0) == 0xC0) {
      uc = (ulong) (c1 & 0x1F);
      seqlen = 2;
    }
    else if ((c1 & 0xF0) == 0xE0) {
      uc = (ulong) (c1 & 0x0F);
      seqlen = 3;
    }
    else if ((c1 & 0xF8) == 0xF0) {
      uc = (ulong) (c1 & 0x07);
      seqlen = 4;
    }
    else {
      // malformed data, do something !!!
      ++pos; return (ulong) c1;
    }

    if (seqlen + pos >= int(len)) {
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
          ++pos; return (ulong) c1;
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
          ++pos; return (ulong) c1;
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
          ++pos; return (ulong) c1;
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
}

#endif
