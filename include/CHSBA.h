#ifndef CHSBA_H
#define CHSBA_H

#include <CRGBA.h>

// h (0.0 1.0)
// s (0.0 1.0)
// b (0.0 1.0)
// a (0.0 1.0)

class CHSBA {
 private:
  static uint clampI(int v) {
    return (v >= 0 ? (v <= 255 ? v : 255) : 0);
  }

 public:
  CHSBA(double h=0, double s=0, double b=0, double a=1) :
   h_(h), s_(s), b_(b), a_(a) {
  }

  CHSBA(const CHSBA &hsba) :
   h_(hsba.h_), s_(hsba.s_), b_(hsba.b_), a_(hsba.a_) {
  }

 ~CHSBA() { }

  CHSBA &operator=(const CHSBA &hsba) {
    if (this == &hsba)
      return *this;

    h_ = hsba.h_;
    s_ = hsba.s_;
    b_ = hsba.b_;
    a_ = hsba.a_;

    return *this;
  }

  CHSBA &operator+=(const CHSBA &hsba) {
    if (this == &hsba)
      return *this;

    h_ += hsba.h_;
    s_ += hsba.s_;
    b_ += hsba.b_;
    a_ += hsba.a_;

    return *this;
  }

  CHSBA &operator*=(const CHSBA &hsba) {
    if (this == &hsba)
      return *this;

    h_ *= hsba.h_;
    s_ *= hsba.s_;
    b_ *= hsba.b_;
    a_ *= hsba.a_;

    return *this;
  }

  double getHue       () const { return h_; }
  double getSaturation() const { return s_; }
  double getBrightness() const { return b_; }
  double getAlpha     () const { return a_; }

  uint getHueI       () const { return clampI(255.0*h_); }
  uint getSaturationI() const { return clampI(255.0*s_); }
  uint getBrightnessI() const { return clampI(255.0*b_); }
  uint getAlphaI     () const { return clampI(255.0*a_); }

  CHSB getHSB() const { return CHSB(h_, s_, b_); }

  CRGBA toRGBA() const;

 private:
  double h_, s_, b_, a_;
};

//------

#include <CRGBUtil.h>

CRGBA CHSBA::toRGBA() const {
  CRGBA rgba = CRGBUtil::HSBtoRGB(getHSB());

  rgba.setAlpha(a_);

  return rgba;
}

#endif
