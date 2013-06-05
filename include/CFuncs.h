#ifndef CFuncs_H
#define CFuncs_H

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

#endif
