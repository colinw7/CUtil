#ifndef CANGLE_TYPE_H
#define CANGLE_TYPE_H

enum CAngleType {
  CANGLE_TYPE_NONE,
  CANGLE_TYPE_DEGREES,
  CANGLE_TYPE_RADIANS
};

//---

#include <algorithm>
#include <cctype>
#include <string>

namespace CAngleTypeUtil {

inline std::string toString(CAngleType type) {
  if      (type == CANGLE_TYPE_DEGREES)
    return "degrees";
  else if (type == CANGLE_TYPE_RADIANS)
    return "radians";
  else
    return "??";
}

inline CAngleType fromString(const std::string &str) {
  std::string lstr = str;

  std::transform(lstr.begin(), lstr.end(), lstr.begin(),
    [](unsigned char c) { return std::tolower(c); }
  );

  if      (lstr == "degrees")
    return CANGLE_TYPE_DEGREES;
  else if (lstr == "radians")
    return CANGLE_TYPE_RADIANS;
  else
    return CANGLE_TYPE_NONE;
}

}

#endif
