#ifndef CSafeIndex_H
#define CSafeIndex_H

#include <CSafeCast.h>

#include <vector>
#include <cassert>

namespace CUtil {

template<typename T, typename INT=int>
const T &safeIndex(const std::vector<T> &v, INT i) {
  assert(i >= 0 && i < INT(v.size())); return v[size_t(i)];
}

template<typename T, typename INT=int>
T &safeIndex(std::vector<T> &v, INT i) {
  assert(i >= 0 && i < INT(v.size())); return v[size_t(i)];
}

template<typename T, typename INT=int>
T safeIndex(const std::vector<T> &v, INT i, const T &def) {
  if (i < 0 || i >= INT(v.size())) return def;
  return v[size_t(i)];
}

}

#endif
