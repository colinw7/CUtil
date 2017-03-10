#ifndef COPT_VAL_H
#define COPT_VAL_H

#include <algorithm>
#include <iostream>

template<typename T>
class COptValT {
 public:
  COptValT() :
   value_(), valid_(false) {
  }

  explicit COptValT(const T &value) :
   value_(value), valid_(true) {
  }

  COptValT(const COptValT &rhs) :
    value_(rhs.value_), valid_(rhs.valid_) {
  }

  COptValT &operator=(const COptValT &rhs) {
    value_ = rhs.value_;
    valid_ = rhs.valid_;

    return *this;
  }

  COptValT &operator=(const T &value) {
    setValue(value);

    return *this;
  }

  bool isValid() const { return valid_; }

  const T &getValue() const {
    if (! valid_) throw "Undefined Value";

    return value_;
  }

  T &getValue() {
    if (! valid_) throw "Undefined Value";

    return value_;
  }

  const T &getValue(const T &defValue) const {
    if (! valid_)
      return defValue;

    return value_;
  }

  void setValue(const T &value) {
    value_ = value;
    valid_ = true;
  }

  void setInvalid() {
    valid_ = false;
  }

  COptValT &updateMin(const COptValT &value) {
    if (value.valid_) {
      if (valid_)
        value_ = std::min(value_, value.value_);
      else
        setValue(value.value_);
    }

    return *this;
  }

  COptValT &updateMax(const COptValT &value) {
    if (value.valid_) {
      if (valid_)
        value_ = std::max(value_, value.value_);
      else
        setValue(value.value_);
    }

    return *this;
  }

  const T &updateMin(const T &value) {
    if (valid_)
      value_ = std::min(value_, value);
    else
      setValue(value);

    return value_;
  }

  const T &updateMax(const T &value) {
    if (valid_)
      value_ = std::max(value_, value);
    else
      setValue(value);

    return value_;
  }

  //------

  friend bool operator<(const COptValT &lhs, const COptValT &rhs) {
    if (! lhs.valid_ || ! rhs.valid_) return false;

    return (lhs.value_ < rhs.value_);
  }

  friend bool operator>(const COptValT &lhs, const COptValT &rhs) {
    return ! (lhs < rhs || lhs == rhs);
  }

  friend bool operator<=(const COptValT &lhs, const COptValT &rhs) {
    return (lhs < rhs || lhs == rhs);
  }

  friend bool operator>=(const COptValT &lhs, const COptValT &rhs) {
    return ! (lhs < rhs);
  }

  friend bool operator==(const COptValT &lhs, const COptValT &rhs) {
    if (! lhs.valid_ || ! rhs.valid_) return false;

    return (lhs.value_ == rhs.value_);
  }

  friend bool operator!=(const COptValT &lhs, const COptValT &rhs) {
    return ! (lhs == rhs);
  }

  //------

  friend bool operator<(const COptValT &lhs, const T &rhs) {
    if (! lhs.valid_) return false;

    return (lhs.value_ < rhs);
  }

  friend bool operator>(const COptValT &lhs, const T &rhs) {
    return ! (lhs < rhs || lhs == rhs);
  }

  friend bool operator<=(const COptValT &lhs, const T &rhs) {
    return (lhs < rhs || lhs == rhs);
  }

  friend bool operator>=(const COptValT &lhs, const T &rhs) {
    return ! (lhs < rhs);
  }

  friend bool operator==(const COptValT &lhs, const T &rhs) {
    if (! lhs.valid_) return false;

    return (lhs.value_ == rhs);
  }

  friend bool operator!=(const COptValT &lhs, const T &rhs) {
    return ! (lhs == rhs);
  }

  //------

  friend bool operator<(const T &lhs, const COptValT &rhs) {
    if (! rhs.valid_) return false;

    return (lhs < rhs.value_);
  }

  friend bool operator>(const T &lhs, const COptValT &rhs) {
    return ! (lhs < rhs || lhs == rhs);
  }

  friend bool operator<=(const T &lhs, const COptValT &rhs) {
    return (lhs < rhs || lhs == rhs);
  }

  friend bool operator>=(const T &lhs, const COptValT &rhs) {
    return ! (lhs < rhs);
  }

  friend bool operator==(const T &lhs, const COptValT &rhs) {
    if (! rhs.valid_) return false;

    return (lhs == rhs.value_);
  }

  friend bool operator!=(const T &lhs, const COptValT &rhs) {
    return ! (lhs == rhs);
  }

  //------

  void print(std::ostream &os, const std::string &unsetStr="<unset>") const {
    if (isValid())
      os << getValue();
    else
      os << unsetStr;
  }

  friend std::ostream &operator<<(std::ostream &os, const COptValT &val) {
    val.print(os);

    return os;
  }

 private:
  T    value_;
  bool valid_;
};

typedef COptValT<bool>        COptBool;
typedef COptValT<int>         COptInt;
typedef COptValT<long>        COptLong;
typedef COptValT<uint>        COptUInt;
typedef COptValT<ulong>       COptULong;
typedef COptValT<double>      COptReal;
typedef COptValT<std::string> COptString;

#endif
