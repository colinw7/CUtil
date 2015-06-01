#ifndef CCMYK_H
#define CCMYK_H

#include <CRGB.h>
#include <CRGBUtil.h>

template<typename T>
class CRGBT;

template<typename T>
class CRGBUtilT;

template<typename T>
class CCMYKT {
 private:
  T cyan_;
  T magenta_;
  T yellow_;
  T black_;

 public:
  CCMYKT() :
   cyan_(0), magenta_(0), yellow_(0), black_(0) {
  }

  CCMYKT(T cyan, T magenta, T yellow, T black) :
   cyan_(cyan), magenta_(magenta), yellow_(yellow), black_(black) {
  }

  CCMYKT(const CCMYKT &cmyk) :
    cyan_(cmyk.cyan_), magenta_(cmyk.magenta_),
    yellow_(cmyk.yellow_), black_(cmyk.black_) {
  }

 ~CCMYKT() { }

  CCMYKT &operator=(const CCMYKT &cmyk) {
    if (this == &cmyk)
      return *this;

    cyan_    = cmyk.cyan_;
    magenta_ = cmyk.magenta_;
    yellow_  = cmyk.yellow_;
    black_   = cmyk.black_;

    return *this;
  }

  T getCyan   () const { return cyan_   ; }
  T getMagenta() const { return magenta_; }
  T getYellow () const { return yellow_ ; }
  T getBlack  () const { return black_  ; }

  void setCyan   (T cyan   ) { cyan_    = cyan   ; }
  void setMagenta(T magenta) { magenta_ = magenta; }
  void setYellow (T yellow ) { yellow_  = yellow ; }
  void setBlack  (T black  ) { black_   = black  ; }

  void lighten(T delta) {
    cyan_    -= delta;
    magenta_ -= delta;
    yellow_  -= delta;

    cyan_    = std::min(std::max(cyan_   , 0.0), 1.0);
    magenta_ = std::min(std::max(magenta_, 0.0), 1.0);
    yellow_  = std::min(std::max(yellow_ , 0.0), 1.0);
  }

  CRGBT<T> toRGB() const { return CRGBUtilT<T>::CMYKtoRGB(*this); }
};

typedef CCMYKT<double> CCMYK;

#endif
