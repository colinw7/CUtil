#ifndef CREF_PTR_H
#define CREF_PTR_H

#include <cassert>
#include <iostream>

// Reference Counted Pointer Class:
//  Stores a pointer to an object of type T and a pointer to an integer counter
//  which is shared between all referenced counted pointers which point to the
//  same object.
//
// Usage:
//  Create:
//   CRefPtr<T> p(new T);
//  Copy
//   CRefPtr<T> p1 = p;
//   CRefPtr<T> p1(p);
//  Delete
//   p = 0;
//
// Beware!!!. Never return or use this from inside a reference pointer class
// or you will get a double free.
//
// Pass using normal value semantics e.g.
//  void proc(CRefPtr<T> value, CRefPtr<T> &ref_value, CRefPtr<T> &const_value) {
//    ...
//  }

template<typename T>
class CRefPtr {
 public:
  typedef T  element_type;
  typedef T  value_type;
  typedef T* pointer;
  typedef T& reference; // TODO: use type traits

 protected:
  template<typename S>
  friend class CRefPtr;

  typedef int Count;

 public:
  static int valueCmp(const CRefPtr &lhs, const CRefPtr &rhs) {
    if (! lhs.p_ || ! rhs.p_) {
      if (lhs.p_ == rhs.p_) return 0;

      return (lhs.p_ < rhs.p_ ? -1 : 1);
    }
    else {
      if (*lhs == *rhs) return 0;

      return (*lhs.p_ < *rhs.p_ ? -1 : 1);
    }
  }

  static bool valueLess(const CRefPtr &lhs, const CRefPtr &rhs) {
    return valueCmp(lhs, rhs) < 0;
  }

  static bool valueGreater(const CRefPtr &lhs, const CRefPtr &rhs) {
    return valueCmp(lhs, rhs) > 0;
  }

  static bool valueLessEqual(const CRefPtr &lhs, const CRefPtr &rhs) {
    return valueCmp(lhs, rhs) <= 0;
  }

  static bool valueGreaterEqual(const CRefPtr &lhs, const CRefPtr &rhs) {
    return valueCmp(lhs, rhs) >= 0;
  }

  static bool valueEqual(const CRefPtr &lhs, const CRefPtr &rhs) {
    return valueCmp(lhs, rhs) == 0;
  }

  static bool valueNotEqual(const CRefPtr &lhs, const CRefPtr &rhs) {
    return valueCmp(lhs, rhs) != 0;
  }

  bool valueLess(const CRefPtr &rhs) const {
    return valueCmp(*this, rhs) < 0;
  }

  bool valueGreater(const CRefPtr &rhs) const {
    return valueCmp(*this, rhs) > 0;
  }

  bool valueLessEqual(const CRefPtr &rhs) const {
    return valueCmp(*this, rhs) <= 0;
  }

  bool valueGreaterEqual(const CRefPtr &rhs) const {
    return valueCmp(*this, rhs) >= 0;
  }

  bool valueEqual(const CRefPtr &rhs) const {
    return valueCmp(*this, rhs) == 0;
  }

  bool valueNotEqual(const CRefPtr &rhs) const {
    return valueCmp(*this, rhs) != 0;
  }

  struct ValueLess {
    bool operator()(const CRefPtr &lhs, const CRefPtr &rhs) const {
      return valueCmp(lhs, rhs) < 0;
    }
  };

 public:
  CRefPtr() :
   p_(0), count_(new Count(1)) {
  }

  explicit CRefPtr(T *p) :
   p_(p), count_(new Count(1)) {
  }

  explicit CRefPtr(const T *p) :
   p_(const_cast<T *>(p)), count_(new Count(1)) {
  }

  CRefPtr(const CRefPtr &p) :
   p_(p.p_), count_(p.count_) {
    addRef();
  }

 ~CRefPtr() {
    removeRef();
  }

  // p->
  T *operator->() {
    return getPtr();
  }

  // p->
  T *operator->() const {
    return getPtr();
  }

  // *p
  T &operator*() const {
    return *getPtr();
  }

#ifdef CREF_PTR_ALLOW_CAST
  // cast to (T *)
  operator T*() const {
    return getPtr();
  }

  // cast to (void *) (also makes auto cast ambiguous)
  operator void*() const {
    return getPtr();
  }
#endif

  T *getPtr() const {
    assert(p_ != 0 && getRef() > 0);

    return p_;
  }

  CRefPtr &operator=(const CRefPtr &p) {
    if (p.p_ == p_)
      return *this;

    p.addRef();

    removeRef();

    p_     = p.p_;
    count_ = p.count_;

    return *this;
  }

  template<typename S>
  CRefPtr &operator=(const CRefPtr<S> &p) {
    if (p.p_ == p_)
      return *this;

    p.addRef();

    removeRef();

    p_     = p.p_;
    count_ = p.count_;

    return *this;
  }

  CRefPtr &operator=(const T *p) {
    if (p == p_)
      return *this;

    removeRef();

    p_     = const_cast<T *>(p);
    count_ = new Count(0);

    addRef();

    return *this;
  }

  CRefPtr &operator=(T *p) {
    if (p == p_)
      return *this;

    removeRef();

    p_     = p;
    count_ = new Count(0);

    addRef();

    return *this;
  }

  void reset() {
    if (p_ == NULL)
      return;

    removeRef();

    p_     = NULL;
    count_ = new Count(0);

    addRef();
  }

  // compare to pointer
  friend bool operator==(const CRefPtr &lhs, const CRefPtr &rhs) { return lhs.p_ == rhs.p_; }
  friend bool operator!=(const CRefPtr &lhs, const CRefPtr &rhs) { return lhs.p_ != rhs.p_; }

#if 0
  friend bool operator==(const CRefPtr &lhs, const T *rhs) { return lhs.p_ == rhs; }
  friend bool operator==(const T *lhs, const CRefPtr &rhs) { return lhs == rhs.p_; }
  friend bool operator!=(const CRefPtr &lhs, const T *rhs) { return lhs.p_ != rhs; }
  friend bool operator!=(const T *lhs, const CRefPtr &rhs) { return lhs == rhs.p_; }

  template<class U>
  friend bool operator==(const CRefPtr &lhs, const U *rhs) { return lhs.p_ == rhs; }
  template<class U>
  friend bool operator==(const U *lhs, const CRefPtr &rhs) { return lhs == rhs.p_; }
  template<class U>
  friend bool operator!=(const CRefPtr &lhs, const U *rhs) { return lhs.p_ != rhs; }
  template<class U>
  friend bool operator!=(const U *lhs, const CRefPtr &rhs) { return lhs == rhs.p_; }

  // compare to smart pointer
  template<class U>
  bool operator==(const CRefPtr<U> &rhs) const { return p_ == rhs.p_; }
  template<class U>
  bool operator!=(const CRefPtr<U> &rhs) const { return p_ != rhs.p_; }
#endif

  // pointer ordering
  friend bool operator< (const CRefPtr &lhs, const CRefPtr &rhs) { return lhs.p_ <  rhs.p_; }
  friend bool operator> (const CRefPtr &lhs, const CRefPtr &rhs) { return lhs.p_ >  rhs.p_; }
  friend bool operator<=(const CRefPtr &lhs, const CRefPtr &rhs) { return lhs.p_ <= rhs.p_; }
  friend bool operator>=(const CRefPtr &lhs, const CRefPtr &rhs) { return lhs.p_ >= rhs.p_; }

#if 0
  template<class U>
  friend bool operator< (const CRefPtr &lhs, const CRefPtr<U> &rhs) { return lhs.p_ <  rhs.p_; }
  template<class U>
  friend bool operator> (const CRefPtr &lhs, const CRefPtr<U> &rhs) { return lhs.p_ >  rhs.p_; }
  template<class U>
  friend bool operator<=(const CRefPtr &lhs, const CRefPtr<U> &rhs) { return lhs.p_ <= rhs.p_; }
  template<class U>
  friend bool operator>=(const CRefPtr &lhs, const CRefPtr<U> &rhs) { return lhs.p_ >= rhs.p_; }
#endif

#if 0
  // if (p)
  operator bool() const {
    return isValid();
  }
#endif

  // if (!p)
  bool operator!() const {
    return ! isValid();
  }

  bool isValid() const {
    return (p_ != 0);
  }

  void uniquify() {
    if (getRef() > 1) {
      p_ = p_->dup();

      count_ = new Count(0);

      addRef();
    }
  }

  Count getRef() const {
    return *count_;
  }

  template<typename S>
  S *
  cast() const {
    return dynamic_cast<S *>(p_);
  }

  template<typename S>
  bool
  canCast() const {
    return (dynamic_cast<S *>(p_) != NULL);
  }

  template<typename S>
  CRefPtr<S>
  refCast() const {
    return CRefPtr<S>(dynamic_cast<S *>(p_), count_);
  }

  friend std::ostream &operator<<(std::ostream &os, const CRefPtr &th) {
    if (th.isValid())
      th.p_->print(os);
    else
      os << "<null>";

    return os;
  }

  void print(std::ostream &os) const {
    os << p_ << " " << getRef();
  }

 protected:
  CRefPtr(T *p, Count *count) :
   p_(p), count_(count) {
    addRef();
  }

  void addRef() const {
    CRefPtr *th = const_cast<CRefPtr *>(this);

    ++(*th->count_);
  }

  void removeRef() {
    assert(*count_ > 0);

    --(*count_);

    if (*count_ == 0)
      free();
  }

  void free() {
    assert(count_);

    delete p_;
    delete count_;
  }

 protected:
  T     *p_;
  Count *count_;
};

// std::less
namespace std {

template<class T>
struct less< CRefPtr<T> > : public binary_function<CRefPtr<T>, CRefPtr<T>, bool> {
  bool operator()(const CRefPtr<T> &lhs, const CRefPtr<T> &rhs) const {
    return less<T *>()(lhs.getPtr(), rhs.getPtr());
  }
};

}

#endif
