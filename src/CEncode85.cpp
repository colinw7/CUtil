#include <CEncode85.h>
#include <cstring>

static const char
ascii85_chars[] =
  "!\"#$%&'()*+,-./0123456789:;<=>?@"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuz";

CEncode85 *
CEncode85::
getInstance()
{
  static CEncode85 *instance;

  if (! instance)
    instance = new CEncode85;

  return instance;
}

CEncode85::
CEncode85()
{
  setChars(ascii85_chars);
}

CEncode85::
~CEncode85()
{
}

void
CEncode85::
setChars(const char chars[86])
{
  memcpy(ascii85_chars_, chars, 85);

  ascii85_chars_[85] = '\0';
}

std::string
CEncode85::
encode(const std::string &str)
{
  std::string str1;

  auto len = str.size();

  uint num = uint(len/4);

  uint pos = 0;

  for (uint i = 0; i < num; ++i, pos += 4) {
    uint chars = (uint(str[pos + 0]) << 24U) | (uint(str[pos + 1]) << 16U) |
                 (uint(str[pos + 2]) <<  8U) |  uint(str[pos + 3]);

    std::string str2 = encodeInt(chars);

    //if (str2 == "z") str2 = "!!!!!";

    str1 += str2;
  }

  if (pos < len) {
    uint chars = 0;

    while (pos < len)
      chars = uint(chars << 8) | uint(str[pos++]);

    std::string str2 = encodeInt(chars);

    //if (str2 == "z") str2 = "!!!!!";

    str1 += str2;
  }

  return str1;
}

std::string
CEncode85::
encodeInt(uint chars)
{
  if (chars == 0) return "z";

  int c[5];

  for (uint i = 0; i < 5; i++) {
    uint temp = chars/85;

    c[i] = int(chars) - int(temp*85);

    chars = temp;
  }

  std::string str;

  for (uint i = 0; i < 5; i++)
    str += ascii85_chars_[c[4 - i]];

  return str;
}

std::string
CEncode85::
decode(const std::string &str)
{
  std::string str1;

  auto len = str.size();

  uint num = uint(len/5);

  for (uint i = 0, pos = 0; i < num; ++i, pos += 5) {
    int i1, i2, i3, i4, i5;

    decodeChar(str[i + 1], &i1);
    decodeChar(str[i + 2], &i2);
    decodeChar(str[i + 3], &i3);
    decodeChar(str[i + 4], &i4);
    decodeChar(str[i + 5], &i5);

    uint val = (((uint(i1)*85 + uint(i2))*85 + uint(i3))*85 + uint(i4))*85 + uint(i5);

    str1 += char((val & 0xFF000000) >> 24);
    str1 += char((val & 0x00FF0000) >> 16);
    str1 += char((val & 0x0000FF00) >>  8);
    str1 += char((val & 0x000000FF)      );
  }

  return str1;
}

bool
CEncode85::
decodeChar(char c, int *pos)
{
  const char *p = strchr(ascii85_chars, c);

  if (p == 0) return false;

  *pos = int(p - ascii85_chars);

  return true;
}
