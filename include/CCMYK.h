#ifndef CCMYK_H
#define CCMYK_H

#include <CRGB.h>

class CCMYK {
 public:
  CCMYK() :
   cyan_(0), magenta_(0), yellow_(0), black_(0) {
  }

  CCMYK(double cyan, double magenta, double yellow, double black) :
   cyan_(cyan), magenta_(magenta), yellow_(yellow), black_(black) {
  }

  CCMYK(const CCMYK &cmyk) :
    cyan_(cmyk.cyan_), magenta_(cmyk.magenta_),
    yellow_(cmyk.yellow_), black_(cmyk.black_) {
  }

 ~CCMYK() { }

  CCMYK &operator=(const CCMYK &cmyk) {
    if (this == &cmyk)
      return *this;

    cyan_    = cmyk.cyan_;
    magenta_ = cmyk.magenta_;
    yellow_  = cmyk.yellow_;
    black_   = cmyk.black_;

    return *this;
  }

  double getCyan   () const { return cyan_   ; }
  double getMagenta() const { return magenta_; }
  double getYellow () const { return yellow_ ; }
  double getBlack  () const { return black_  ; }

  void setCyan   (double cyan   ) { cyan_    = cyan   ; }
  void setMagenta(double magenta) { magenta_ = magenta; }
  void setYellow (double yellow ) { yellow_  = yellow ; }
  void setBlack  (double black  ) { black_   = black  ; }

  void lighten(double delta) {
    cyan_    -= delta;
    magenta_ -= delta;
    yellow_  -= delta;

    cyan_    = std::min(std::max(cyan_   , 0.0), 1.0);
    magenta_ = std::min(std::max(magenta_, 0.0), 1.0);
    yellow_  = std::min(std::max(yellow_ , 0.0), 1.0);
  }

  //CRGB toRGB() const;

 private:
  double cyan_;
  double magenta_;
  double yellow_;
  double black_;
};

//------

//#include <CRGBUtil.h>

//CRGB CCMYK::toRGB() const { return CRGBUtil::CMYKtoRGB(*this); }

#endif
