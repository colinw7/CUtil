#ifndef CSafeIndex_H
#define CSafeIndex_H

#include <vector>
#include <cassert>

namespace CUtil {

template<typename T>
const T &safeIndex(const std::vector<T> &v, int i) {
  assert(i >= 0 && i < int(v.size())); return v[size_t(i)];
}

template<typename T>
T &safeIndex(std::vector<T> &v, int i) {
  assert(i >= 0 && i < int(v.size())); return v[size_t(i)];
}

}

#endif
