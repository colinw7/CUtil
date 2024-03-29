#ifndef CHSV_H
#define CHSV_H

#include <CRGB.h>

// hue, saturation, value
//
// hue        (0-360)
// value      (0-1)
// saturation (0-1)
class CHSV {
 public:
  CHSV(double h=0, double s=0, double v=0) :
   h_(h), s_(s), v_(v) {
  }

  CHSV(const CHSV &hsv) :
   h_(hsv.h_), s_(hsv.s_), v_(hsv.v_) {
  }

 ~CHSV() { }

  CHSV &operator=(const CHSV &hsv) {
    if (&hsv == this)
      return *this;

    h_ = hsv.h_;
    s_ = hsv.s_;
    v_ = hsv.v_;

    return *this;
  }

  //------

  CHSV operator+() const {
    return CHSV(h_, s_, v_);
  }

  CHSV operator-() const {
    return CHSV(-h_, -s_, -v_);
  }

  CHSV &operator+=(const CHSV &rhs) {
    h_ += rhs.h_;
    s_ += rhs.s_;
    v_ += rhs.v_;

    return *this;
  }

  CHSV operator+(const CHSV &rhs) const {
    return CHSV(h_ + rhs.h_, s_ + rhs.s_, v_ + rhs.v_);
  }

  CHSV &operator-=(const CHSV &rhs) {
    h_ -= rhs.h_;
    s_ -= rhs.s_;
    v_ -= rhs.v_;

    return *this;
  }

  CHSV operator-(const CHSV &rhs) const {
    return CHSV(h_ - rhs.h_, s_ - rhs.s_, v_ - rhs.v_);
  }

  CHSV &operator*=(const CHSV &rhs) {
    h_ *= rhs.h_;
    s_ *= rhs.s_;
    v_ *= rhs.v_;

    return *this;
  }

  CHSV &operator*=(double rhs) {
    h_ *= rhs;
    s_ *= rhs;
    v_ *= rhs;

    return *this;
  }

  CHSV operator*(const CHSV &rhs) const {
    return CHSV(h_*rhs.h_, s_*rhs.s_, v_*rhs.v_);
  }

  CHSV &operator/=(const CHSV &rhs) {
    h_ /= rhs.h_;
    s_ /= rhs.s_;
    v_ /= rhs.v_;

    return *this;
  }

  CHSV &operator/=(double rhs) {
    double irhs = 1.0/rhs;

    h_ *= irhs;
    s_ *= irhs;
    v_ *= irhs;

    return *this;
  }

  CHSV operator/(const CHSV &rhs) const {
    return CHSV(h_/rhs.h_, s_/rhs.s_, v_/rhs.v_);
  }

  CHSV operator/(double rhs) const {
    double irhs = 1.0/rhs;

    return CHSV(h_*irhs, s_*irhs, v_*irhs);
  }

  friend CHSV operator*(const CHSV &lhs, double rhs) {
    return CHSV(lhs.h_*rhs, lhs.s_*rhs, lhs.v_*rhs);
  }

  friend CHSV operator*(double lhs, const CHSV &rhs) {
    return CHSV(lhs*rhs.h_, lhs*rhs.s_, lhs*rhs.v_);
  }

  //------

  double getHue       () const { return h_; }
  double getSaturation() const { return s_; }
  double getValue     () const { return v_; }

  void setHue       (double h) { h_ = h; }
  void setSaturation(double s) { s_ = s; }
  void setValue     (double v) { v_ = v; }

  uint getHueI       () const { return uint(iround(h_)); }
  uint getSaturationI() const { return clampI(ivalue(s_)); }
  uint getValueI     () const { return clampI(ivalue(v_)); }

  //CRGB toRGB() const;

 private:
  static uint clampI(int v) {
    return (v >= 0 ? uint(v <= 255 ? v : 255) : 0);
  }

  static int iround(double r) {
    if (r < 0)
      return int(r - 0.5);
    else
      return int(r + 0.5);
  }

  static int ivalue(double r) {
    return iround(r*255.0);
  }

 private:
  double h_ { 0.0 };
  double s_ { 0.0 };
  double v_ { 0.0 };
};

//------

//#include <CRGBUtil.h>

//inline CRGB CHSV::toRGB() const { return CRGBUtil::HSVtoRGB(*this); }

#endif
