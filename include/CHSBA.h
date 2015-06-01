#ifndef CHSBA_H
#define CHSBA_H

#include <CRGBA.h>
#include <CRGBUtil.h>

// h (0.0 1.0)
// s (0.0 1.0)
// b (0.0 1.0)
// a (0.0 1.0)

template<typename T>
class CRGBUtilT;

template<typename T>
class CHSBAT {
 private:
  typedef CRGBUtilT<T> Util;

 public:
  CHSBAT(T h=0, T s=0, T b=0, T a=1) :
   h_(h), s_(s), b_(b), a_(a) {
  }

  CHSBAT(const CHSBAT &hsba) :
   h_(hsba.h_), s_(hsba.s_), b_(hsba.b_), a_(hsba.a_) {
  }

 ~CHSBAT() { }

  CHSBAT &operator=(const CHSBAT &hsba) {
    if (this == &hsba)
      return *this;

    h_ = hsba.h_;
    s_ = hsba.s_;
    b_ = hsba.b_;
    a_ = hsba.a_;

    return *this;
  }

  CHSBAT &operator+=(const CHSBAT &hsba) {
    if (this == &hsba)
      return *this;

    h_ += hsba.h_;
    s_ += hsba.s_;
    b_ += hsba.b_;
    a_ += hsba.a_;

    return *this;
  }

  CHSBAT &operator*=(const CHSBAT &hsba) {
    if (this == &hsba)
      return *this;

    h_ *= hsba.h_;
    s_ *= hsba.s_;
    b_ *= hsba.b_;
    a_ *= hsba.a_;

    return *this;
  }

  T getHue       () const { return h_; }
  T getSaturation() const { return s_; }
  T getBrightness() const { return b_; }
  T getAlpha     () const { return a_; }

  uint getHueI       () const { return Util::clampI(255.0*h_); }
  uint getSaturationI() const { return Util::clampI(255.0*s_); }
  uint getBrightnessI() const { return Util::clampI(255.0*b_); }
  uint getAlphaI     () const { return Util::clampI(255.0*a_); }

  CHSBT<T> getHSB() const { return CHSBT<T>(h_, s_, b_); }

  CRGBAT<T> toRGBA() const {
    CRGBAT<T> rgba = Util::HSBtoRGB(getHSB());

    rgba.setAlpha(a_);

    return rgba;
  }

 private:
  T h_, s_, b_, a_;
};

typedef CHSBAT<double> CHSBA;

#endif
