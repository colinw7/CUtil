#ifndef CPAIR_H
#define CPAIR_H

template <typename T1, typename T2>
struct CPair {
  typedef T1 first_type;
  typedef T2 second_type;

  T1 first;
  T2 second;

  CPair(const T1 &nfirst, const T2 &nsecond) :
   first(nfirst), second(nsecond) {
  }

  bool operator<(const CPair &pair) const {
    if (first != pair.first)
      return first < pair.first;

    return second < pair.second;
  }

  bool operator==(const CPair &pair) const {
    return (first == pair.first && second == pair.second);
  }
};

#endif
