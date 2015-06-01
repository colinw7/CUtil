#ifndef CHSL_H
#define CHSL_H

#include <CRGB.h>
#include <CRGBUtil.h>

template<typename T>
class CRGBUtilT;

// hue, saturation, lightness
template<typename T>
class CHSLT {
 private:
  T h_, s_, l_;

 public:
  CHSLT() {
  }

  CHSLT(T h, T s, T l) :
   h_(h), s_(s), l_(l) {
  }

  CHSLT(const CHSLT &hsl) :
   h_(hsl.h_), s_(hsl.s_), l_(hsl.l_) {
  }

 ~CHSLT() { }

  CHSLT &operator=(const CHSLT &hsl) {
    if (&hsl == this)
      return *this;

    h_ = hsl.h_;
    s_ = hsl.s_;
    l_ = hsl.l_;

    return *this;
  }

  T getHue       () const { return h_; }
  T getSaturation() const { return s_; }
  T getLuminance () const { return l_; }

  void setHue       (T h) { h_ = h; }
  void setSaturation(T s) { s_ = s; }
  void setLuminance (T l) { l_ = l; }

  CRGBT<T> toRGB() const { return CRGBUtilT<T>::HSLtoRGB(*this); }
};

typedef CHSLT<double> CHSL;

#endif
