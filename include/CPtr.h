#ifndef CPTR
#define CPTR

/*! This class provides a transparent wrapper around a pointer and provides
    ownership and lifetime control:

    The pointer can be set or get with control over whether the pointed to object
    is deleted or not.
*/
template<class T>
class CPtr {
 public:
  typedef T element_type;

  // create

  explicit
  CPtr(T *p = NULL) :
   p_(p) {
  }

  // construct, copy, destroy

  CPtr(const CPtr &p) :
   p_(p.p_) {
  }

  CPtr &operator=(const CPtr &p) {
    p_ = p.p_;

    return *this;
  }

  CPtr &operator=(T *p) {
    p_ = p;

    return *this;
  }

 ~CPtr() {
    p_ = NULL;
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
    return (p_ != NULL);
  }

  // get

  T *get() const {
    return p_;
  }

  // set

  void set(const CPtr &p) {
    p.p_ = p;
  }

  // set

  void set(const T *p) {
    p_ = p;
  }

  // reset

  void reset() {
    p_ = NULL;
  }

 private:
  T *p_;
};

#endif
