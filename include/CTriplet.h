#ifndef CTRIPLET_H
#define CTRIPLET_H

#include <iostream>

template <typename T1, typename T2, typename T3>
struct CTriplet {
  typedef T1 first_type;
  typedef T2 second_type;
  typedef T3 third_type;

  T1 first;
  T2 second;
  T3 third;

  CTriplet(const T1 &nfirst, const T2 &nsecond, const T3 &nthird) :
   first(nfirst), second(nsecond), third(nthird) {
  }

  CTriplet(const CTriplet &triplet) :
   first(triplet.first), second(triplet.second), third(triplet.third) {
  }

  CTriplet &operator=(const CTriplet &triplet) {
    first  = triplet.first;
    second = triplet.second;
    third  = triplet.third;

    return *this;
  }

  bool operator<(const CTriplet &triplet) const {
    if (first != triplet.first)
      return first < triplet.first;

    if (second != triplet.second)
      return second < triplet.second;

    return third < triplet.third;
  }

  bool operator==(const CTriplet &triplet) const {
    return (first == triplet.first && second == triplet.second && third == triplet.third);
  }

  void print(std::ostream &os) const {
    os << "<" << first << "," << second << "," << third << ">";
  }

  friend std::ostream &operator<<(std::ostream &os, const CTriplet &triplet) {
    triplet.print(os);

    return os;
  }
};

#endif
