#ifndef CHSVA_H
#define CHSVA_H

#include <CRGBA.h>

// h (0.0 360.0)
// s (0.0 1.0)
// v (0.0 1.0)
// a (0.0 1.0)

template<typename T>
class CRGBUtil;

template<typename T>
class CHSVAT {
 private:
  typedef CRGBUtil<T> Util;

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

  uint clampI(int i) const { return std::min(std::max(i, 0), 255); }

  uint getHueI       () const { double h = h_; while (h < 0) h += 360; return int(h) % 360; }
  uint getSaturationI() const { return clampI(255.0*s_); }
  uint getValueI     () const { return clampI(255.0*v_); }
  uint getAlphaI     () const { return clampI(255.0*a_); }

  CRGBAT<T> toRGBA() const {
    T r = v_;
    T g = v_;
    T b = v_;

    if (s_ > 0.0) {
      T h = h_;

      while (h <    0.0) h += 360.0;
      while (h >= 360.0) h -= 360.0;

      h /= 60.0;

      int i = (int) h;

      T f = h - i;

      T f1 = 1.0 - f;

      T p = v_*(1.0 - s_);
      T q = v_*(1.0 - s_*f);
      T t = v_*(1.0 - s_*f1);

      switch (i) {
        case  0: r = v_; g = t ; b = p ; break;
        case  1: r = q ; g = v_; b = p ; break;
        case  2: r = p ; g = v_; b = t ; break;
        case  3: r = p ; g = q ; b = v_; break;
        case  4: r = t ; g = p ; b = v_; break;
        case  5: r = v_; g = p ; b = q ; break;
        default:                         break;
      }
    }

    return CRGBAT<T>(r, g, b, a_);
  }

 private:
  T h_, s_, v_, a_;
};

typedef CHSVAT<double> CHSVA;

#endif
