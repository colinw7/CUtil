#ifndef CFuncs_H
#define CFuncs_H

#include <vector>
#include <iostream>

struct CDeletePointer {
  template<class T>
  void operator()(const T *p) const {
    delete p;
  }
};

template<class T>
class CDeleteMapSecond {
 public:
  void operator()(typename T::value_type &p) const {
    delete p.second;
  }
};

template<class T1, class T2>
void
process_vector(const std::vector<T1> &v, const T2 &proc) {
  typename std::vector<T1>::const_iterator vi1 = v.begin();
  typename std::vector<T1>::const_iterator vi2 = v.end  ();

  for ( ; vi1 != vi2; ++vi1) {
    proc(*vi1);
  }
}

template<class T>
class CPrintSeparated {
 public:
  CPrintSeparated(std::ostream &os=std::cout, const std::string &sep=" ") :
   os_(os), sep_(sep) {
  }

  void operator()(const T &obj) {
    if (! first_)
      os_ << sep_;

    os_ << obj;

    first_ = false;
  }

  void operator()(const T *obj) {
    if (! first_)
      os_ << sep_;

    os_ << *obj;

    first_ = false;
  }

 private:
  std::ostream &os_;
  bool          first_ { true };
  std::string   sep_;
};

#endif
