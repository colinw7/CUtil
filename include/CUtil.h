#ifndef CUTIL_H
#define CUTIL_H

#include <CAngleType.h>
#include <string>

class CUtil {
 public:
  static std::string toString   (CAngleType angle_type);
  static CAngleType  toAngleType(const std::string &str);

  static void breakpoint();

  static void decodeMask(uint full_mask, uint *shift, uint *mask);
  static void decodeMask(ushort full_mask, ushort *shift, ushort *mask);
};

#endif
