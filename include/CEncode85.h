#ifndef CENCODE_85_H
#define CENCODE_85_H

#include <string>
#include <sys/types.h>

class CFile;

#define CEncode85Inst CEncode85::getInstance()

class CEncode85 {
 public:
  static CEncode85 *getInstance();

  void setChars(const char base_85_chars[85]);

  std::string encode(const std::string &str);

  std::string decode(const std::string &str);

 private:
  CEncode85();
 ~CEncode85();

  std::string encodeInt(uint chars);

  bool decodeChar(char c, int *pos);

 private:
  char ascii85_chars_[86];
//char end_char_ { '\0' };
};

#endif
