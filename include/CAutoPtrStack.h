#ifndef CAutoPtrStack_H
#define CAutoPtrStack_H

#include <vector>

template<typename T>
class CAutoPtrStack {
 private:
  typedef std::vector<T *> Stack;

  Stack stack_;

 public:
  typedef typename Stack::iterator       iterator;
  typedef typename Stack::const_iterator const_iterator;
  typedef typename Stack::value_type     value_type;

  CAutoPtrStack(uint n = 0) {
    resize(n);
  }

 ~CAutoPtrStack() {
    clear();
  }

  void push(T *value) {
    assert(value != NULL);

    stack_.push_back(value);
  }

  void pop() {
    assert(! stack_.empty());

    T *value = stack_.back();

    stack_.pop_back();

    delete value;
  }

  void pop(T **value) {
    assert(! stack_.empty());

    *value = stack_.back();

    stack_.pop_back();
  }

  void resize(uint n) {
    uint size = stack_.size();

    stack_.resize(n);

    for (uint i = size; i < n; ++i)
      stack_[i] = NULL;
  }

  void clear() {
    for (auto &p : stack_)
      delete p;

    stack_.clear();
  }

  bool empty() {
    return stack_.empty();
  }

  uint size() {
    return stack_.size();
  }

  iterator begin() {
    return stack_.begin();
  }

  const_iterator begin() const {
    return stack_.begin();
  }

  iterator end() {
    return stack_.end();
  }

  const_iterator end() const {
    return stack_.end();
  }
};

#endif
