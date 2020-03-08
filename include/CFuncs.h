#ifndef CFuncs_H
#define CFuncs_H

#include <vector>
#include <list>
#include <set>
#include <map>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <sstream>

//---

// TODO: remove, use C++ for loop
struct CDeletePointer {
  template<class T>
  void operator()(const T *p) const {
    delete p;
  }
};

// TODO: not used
struct CDeletePointerSecond {
  template<class T>
  void operator()(const T &p) const {
    delete p.second;
  }
};

// TODO: remove, use C++ for loop
template<class T>
class CDeleteMapSecond {
 public:
  void operator()(typename T::value_type &p) const {
    delete p.second;
  }
};

// TODO: not used
template<class T>
class CPrintFuncSeparated {
 public:
  CPrintFuncSeparated(std::ostream &os=std::cout, const std::string &sep=" ") :
   os_(os), sep_(sep) {
  }

  void operator()(const T &obj) {
    if (! first_)
      os_ << sep_;

    obj.print(os_);

    first_ = false;
  }

  void operator()(const T *obj) {
    if (! first_)
      os_ << sep_;

    obj->print(os_);

    first_ = false;
  }

 private:
  std::ostream &os_;
  bool          first_ { true };
  std::string   sep_;
};

// TODO: replace ?
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

// TODO: not used
template<class T>
void
CPrintContainer(const typename std::vector<T>::const_iterator p1,
                const typename std::vector<T>::const_iterator p2,
                std::ostream &os=std::cout, const std::string &sep=" ",
                const std::string &term="\n")
{
  std::for_each(p1, p2, CPrintSeparated<T>(os, sep));

  os << term;
}

template<class T>
void
CPrintContainer(const typename std::list<T>::const_iterator p1,
                const typename std::list<T>::const_iterator p2,
                std::ostream &os=std::cout, const std::string &sep=" ",
                const std::string &term="\n")
{
  std::for_each(p1, p2, CPrintSeparated<T>(os, sep));

  os << term;
}

// TODO: not used
template<class T>
class CAppendSeparated {
 public:
  CAppendSeparated(std::ostream &os=std::cout, const std::string &sep=" ") :
   os_(os), sep_(sep) {
  }

  void operator()(std::string &s, const T &obj) {
    if (! first_)
      s += sep_;

    std::stringstream ss;

    ss << obj;

    s += ss.str();

    first_ = false;
  }

 private:
  std::ostream &os_;
  bool          first_ { true };
  std::string   sep_;
};

//---

// TODO: not used
template<class T>
void
CPrintContainer1(const typename std::list<T>::const_iterator p1,
                 const typename std::list<T>::const_iterator p2,
                 std::ostream &os=std::cout, const std::string &sep=" ",
                 const std::string &term="\n") {
  std::string s = std::accumulate(p1, p2, "",  CAppendSeparated<T>(os, sep));

  os << s << term;
}

// TODO: not used
template<typename T>
struct CArrayStreamerT {
  CArrayStreamerT(const std::vector<T> &array_, const std::string &sep_=" ") :
   array(array_), sep(sep_) {
  }

  const std::vector<T> &array;
  const std::string    &sep;
};

template<typename T>
CArrayStreamerT<T>
makeArrayStreamer(const std::vector<T> &array, const std::string &sep=" ") {
  return CArrayStreamerT<T>(array, sep);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const CArrayStreamerT<T> &as) {
  unsigned int n = as.array.size();

  for (unsigned int i = 0; i < n; ++i) {
    if (i > 0) os << as.sep;

    os << as.array[i];
  }

  return os;
}

//---

// TODO: not used
template<typename T1, typename T2>
T1 *
CBinarySearch(T1 *first, T1 *last, const T2 &value, int (*cmp)(T1 *, const T2 &))
{
  T1 *mid = (first + last)/2;

  int val = (*cmp)(mid, value);

  if (val == 0)
    return first;

  if (val < 0)
    return CBinarySearch(mid + 1, last, cmp);
  else
    return CBinarySearch(first, mid, cmp);
}

//---

// TODO: remove
template<class T1, class T2>
void
process_vector(const std::vector<T1> &v, const T2 &proc) {
  typename std::vector<T1>::const_iterator vi1 = v.begin();
  typename std::vector<T1>::const_iterator vi2 = v.end  ();

  for ( ; vi1 != vi2; ++vi1) {
    proc(*vi1);
  }
}

// TODO: remove
template<class Iterator, class Func>
void
process_map(Iterator p1, Iterator p2, Func f)
{
  for ( ; p1 != p2; ++p1)
    f(p1->second);
}

// TODO: remove
template<class KEY, class DATA>
void
copy_map(const std::map<KEY,DATA> &map1, std::map<KEY,DATA> &map2) {
  typedef typename std::map<KEY,DATA> Map;

  typename Map::const_iterator p1, p2;

  for (p1 = map1.begin(), p2 = map1.end(); p1 != p2; ++p1)
    map2[(*p1).first] = (*p1).second;
}

//---

template<class T>
class CVectorP : public std::vector<T *> {
 private:
  typedef std::vector<T *> Vector;

 public:
  ~CVectorP() {
     for_each(Vector::begin(), Vector::end(), CDeletePointer());
  }
};

//---

template<class T>
void
CDeleteItem(std::vector<T> &c, const T &v) {
  c.erase(std::remove(c.begin(), c.end(), v), c.end());
}

template<class T>
void
CDeleteItem(std::list<T> &c, const T &v) {
  c.remove(v);
}

template<class T>
void
CDeleteItem(std::set<T> &c, const T &v) {
  c.erase(v);
}

template<class K, class V>
void
CDeleteItem(std::map<K,V> &c, const V &v) {
  c.erase(v);
}

template<class T>
void
CDeleteItem(std::vector<T> &c, bool (*pred)(const T &v)) {
  c.erase(std::remove(c.begin(), c.end(), pred), c.end());
}

template<class T>
void
CDeleteItem(std::list<T> &c, bool (*pred)(const T &v)) {
  c.remove_if(pred);
}

template<class T>
void
CDeleteItem(std::set<T> &c, bool (*pred)(const T &v)) {
  typename std::set<T>::iterator p1, p2;

  for (p1 = c.begin(), p2 = c.end(); p1 != p2; ) {
    if ((*pred)((*p1).second)) c.erase(p1++);
    else                       ++p1;
  }
}

template<class K, class V>
void
CDeleteItem(std::map<K,V> &c, bool (*pred)(const V &v)) {
  typename std::map<K,V>::iterator p1, p2;

  for (p1 = c.begin(), p2 = c.end(); p1 != p2; ) {
    if ((*pred)((*p1).second)) c.erase(p1++);
    else                       ++p1;
  }
}

//---

// TODO: std::shrink_to_fit

// shrink to fix i.e. capacity() == size()
template<class T>
void
CShrinkContainer(std::vector<T> &c)
{
  std::vector<T>(c).swap(c);
}

template<class T>
void
CShrinkContainer(T &t)
{
  T(t).swap(t);
}

//---

#endif
