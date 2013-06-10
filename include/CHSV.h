#ifndef CHSV_H
#define CHSV_H

#include <CRGB.h>

template<typename T>
class CRGBT;

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

  T getHue       () const { return h_; }
  T getSaturation() const { return s_; }
  T getValue     () const { return v_; }

  void setHue       (T h) { h_ = h; }
  void setSaturation(T s) { s_ = s; }
  void setValue     (T v) { v_ = v; }

  CRGBT<T> toRGB() const {
    T r = getValue();
    T g = getValue();
    T b = getValue();

    if (getSaturation() > 0.0) {
      T h = getHue();

      while (h <    0.0) h += 360.0;
      while (h >= 360.0) h -= 360.0;

      h /= 60.0;

      int i = (int) h;

      T f = h - i;

      T f1 = 1.0 - f;

      T p = getValue()*(1.0 - getSaturation());
      T q = getValue()*(1.0 - getSaturation()*f);
      T t = getValue()*(1.0 - getSaturation()*f1);

      switch (i) {
        case  0: r = getValue(); g = t; b = p; break;
        case  1: r = q; g = getValue(); b = p; break;
        case  2: r = p; g = getValue(); b = t; break;
        case  3: r = p; g = q; b = getValue(); break;
        case  4: r = t; g = p; b = getValue(); break;
        case  5: r = getValue(); g = p; b = q; break;
        default:                               break;
      }
    }

    return CRGBT<T>(r, g, b);
  }

  static CHSVT fromRGB(const CRGBA &rgba) {
    return fromRGB(CRGB(rgba.getRed(), rgba.getGreen(), rgba.getBlue()));
  }

  static CHSVT fromRGB(const CRGB &rgb) {
    T r = rgb.getRed();
    T g = rgb.getGreen();
    T b = rgb.getBlue();

    T min_rgb = std::min(r, std::min(g, b));
    T max_rgb = std::max(r, std::max(g, b));

    T delta = max_rgb - min_rgb;

    T v = max_rgb;

    T s = 0.0;

    if (max_rgb > 0.0)
      s = delta/max_rgb;

    T h = 0.0;

    if (s > 0.0) {
      if      (r == max_rgb) h = 0.0 + (g - b)/delta;
      else if (g == max_rgb) h = 2.0 + (b - r)/delta;
      else                   h = 4.0 + (r - g)/delta;

      h *= 60.0;

      while (h <    0.0) h += 360.0;
      while (h >= 360.0) h -= 360.0;
    }

    return CHSVT(h, s, v);
  }

 private:
  T h_, s_, v_;
};

typedef CHSVT<double> CHSV;

#endif
