#ifndef CUTIL_H
#define CUTIL_H

//#include <CAngleType.h>

#include <algorithm>
#include <string>
#include <iostream>

class CUtil {
 public:
  static void setOStream(std::ostream &os) { os_ = &os; }

  //static std::string toString   (CAngleType angle_type);
  //static CAngleType  toAngleType(const std::string &str);

  // dummy proc for debugging stop
  static void breakpoint();

  // decode position of first but set in mask
  static void decodeMask(uint full_mask, uint *shift, uint *mask);
  static void decodeMask(ushort full_mask, ushort *shift, ushort *mask);

  template<typename Collection>
  static bool contains(Collection &&collection,
                       typename std::remove_reference<Collection>::type::value_type const &value) {
    return std::find(std::begin(collection), std::end(collection), value) != std::end(collection);
  }

  // print string
  static void printString(const std::string &str);

 private:
  static std::ostream *os_;
};

#endif
