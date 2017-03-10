#ifndef CHSI_H
#define CHSI_H

#include <CRGB.h>

class CHSI {
 public:
  CHSI() { }

  CHSI(double h, double s, double i) :
   h_(h), s_(s), i_(i) {
  }

  CHSI(const CHSI &hsi) :
   h_(hsi.h_), s_(hsi.s_), i_(hsi.i_) {
  }

 ~CHSI() { }

  CHSI &operator=(const CHSI &hsi) {
    if (this == &hsi)
      return *this;

    h_ = hsi.h_;
    s_ = hsi.s_;
    i_ = hsi.i_;

    return *this;
  }

  double getHue       () const { return h_; }
  double getSaturation() const { return s_; }
  double getIntensity () const { return i_; }

  //CRGB toRGB() const;

 private:
  double h_, s_, i_;
};

//------

//#include <CRGBUtil.h>

//CRGB CHSI::toRGB() const { return CRGBUtil::HSItoRGB(*this); }

#endif
