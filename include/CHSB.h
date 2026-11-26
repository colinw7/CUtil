#ifndef CHSB_H
#define CHSB_H

#include <CRGB.h>

class CHSB {
 public:
  CHSB() { }

  CHSB(double h, double s, double b) :
   h_(h), s_(s), b_(b) {
  }

  CHSB(const CHSB &hsb) :
   h_(hsb.h_), s_(hsb.s_), b_(hsb.b_) {
  }

 ~CHSB() { }

  CHSB &operator=(const CHSB &hsb) {
    if (&hsb == this)
      return *this;

    h_ = hsb.h_;
    s_ = hsb.s_;
    b_ = hsb.b_;

    return *this;
  }

  double getHue       () const { return h_; }
  double getSaturation() const { return s_; }
  double getBrightness() const { return b_; }

  void setHue       (double h) { h_ = h; }
  void setSaturation(double s) { s_ = s; }
  void setBrightness(double b) { b_ = b; }

  //CRGB toRGB() const;

 private:
  double h_ { 0.0 };
  double s_ { 0.0 };
  double b_ { 0.0 };
};

//------

//#include <CRGBUtil.h>

//CRGB CHSB::toRGB() const { return CRGBUtil::HSBtoRGB(*this); }

#endif
