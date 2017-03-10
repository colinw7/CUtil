#ifndef CHSL_H
#define CHSL_H

#include <CRGB.h>

// hue, saturation, lightness
class CHSL {
 public:
  CHSL() {
  }

  CHSL(double h, double s, double l) :
   h_(h), s_(s), l_(l) {
  }

  CHSL(const CHSL &hsl) :
   h_(hsl.h_), s_(hsl.s_), l_(hsl.l_) {
  }

 ~CHSL() { }

  CHSL &operator=(const CHSL &hsl) {
    if (&hsl == this)
      return *this;

    h_ = hsl.h_;
    s_ = hsl.s_;
    l_ = hsl.l_;

    return *this;
  }

  double getHue       () const { return h_; }
  double getSaturation() const { return s_; }
  double getLuminance () const { return l_; }

  void setHue       (double h) { h_ = h; }
  void setSaturation(double s) { s_ = s; }
  void setLuminance (double l) { l_ = l; }

  //CRGB toRGB() const;

 private:
  double h_, s_, l_;
};

//------

//#include <CRGBUtil.h>

//CRGB CHSL::toRGB() const { return CRGBUtil::HSLtoRGB(*this); }

#endif
