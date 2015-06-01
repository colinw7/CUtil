#ifndef CHSVA_H
#define CHSVA_H

#include <CRGBA.h>
#include <CRGBUtil.h>

// h (0.0 360.0)
// s (0.0 1.0)
// v (0.0 1.0)
// a (0.0 1.0)

template<typename T>
class CRGBUtilT;

template<typename T>
class CHSVAT {
 private:
  typedef CRGBUtilT<T> Util;

 public:
  CHSVAT(T h=0, T s=0, T v=0, T a=1) :
   h_(h), s_(s), v_(v), a_(a) {
  }

  CHSVAT(const CHSVAT &hsva) :
   h_(hsva.h_), s_(hsva.s_), v_(hsva.v_), a_(hsva.a_) {
  }

 ~CHSVAT() { }

  CHSVAT &operator=(const CHSVAT &hsva) {
    if (this == &hsva)
      return *this;

    h_ = hsva.h_;
    s_ = hsva.s_;
    v_ = hsva.v_;
    a_ = hsva.a_;

    return *this;
  }

  CHSVAT &operator+=(const CHSVAT &hsva) {
    if (this == &hsva)
      return *this;

    h_ += hsva.h_;
    s_ += hsva.s_;
    v_ += hsva.v_;
    a_ += hsva.a_;

    return *this;
  }

  CHSVAT &operator*=(const CHSVAT &hsva) {
    if (this == &hsva)
      return *this;

    h_ *= hsva.h_;
    s_ *= hsva.s_;
    v_ *= hsva.v_;
    a_ *= hsva.a_;

    return *this;
  }

  T getHue       () const { return h_; }
  T getSaturation() const { return s_; }
  T getValue     () const { return v_; }
  T getAlpha     () const { return a_; }

  uint getHueI       () const { double h = h_; while (h < 0) h += 360; return int(h) % 360; }
  uint getSaturationI() const { return Util::clampI(255.0*s_); }
  uint getValueI     () const { return Util::clampI(255.0*v_); }
  uint getAlphaI     () const { return Util::clampI(255.0*a_); }

  CHSVT<T> getHSV() const { return CHSVT<T>(h_, s_, v_); }

  CRGBAT<T> toRGBA() const {
    CRGBAT<T> rgba = Util::HSVtoRGB(getHSV());

    rgba.setAlpha(a_);

    return rgba;
  }

 private:
  T h_, s_, v_, a_;
};

typedef CHSVAT<double> CHSVA;

#endif
