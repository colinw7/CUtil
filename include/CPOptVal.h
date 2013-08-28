#ifndef CPOPT_VAL_H
#define CPOPT_VAL_H

#include <CThrow.h>
#include <sys/types.h>

template<typename T>
class CPOptValT {
 private:
  T *value_;

 public:
  CPOptValT() :
   value_(NULL) {
  }

  explicit CPOptValT(const T &value) {
    setValue(value);
  }

  CPOptValT(const CPOptValT &rhs) :
   value_(NULL) {
    if (rhs.value_)
      setValue(*rhs.value_);
  }

 ~CPOptValT() {
    delete value_;
  }

  const CPOptValT &operator=(const CPOptValT &rhs) {
    if (rhs.value_)
      setValue(rhs.value);
    else
      value_ = NULL;

    return *this;
  }

  const CPOptValT &operator=(const T &value) {
    setValue(value);

    return *this;
  }

  const T &getValue() const {
    CTHROW_IF(! value_, "Undefined Value");
    return *value_ ;
  }

  T &getValue() {
    CTHROW_IF(! value_, "Undefined Value");
    return *value_ ;
  }

  void getValue(T &value) const {
    CTHROW_IF(! value_, "Undefined Value");
    value = *value_;
  }

  bool isValid() const { return getValid(); }

  bool getValid() const { return value_; }

  void initValue() const {
    if (! value_) {
      CPOptValT *th = const_cast<CPOptValT *>(this);

      th->value_ = new T;
    }
  }

  void setValue(const T &value) {
    if (! value_)
      value_ = new T(value);
    else
      *value_ = value;
  }

  void setInvalid() {
    if (value_) {
      delete value_;

      value_ = NULL;
    }
  }

  const T &updateMin(const T &value) {
    if (value_)
      *value_ = std::min(*value_, value);
    else
      setValue(value);

    return value;
  }

  const T &updateMax(const T &value) {
    if (value_)
      *value_ = std::max(*value_, value);
    else
      setValue(value);

    return value;
  }

  //------

  friend bool operator<(const CPOptValT &lhs, const CPOptValT &rhs) {
    if (! lhs.value_ || ! rhs.value_) return false;

    return (*lhs.value_ < *rhs.value_);
  }

  friend bool operator>(const CPOptValT &lhs, const CPOptValT &rhs) {
    return ! (lhs < rhs || lhs == rhs);
  }

  friend bool operator<=(const CPOptValT &lhs, const CPOptValT &rhs) {
    return (lhs < rhs || lhs == rhs);
  }

  friend bool operator>=(const CPOptValT &lhs, const CPOptValT &rhs) {
    return ! (lhs < rhs);
  }

  friend bool operator==(const CPOptValT &lhs, const CPOptValT &rhs) {
    if (! lhs.value_ || ! rhs.value_) return false;

    return (*lhs.value_ == *rhs.value_);
  }

  friend bool operator!=(const CPOptValT &lhs, const CPOptValT &rhs) {
    return ! (lhs == rhs);
  }

  //------

  friend bool operator<(const CPOptValT &lhs, const T &rhs) {
    if (! lhs.value_) return false;

    return (*lhs.value_ < rhs);
  }

  friend bool operator>(const CPOptValT &lhs, const T &rhs) {
    return ! (lhs < rhs || lhs == rhs);
  }

  friend bool operator<=(const CPOptValT &lhs, const T &rhs) {
    return (lhs < rhs || lhs == rhs);
  }

  friend bool operator>=(const CPOptValT &lhs, const T &rhs) {
    return ! (lhs < rhs);
  }

  friend bool operator==(const CPOptValT &lhs, const T &rhs) {
    if (! lhs.value_) return false;

    return (*lhs.value_ == rhs);
  }

  friend bool operator!=(const CPOptValT &lhs, const T &rhs) {
    return ! (lhs == rhs);
  }

  //------

  friend bool operator<(const T &lhs, const CPOptValT &rhs) {
    if (! rhs.value_) return false;

    return (lhs < *rhs.value_);
  }

  friend bool operator>(const T &lhs, const CPOptValT &rhs) {
    return ! (lhs < rhs || lhs == rhs);
  }

  friend bool operator<=(const T &lhs, const CPOptValT &rhs) {
    return (lhs < rhs || lhs == rhs);
  }

  friend bool operator>=(const T &lhs, const CPOptValT &rhs) {
    return ! (lhs < rhs);
  }

  friend bool operator==(const T &lhs, const CPOptValT &rhs) {
    if (! rhs.value_) return false;

    return (lhs == *rhs.value_);
  }

  friend bool operator!=(const T &lhs, const CPOptValT &rhs) {
    return ! (lhs == rhs);
  }

  //------

  friend std::ostream &operator<<(std::ostream &os, const CPOptValT &val) {
    return os << val.getValue();
  }
};

typedef CPOptValT<bool>        CPOptBool;
typedef CPOptValT<int>         CPOptInt;
typedef CPOptValT<uint>        CPOptUInt;
typedef CPOptValT<double>      CPOptReal;
typedef CPOptValT<std::string> CPOptString;

#endif
