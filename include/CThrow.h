#ifndef CThrow_H
#define CThrow_H

#include <iostream>

#define CTHROW_THROW 1
#define CTHROW_SEGV  2
#define CTHROW_PRINT 3
#define CTHROW_EXIT  4

#define CTHROW(m) { \
std::cerr << __FILE__ << ":" << __LINE__ << ":" << m << std::endl; \
}

#define CITHROW(i) CThrow::doThrow(i)

using std::cerr;

namespace CThrow {
  inline void doThrow(int id) {
    std::cerr << "throw:" << id << std::endl;
  }
}

#endif
