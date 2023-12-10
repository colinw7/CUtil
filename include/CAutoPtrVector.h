#ifndef CAutoPtrVector_H
#define CAutoPtrVector_H

#include <vector>
#include <cassert>
#include <sys/types.h>

template<typename T>
class CAutoPtrVector {
 private:
  typedef std::vector<T *> Vector;

  Vector vector_;

 public:
  typedef typename Vector::iterator       iterator;
  typedef typename Vector::const_iterator const_iterator;
  typedef typename Vector::value_type     value_type;

  CAutoPtrVector(uint n = 0) {
    resize(n);
  }

 ~CAutoPtrVector() {
    clear();
  }

  uint size() const { return uint(vector_.size()); }

  void push_back(T *value) {
    addValue(value);
  }

  T *operator[](int i) const {
    return getValue(uint(i));
  }

  void addValue(T *value) {
    assert(value != nullptr);

    vector_.push_back(value);
  }

  void setValue(uint i, T *value) {
    assert(value != nullptr);

    uint size = vector_.size();

    assert(i < size);

    if (vector_[i] != value)
      delete vector_[i];

    vector_[i] = value;
  }

  T *getValue(uint i) const {
    uint size = uint(vector_.size());

    assert(i < size);

    return vector_[i];
  }

  void resize(uint n) {
    uint size = uint(vector_.size());

    vector_.resize(n);

    for (uint i = size; i < n; ++i)
      vector_[i] = nullptr;
  }

  void clear() {
    for (auto &p : vector_)
      delete p;

    vector_.clear();
  }

  iterator begin() {
    return vector_.begin();
  }

  const_iterator begin() const {
    return vector_.begin();
  }

  iterator end() {
    return vector_.end();
  }

  const_iterator end() const {
    return vector_.end();
  }
};

#endif
