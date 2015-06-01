#ifndef CHSB_H
#define CHSB_H

#include <CRGB.h>
#include <CRGBUtil.h>

template<typename T>
class CRGBT;

template<typename T>
class CRGBUtilT;

template<typename T>
class CHSBT {
 public:
  CHSBT(T h=0, T s=0, T b=0) :
   h_(h), s_(s), b_(b) {
  }

  CHSBT(const CHSBT &hsb) :
   h_(hsb.h_), s_(hsb.s_), b_(hsb.b_) {
  }

 ~CHSBT() { }

  CHSBT &operator=(const CHSBT &hsb) {
    if (&hsb == this)
      return *this;

    h_ = hsb.h_;
    s_ = hsb.s_;
    b_ = hsb.b_;

    return *this;
  }

  T getHue       () const { return h_; }
  T getSaturation() const { return s_; }
  T getBrightness() const { return b_; }

  void setHue       (T h) { h_ = h; }
  void setSaturation(T s) { s_ = s; }
  void setBrightness(T b) { b_ = b; }

  CRGBT<T> toRGB() const { return CRGBUtilT<T>::HSBtoRGB(*this); }

 private:
  T h_, s_, b_;
};

typedef CHSBT<double> CHSB;

#endif
