#ifndef CHSVA_H
#define CHSVA_H

#include <CRGBA.h>

// h (0.0 360.0)
// s (0.0 1.0)
// v (0.0 1.0)
// a (0.0 1.0)

class CHSVA {
 private:
  static uint clampI(int v) {
    return (v >= 0 ? (v <= 255 ? v : 255) : 0);
  }

 public:
  CHSVA(double h=0, double s=0, double v=0, double a=1) :
   h_(h), s_(s), v_(v), a_(a) {
  }

  CHSVA(const CHSVA &hsva) :
   h_(hsva.h_), s_(hsva.s_), v_(hsva.v_), a_(hsva.a_) {
  }

 ~CHSVA() { }

  CHSVA &operator=(const CHSVA &hsva) {
    if (this == &hsva)
      return *this;

    h_ = hsva.h_;
    s_ = hsva.s_;
    v_ = hsva.v_;
    a_ = hsva.a_;

    return *this;
  }

  CHSVA &operator+=(const CHSVA &hsva) {
    if (this == &hsva)
      return *this;

    h_ += hsva.h_;
    s_ += hsva.s_;
    v_ += hsva.v_;
    a_ += hsva.a_;

    return *this;
  }

  CHSVA &operator*=(const CHSVA &hsva) {
    if (this == &hsva)
      return *this;

    h_ *= hsva.h_;
    s_ *= hsva.s_;
    v_ *= hsva.v_;
    a_ *= hsva.a_;

    return *this;
  }

  double getHue       () const { return h_; }
  double getSaturation() const { return s_; }
  double getValue     () const { return v_; }
  double getAlpha     () const { return a_; }

  uint getHueI       () const { double h = h_; while (h < 0) h += 360; return int(h) % 360; }
  uint getSaturationI() const { return clampI(255.0*s_); }
  uint getValueI     () const { return clampI(255.0*v_); }
  uint getAlphaI     () const { return clampI(255.0*a_); }

  CHSV getHSV() const { return CHSV(h_, s_, v_); }

  CRGBA toRGBA() const {
    CRGBA rgba = CRGBUtil::HSVtoRGB(getHSV());

    rgba.setAlpha(a_);

    return rgba;
  }

 private:
  double h_, s_, v_, a_;
};

//------

//#include <CRGBUtil.h>
// CRGBA CHSVA::toRGBA() const {
//   CRGBA rgba = CRGBUtil::HSVtoRGB(getHSV()); rgba.setAlpha(a_); return rgba;
// }

#endif
