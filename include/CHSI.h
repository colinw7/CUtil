#ifndef CHSI_H
#define CHSI_H

#include <CRGB.h>
#include <CRGBUtil.h>

template<typename T>
class CRGBUtilT;

template<typename T>
class CHSIT {
 private:
  T h_, s_, i_;

 public:
  CHSIT() { }

  CHSIT(T h, T s, T i) :
   h_(h), s_(s), i_(i) {
  }

  CHSIT(const CHSIT &hsi) :
   h_(hsi.h_), s_(hsi.s_), i_(hsi.i_) {
  }

 ~CHSIT() { }

  CHSIT &operator=(const CHSIT &hsi) {
    if (this == &hsi)
      return *this;

    h_ = hsi.h_;
    s_ = hsi.s_;
    i_ = hsi.i_;

    return *this;
  }

  T getHue       () const { return h_; }
  T getSaturation() const { return s_; }
  T getIntensity () const { return i_; }

  CRGBT<T> toRGB() const { return CRGBUtilT<T>::HSItoRGB(*this); }
};

typedef CHSIT<double> CHSI;

#endif
