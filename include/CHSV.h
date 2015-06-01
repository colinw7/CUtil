#ifndef CHSV_H
#define CHSV_H

#include <CRGB.h>
#include <CRGBUtil.h>

template<typename T>
class CRGBT;

template<typename T>
class CRGBUtilT;

// hue, saturation, value
//
// hue        (0-360)
// value      (0-1)
// saturation (0-1)
template<typename T>
class CHSVT {
 public:
  CHSVT(T h=0, T s=0, T v=0) :
   h_(h), s_(s), v_(v) {
  }

  CHSVT(const CHSVT &hsv) :
   h_(hsv.h_), s_(hsv.s_), v_(hsv.v_) {
  }

 ~CHSVT() { }

  CHSVT &operator=(const CHSVT &hsv) {
    if (&hsv == this)
      return *this;

    h_ = hsv.h_;
    s_ = hsv.s_;
    v_ = hsv.v_;

    return *this;
  }

  //------

  CHSVT operator+() const {
    return CHSVT(h_, s_, v_);
  }

  CHSVT operator-() const {
    return CHSVT(-h_, -s_, -v_);
  }

  CHSVT &operator+=(const CHSVT &rhs) {
    h_ += rhs.h_;
    s_ += rhs.s_;
    v_ += rhs.v_;

    return *this;
  }

  CHSVT operator+(const CHSVT &rhs) const {
    return CHSVT(h_ + rhs.h_, s_ + rhs.s_, v_ + rhs.v_);
  }

  CHSVT &operator-=(const CHSVT &rhs) {
    h_ -= rhs.h_;
    s_ -= rhs.s_;
    v_ -= rhs.v_;

    return *this;
  }

  CHSVT operator-(const CHSVT &rhs) const {
    return CHSVT(h_ - rhs.h_, s_ - rhs.s_, v_ - rhs.v_);
  }

  CHSVT &operator*=(const CHSVT &rhs) {
    h_ *= rhs.h_;
    s_ *= rhs.s_;
    v_ *= rhs.v_;

    return *this;
  }

  CHSVT &operator*=(T rhs) {
    h_ *= rhs;
    s_ *= rhs;
    v_ *= rhs;

    return *this;
  }

  CHSVT operator*(const CHSVT &rhs) const {
    return CHSVT(h_*rhs.h_, s_*rhs.s_, v_*rhs.v_);
  }

  CHSVT &operator/=(const CHSVT &rhs) {
    h_ /= rhs.h_;
    s_ /= rhs.s_;
    v_ /= rhs.v_;

    return *this;
  }

  CHSVT &operator/=(T rhs) {
    T irhs = 1.0/rhs;

    h_ *= irhs;
    s_ *= irhs;
    v_ *= irhs;

    return *this;
  }

  CHSVT operator/(const CHSVT &rhs) const {
    return CHSVT(h_/rhs.h_, s_/rhs.s_, v_/rhs.v_);
  }

  CHSVT operator/(T rhs) const {
    T irhs = 1.0/rhs;

    return CHSVT(h_*irhs, s_*irhs, v_*irhs);
  }

  friend CHSVT operator*(const CHSVT &lhs, T rhs) {
    return CHSVT(lhs.h_*rhs, lhs.s_*rhs, lhs.v_*rhs);
  }

  friend CHSVT operator*(T lhs, const CHSVT &rhs) {
    return CHSVT(lhs*rhs.h_, lhs*rhs.s_, lhs*rhs.v_);
  }

  //------

  T getHue       () const { return h_; }
  T getSaturation() const { return s_; }
  T getValue     () const { return v_; }

  void setHue       (T h) { h_ = h; }
  void setSaturation(T s) { s_ = s; }
  void setValue     (T v) { v_ = v; }

  CRGBT<T> toRGB() const { return CRGBUtilT<T>::HSVtoRGB(*this); }

 private:
  T h_, s_, v_;
};

typedef CHSVT<double> CHSV;

#endif
