#ifndef CAUTO_FREE
#define CAUTO_FREE

template<class T>
class CAutoFree {
 public:
  CAutoFree(T *p=nullptr) : p_(p) { }

 ~CAutoFree() { free(p_); }

  T *operator->() const {
    return p_;
  }

  operator T*() const {
    return p_;
  }

  T &operator*() const {
    return *p_;
  }

  T **operator&() const {
    return &p_;
  }

  CAutoFree &operator=(const CAutoFree &p) {
    set(p);

    return *this;
  }

  CAutoFree &operator=(T *p) {
    set(p);

    return *this;
  }

  bool operator==(T const *p) const {
    return p_ == p;
  }

  bool operator!=(T const *p) const {
    return p_ != p;
  }

  T *get() {
    return p_;
  }

  void set(const CAutoFree &p) {
    set(p.p_);
  }

  void set(T *p) {
    p_ = p;
  }

 private:
  T *p_ { nullptr };
};

//---

#include <netdb.h>

class CAutoFreeAddrInfo {
 private:
  typedef struct addrinfo T;

 public:
  CAutoFreeAddrInfo(T *p=nullptr) : p_(p) { }

 ~CAutoFreeAddrInfo() {
    extern void freeaddrinfo(T *p);

    if (p_)
      freeaddrinfo(p_);
  }

  T *operator->() const {
    return p_;
  }

  operator T*() const {
    return p_;
  }

  T &operator*() const {
    return *p_;
  }

  T **operator&() {
    return &p_;
  }

  CAutoFreeAddrInfo &operator=(const CAutoFreeAddrInfo &p) {
    set(p);

    return *this;
  }

  CAutoFreeAddrInfo &operator=(T *p) {
    set(p);

    return *this;
  }

  bool operator==(T const *p) const {
    return p_ == p;
  }

  bool operator!=(T const *p) const {
    return p_ != p;
  }

  T *get() {
    return p_;
  }

  void set(const CAutoFreeAddrInfo &p) {
    set(p.p_);
  }

  void set(T *p) {
    p_ = p;
  }

 private:
  T *p_ { nullptr };
};

#endif
