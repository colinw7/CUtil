#ifndef CINST_COUNT_H
#define CINST_COUNT_H

#include <sys/types.h>

#include <iostream>

#define CINST_COUNT_MEMBER(T) \
 public: \
  static const char *getCInstCountClassName() { return #T; } \
 private: \
  CInstCount<T> inst_count_

template<class T>
class CInstCountMgr {
 private:
  uint count_;

 public:
  CInstCountMgr() : count_(0) { }

 ~CInstCountMgr() {
    if (count_ > 0)
      std::cerr << count_ << " unfreed instance(s) of " <<
                   T::getCInstCountClassName() << std::endl;
  }

  uint createInstance() { return ++count_; }
  void deleteInstance() { --count_; }
};

template<class T>
class CInstCount {
 private:
  uint id_;

 public:
  CInstCount() {
    id_ = getMgr().createInstance();
  }

 ~CInstCount() {
    getMgr().deleteInstance();
  }

 private:
  static CInstCountMgr<T> &getMgr() {
    static CInstCountMgr<T> mgr;

    return mgr;
  }
};

#endif
