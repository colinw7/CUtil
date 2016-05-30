#ifndef CREF_PTR_DBG_H
#define CREF_PTR_DBG_H

#include <iostream>

template<typename T>
class CTempRefPtr;

template<typename T>
class CRefPtrDbg {
 protected:
  typedef uint Count;

  T     *p_;
  Count *count_;

  friend class CTempRefPtr<T>;

 public:
  static CRefPtrDbg null() {
    return *nullP();
  }

  CRefPtrDbg() :
   p_(0), count_(new Count(1)) {
    addRefDbg();
  }

  explicit CRefPtrDbg(T *p) :
   p_(p), count_(new Count(1)) {
    addRefDbg();
  }

  explicit CRefPtrDbg(T const *p) :
   p_(const_cast<T *>(p)), count_(new Count(1)) {
    addRefDbg();
  }

  CRefPtrDbg(const CRefPtrDbg &p) :
   p_(p.p_), count_(p.count_) {
    addRef();
  }

  virtual ~CRefPtrDbg() {
    removeRef();
  }

  // p->
  T *operator->() {
    assert(p_ != 0 && *count_ > 0);

    return p_;
  }

  // p->
  const T *operator->() const {
    assert(p_ != 0 && *count_ > 0);

    return p_;
  }

  // *p
  T &operator*() const {
    assert(p_ != 0 && *count_ > 0);

    return *p_;
  }

  // cast to (T *)
  operator T*() const {
    assert(p_ != 0 && *count_ > 0);

    return p_;
  }

  CRefPtrDbg &operator=(CRefPtrDbg const &p) {
    if (p.p_ == p_)
      return *this;

    p.addRef();

    removeRef();

    p_     = p.p_;
    count_ = p.count_;

    return *this;
  }

  CRefPtrDbg &operator=(T const *p) {
    if (p == p_)
      return *this;

    removeRef();

    p_     = const_cast<T *>(p);
    count_ = new Count(0);

    addRef();

    return *this;
  }

  CRefPtrDbg &operator=(T *p) {
    if (p == p_)
      return *this;

    removeRef();

    p_     = p;
    count_ = new Count(0);

    addRef();

    return *this;
  }

  bool operator==(CRefPtrDbg const &p) const {
    return p_ == p.p_;
  }

  bool operator!=(CRefPtrDbg const &p) const {
    return p_ != p.p_;
  }

  bool operator==(T const *p) const {
    return p_ == p;
  }

  bool operator!=(T const *p) const {
    return p_ != p;
  }

  bool operator<(T const *p) const {
    return p_ < p;
  }

  // if (p)
  operator bool() const {
    return isValid();
  }

  bool isValid() const {
    return (p_ != 0);
  }

  virtual void uniquify() {
    if (*count_ > 1) {
      p_ = p_->dup();

      count_ = new Count(0);

      addRef();
    }
  }

  Count getNumRefs() const {
    return *count_;
  }

  template<typename S>
  S *
  cast() const {
    return dynamic_cast<S *>(p_);
  }

  friend std::ostream &operator<<(std::ostream &os, const CRefPtrDbg &th) {
    if (th.p_) os << *th.p_;

    return os;
  }

  virtual void print(std::ostream &os) const {
    os << p_ << " " << *count_;
  }

 protected:
  CRefPtrDbg(T *p, Count *count) :
   p_(p), count_(count) {
  }

  static CRefPtrDbg *nullP() {
    static CRefPtrDbg null_ptr;

    return &null_ptr;
  }

  bool isNull() const {
    return (count_ == nullP()->count_);
  }

  virtual void addRef() const {
    if (isNull())
      return;

    CRefPtrDbg *th = const_cast<CRefPtrDbg *>(this);

    ++(*th->count_);

    addRefDbg();
  }

  virtual void removeRef() {
    if (isNull())
      return;

    assert(*count_ > 0);

    removeRefDbg();

    --(*count_);

    if (*count_ == 0)
      free();
  }

  virtual void free() {
    assert(count_);

    if (p_)
      std::cerr << "free: " << *p_ << " " <<
                   "(" << p_ << " #" << *count_ << ")" << std::endl;
    else
      std::cerr << "free: " <<
                   "(" << p_ << " #" << *count_ << ")" << std::endl;

    delete p_;
    delete count_;
  }

  void addRefDbg() const {
    if (p_)
      std::cerr << "addRef: " << *p_ << " " <<
                   "(" << p_ << " #" << *count_ << ")" << std::endl;
    else
      std::cerr << "addRef: " <<
                   "(" << p_ << " #" << *count_ << ")" << std::endl;
  }

  void removeRefDbg() {
    if (p_)
      std::cerr << "removeRef: " << *p_ << " " <<
                   "(" << p_ << " #" << *count_ - 1<< ")" << std::endl;
    else
      std::cerr << "removeRef: " <<
                   "(" << p_ << " #" << *count_ - 1<< ")" << std::endl;
  }
};

#endif
