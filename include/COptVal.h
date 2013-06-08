#ifndef COPT_VAL_H
#define COPT_VAL_H

#include <cassert>
#include <iostream>
#include <sys/types.h>

template<typename T>
class COptValT {
 private:
  T    value_;
  bool valid_;
  T    def_value_;
  bool def_valid_;

 public:
  COptValT() :
   value_(), valid_(false), def_value_(), def_valid_(false) {
  }

  explicit COptValT(const T &value) :
   value_(value), valid_(true), def_value_(), def_valid_(false) {
  }

  COptValT(const COptValT &rhs) :
    value_(rhs.value_), valid_(rhs.valid_), def_value_(rhs.value_), def_valid_(rhs.valid_) {
  }

  const COptValT &operator=(const COptValT &rhs) {
    value_     = rhs.value_;
    valid_     = rhs.valid_;
    def_value_ = rhs.def_value_;
    def_valid_ = rhs.def_valid_;

    return *this;
  }

  const COptValT &operator=(const T &value) {
    setValue(value);

    return *this;
  }

  bool isValid() const { return getValid(); }

  bool getValid() const { return valid_; }

  const T &getValue() const {
    if      (valid_)
      return value_;
    else if (def_valid_)
      return def_value_;
    else {
      assert(false);
      return value_;
    }
  }

  T &getValue() {
    if      (valid_)
      return value_;
    else if (def_valid_)
      return def_value_;
    else {
      assert(false);
      return value_;
    }
  }

  T getValue(const T &def_value) const {
    if (valid_)
      return value_;
    else
      return def_value;
  }

  void setValue(const T &value) {
    value_ = value;
    valid_ = true;
  }

  void setInvalid() {
    valid_ = false;
  }

  bool isDefValid() const { return getDefValid(); }

  bool getDefValid() const { return def_valid_; }

  const T &getDefValue() const {
    if (def_valid_)
      return def_value_;
    else {
      assert(false);
      return def_value_;
    }
  }

  T &getDefValue() {
    if (def_valid_)
      return def_value_;
    else {
      assert(false);
      return def_value_;
    }
  }

  void setDefValue(const T &value) {
    def_value_ = value;
    def_valid_ = true;
  }

  void setDefInvalid() {
    def_valid_ = false;
  }

  const T &updateMin(const T &value) {
    if (valid_)
      value_ = std::min(value_, value);
    else
      setValue(value);

    return value;
  }

  const T &updateMax(const T &value) {
    if (valid_)
      value_ = std::max(value_, value);
    else
      setValue(value);

    return value;
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
    return os << val.getValue();
  }
};

typedef COptValT<bool>        COptBool;
typedef COptValT<int>         COptInt;
typedef COptValT<uint>        COptUInt;
typedef COptValT<double>      COptReal;
typedef COptValT<std::string> COptString;

#endif
