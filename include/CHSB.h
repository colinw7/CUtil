#ifndef CHSB_H
#define CHSB_H

#include <CRGB.h>

template<typename T>
class CRGBT;

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

  CRGBT<T> toRGB() const {
    T r = getBrightness();
    T g = getBrightness();
    T b = getBrightness();

    if (getSaturation() > 0.0) {
      T h = getHue()*(360 - 1E-6);

      while (h <    0.0) h += 360.0;
      while (h >= 360.0) h -= 360.0;

      h /= 60.0;

      int i = (int) h;

      T f = h - i;

      T f1 = 1.0 - f;

      T p = getBrightness()*(1.0 - getSaturation());
      T q = getBrightness()*(1.0 - getSaturation()*f);
      T t = getBrightness()*(1.0 - getSaturation()*f1);

      switch (i) {
        case  0: r = getBrightness(); g = t; b = p; break;
        case  1: r = q; g = getBrightness(); b = p; break;
        case  2: r = p; g = getBrightness(); b = t; break;
        case  3: r = p; g = q; b = getBrightness(); break;
        case  4: r = t; g = p; b = getBrightness(); break;
        case  5: r = getBrightness(); g = p; b = q; break;
        default:                                    break;
      }
    }

    return CRGBT<T>(r, g, b);
  }

  static CHSBT<T> fromRGB(const CRGBT<T> &rgb) {
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

    return CHSBT<T>(h/360.0, s, v);
  }

 private:
  T h_, s_, b_;
};

typedef CHSBT<double> CHSB;

#endif
