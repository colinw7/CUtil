#ifndef CAUTO_PTR
#define CAUTO_PTR

/*! This class provides a transparent wrapper around a pointer and provides
    ownership and lifetime control:

    The pointer can be set or get with control over whether the pointed to object is deleted or not.
*/
template<class T>
class CAutoPtr {
 private:
  T *p_;

 public:
  typedef T element_type;

  // create

  explicit
  CAutoPtr(T *p = 0) :
   p_(p) {
  }

  // construct, copy, destroy

  CAutoPtr(const CAutoPtr &p) :
   p_(p.p_) {
    CAutoPtr &p1 = const_cast<CAutoPtr &>(p);

    p1.set(0);
  }

  CAutoPtr &operator=(const CAutoPtr &p) {
    set(p);

    return *this;
  }

  CAutoPtr &operator=(T *p) {
    set(p);

    return *this;
  }

 ~CAutoPtr() {
    delete p_;
  }

  // pointer like access

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

  // booleans

  bool operator==(T const *p) const {
    return p_ == p;
  }

  bool operator!=(T const *p) const {
    return p_ != p;
  }

  // enquire

  bool isValid() const {
    return (p_ != 0);
  }

  // get

  T *get() const {
    return p_;
  }

  // set (free old value)

  void set(CAutoPtr &p) {
    set(p.p_);

    p.release();
  }

  // set (free old value)

  void set(T *p) {
    delete p_;

    p_ = p;
  }

  // reset (free old value)

  void reset() {
    delete p_;

    p_ = 0;
  }

  // get and reset (extract) (no free)

  T *release() {
    T *p = p_;

    p_ = 0;

    return p;
  }
};

template<class T>
class CAutoArrayPtr {
 private:
  T *p_;

 public:
  typedef T element_type;

  explicit
  CAutoArrayPtr(T *p = 0) :
   p_(p) {
  }

  // construct, copy, destroy

  CAutoArrayPtr(const CAutoArrayPtr &p) :
   p_(p.p_) {
    p.set(0);
  }

  CAutoArrayPtr &operator=(const CAutoArrayPtr &p) {
    set(p);

    return *this;
  }

  CAutoArrayPtr &operator=(T *p) {
    set(p);

    return *this;
  }

 ~CAutoArrayPtr() {
    delete [] p_;
  }

  // subscript

  T operator[](int i) const {
    return p_[i];
  }

  T &operator[](int i) {
    return p_[i];
  }

  // booleans

  bool operator==(T const *p) const {
    return p_ == p;
  }

  bool operator!=(T const *p) const {
    return p_ != p;
  }

  // control

  T *get() const {
    return p_;
  }

  void set(CAutoArrayPtr &p) {
    set(p.p_);

    p.release();
  }

  void set(T *p) {
    delete [] p_;

    p_ = p;
  }

  void reset() {
    delete [] p_;

    p_ = 0;
  }

  T *release() {
    T *p = p_;

    p_ = 0;

    return p;
  }
};

#endif
