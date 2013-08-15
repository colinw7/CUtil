#ifndef CCMYK_H
#define CCMYK_H

#include <CRGB.h>

template<typename T>
class CRGBT;

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

  CRGBT<T> toRGB() const {
    T k = getBlack();

    T max_color = std::max(getCyan() + k, std::max(getMagenta() + k, getYellow() + k));

    if (max_color > 1.0)
      k -= max_color - 1.0;

    if (k < 0.0)
      k = 0.0;

    T r = std::max(1.0 - (getCyan()    + k), 0.0);
    T g = std::max(1.0 - (getMagenta() + k), 0.0);
    T b = std::max(1.0 - (getYellow()  + k), 0.0);

    return CRGBT<T>(r, g, b);
  }

  static CCMYKT fromRGB(const CRGBT<T> &rgb) {
    T cyan    = 1.0 - rgb.getRed();
    T magenta = 1.0 - rgb.getGreen();
    T yellow  = 1.0 - rgb.getBlue();

    //------

    T black = std::min(std::min(cyan, magenta), yellow);

    black = std::min(std::max(black, 0.0), 1.0);

    //------

    cyan    -= black;
    magenta -= black;
    yellow  -= black;

    cyan    = std::min(std::max(cyan   , 0.0), 1.0);
    magenta = std::min(std::max(magenta, 0.0), 1.0);
    yellow  = std::min(std::max(yellow , 0.0), 1.0);

    return CCMYKT(cyan, magenta, yellow, black);
  }
};

typedef CCMYKT<double> CCMYK;

#endif
