#ifndef CSafeCast_H
#define CSafeCast_H

#include <limits>
#include <cassert>
#include <cstddef>

namespace CUtil {

inline size_t toSizeT(int i) {
  assert(i >= 0); return size_t(i);
}

inline double toDouble(int i) {
  return double(i);
}

inline int toInt(size_t i) {
  assert(i < std::numeric_limits<int>::max()); return int(i);
}

}

#endif
