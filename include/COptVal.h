#ifndef COPT_VAL_H
#define COPT_VAL_H

#include <CThrow.h>

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

  const COptValT &operator=(const COptValT &rhs) {
    value_ = rhs.value_;
    valid_ = rhs.valid_;

    return *this;
  }

  const COptValT &operator=(const T &value) {
    setValue(value);

    return *this;
  }

  bool isValid() const { return valid_; }

  const T &getValue() const {
    if (! valid_)
      CTHROW("Undefined Value");

    return value_;
  }

  T &getValue() {
    if (! valid_)
      CTHROW("Undefined Value");

    return value_;
  }

  T getValue(const T &defValue) const {
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
    if (valid_)
      value_ = std::min(value_, value.value_);
    else if (value.valid_)
      setValue(value.value_);

    return *this;
  }

  COptValT &updateMax(const COptValT &value) {
    if (valid_ && value.valid_)
      value_ = std::max(value_, value.value_);
    else if (value.valid_)
      setValue(value.value_);

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

  friend std::ostream &operator<<(std::ostream &os, const COptValT &val) {
    if (val.isValid())
      os << val.getValue();
    else
      os << "<unset>";

    return os;
  }

 private:
  T    value_;
  bool valid_;
};

typedef COptValT<bool>        COptBool;
typedef COptValT<int>         COptInt;
typedef COptValT<uint>        COptUInt;
typedef COptValT<double>      COptReal;
typedef COptValT<std::string> COptString;

#endif
