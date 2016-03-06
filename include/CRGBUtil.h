#ifndef CRGB_UTIL_H
#define CRGB_UTIL_H

#include <CRGB.h>
#include <CCMYK.h>
#include <CHSL.h>
#include <CHSV.h>
#include <CHSB.h>
#include <CHSI.h>
#include <CMathGen.h>

template<typename T> class CCMYKT;
template<typename T> class CRGBT;
template<typename T> class CHSLT;
template<typename T> class CHSVT;
template<typename T> class CHSBT;
template<typename T> class CHSIT;

template<typename T>
class CRGBUtilT {
 public:
  static CRGBT<T>
  CMYKtoRGB(const CCMYKT<T> &cmyk) {
    T k = cmyk.getBlack();

    T max_color = std::max(cmyk.getCyan() + k,
                    std::max(cmyk.getMagenta() + k, cmyk.getYellow() + k));

    if (max_color > 1.0)
      k -= max_color - 1.0;

    if (k < 0.0)
      k = 0.0;

    T r = std::max(1.0 - (cmyk.getCyan()    + k), 0.0);
    T g = std::max(1.0 - (cmyk.getMagenta() + k), 0.0);
    T b = std::max(1.0 - (cmyk.getYellow()  + k), 0.0);

    return CRGBT<T>(r, g, b);
  }

  static CRGBT<T>
  HSLtoRGB(const CHSLT<T> &hsl) {
    T r = 0.0, g = 0.0, b = 0.0;

    T v = (hsl.getLuminance() <= 0.5) ?
            (hsl.getLuminance()*(1.0 + hsl.getSaturation())) :
            (hsl.getLuminance() + hsl.getSaturation() -
             hsl.getLuminance()*hsl.getSaturation());

    if (v > 0.0) {
      T m  = hsl.getLuminance() + hsl.getLuminance() - v;
      T sv = (v - m)/v;

      T h = hsl.getHue()*6.0;

      int sextant = int(h);

      T fract = h - sextant;

      T vsf = v * sv * fract;

      T mid1 = m + vsf;
      T mid2 = v - vsf;

      switch (sextant) {
        case 0: r = v   ; g = mid1; b = m   ; break;
        case 1: r = mid2; g = v   ; b = m   ; break;
        case 2: r = m   ; g = v   ; b = mid1; break;
        case 3: r = m   ; g = mid2; b = v   ; break;
        case 4: r = mid1; g = m   ; b = v   ; break;
        case 5: r = v   ; g = m   ; b = mid2; break;
      }
    }

    return CRGBT<T>(r, g, b);
  }

  static CRGBT<T>
  HSVtoRGB(const CHSVT<T> &hsv) {
    T r = hsv.getValue();
    T g = hsv.getValue();
    T b = hsv.getValue();

    if (hsv.getSaturation() > 0.0) {
      T h = hsv.getHue();

      while (h <    0.0) h += 360.0;
      while (h >= 360.0) h -= 360.0;

      h /= 60.0;

      int i = (int) h;

      T f = h - i;

      T f1 = 1.0 - f;

      T p = hsv.getValue()*(1.0 - hsv.getSaturation());
      T q = hsv.getValue()*(1.0 - hsv.getSaturation()*f);
      T t = hsv.getValue()*(1.0 - hsv.getSaturation()*f1);

      switch (i) {
        case  0: r = hsv.getValue(); g = t; b = p; break;
        case  1: r = q; g = hsv.getValue(); b = p; break;
        case  2: r = p; g = hsv.getValue(); b = t; break;
        case  3: r = p; g = q; b = hsv.getValue(); break;
        case  4: r = t; g = p; b = hsv.getValue(); break;
        case  5: r = hsv.getValue(); g = p; b = q; break;
        default:                                   break;
      }
    }

    return CRGBT<T>(r, g, b);
  }

  static CRGBT<T>
  HSBtoRGB(const CHSBT<T> &hsb) {
    CHSVT<T> hsv(hsb.getHue()*(360 - 1E-6), hsb.getSaturation(), hsb.getBrightness());

    return HSVtoRGB(hsv);
  }

  static CRGBT<T>
  HSItoRGB(const CHSIT<T> &hsb) {
    T h = hsb.getHue();
    T s = hsb.getSaturation();
    T i = hsb.getIntensity();

    T hp = h*M_PI*0.5;

    int h1 = CMathGen::Round(hp)/120;

    T r, g, b, c1, c2;

    switch (h1) {
      case 0:
        c1 = s*::cos(hp);
        c2 = ::cos(0.333333*M_PI - hp);

        b = 0.333333*(1.0 - s);
        r = 0.333333*(1.0 + (c1/c2));
        g = 1.0 - r - g;

        break;
      case 1:
        hp -= hp - 0.666666*M_PI;

        c1 = s*::cos(hp);
        c2 = ::cos(0.333333*M_PI - hp);

        g = 0.333333*(1.0 + (c1/c2));
        r = 0.333333*(1.0 - s);
        b = 1.0 - r - g;

        break;
      case 2:
        hp -= hp - 1.333333*M_PI;

        c1 = s*::cos(hp);
        c2 = ::cos(0.333333*M_PI - hp);

        g = 0.333333*(1.0 + (c1/c2));
        r = 0.333333*(1.0 - s);
        b = 1.0 - r - g;

        break;
      default:
        break;
    }

    return CRGBT<T>(0.0, 0.0, 0.0);
  }

  static CCMYKT<T>
  RGBtoCMYK(const CRGBT<T> &rgb) {
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

    return CCMYKT<T>(cyan, magenta, yellow, black);
  }

  static CHSVT<T>
  RGBtoHSV(const CRGBT<T> &rgb) {
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

    return CHSVT<T>(h, s, v);
  }

  static CHSLT<T>
  RGBtoHSL(const CRGBT<T> &rgb) {
    T vm;
    T r2, g2, b2;

    T v = std::max(std::max(rgb.getRed(), rgb.getGreen()), rgb.getBlue());
    T m = std::min(std::min(rgb.getRed(), rgb.getGreen()), rgb.getBlue());

    T l = (m + v)*0.5;

    if (l <= 0.0)
      return CHSL(0.0, 0.0, 0.0);

    vm = v - m;

    if (vm <= 0.0)
      return CHSL(0.0, 0.0, 0.0);

    T s = vm;

    s /= (l <= 0.5) ? (v + m) : (2.0 - v - m);

    r2 = (v - rgb.getRed  ())/vm;
    g2 = (v - rgb.getGreen())/vm;
    b2 = (v - rgb.getBlue ())/vm;

    T h;

    if      (rgb.getRed  () == v) h = (rgb.getGreen() == m ? 5.0 + b2 : 1.0 - g2);
    else if (rgb.getGreen() == v) h = (rgb.getBlue () == m ? 1.0 + r2 : 3.0 - b2);
    else                          h = (rgb.getRed  () == m ? 3.0 + g2 : 5.0 - r2);

    h /= 6.0;

    return CHSLT<T>(h, s, l);
  }

  static CHSBT<T>
  RGBtoHSB(const CRGBT<T> &rgb) {
    CHSVT<T> hsv = RGBtoHSV(rgb);

    T hue        = hsv.getHue()/360.0;
    T saturation = hsv.getSaturation();
    T brightness = hsv.getValue();

    return CHSBT<T>(hue, saturation, brightness);
  }

  static CHSIT<T>
  RGBtoHSI(const CRGBT<T> &rgb) {
    T r = rgb.getRed();
    T g = rgb.getGreen();
    T b = rgb.getBlue();

    T rg = r - g;
    T rb = r - b;
    T gb = g - b;

    if (fabs(rg) < 1E-6 && fabs(rb) < 1E-6 && fabs(gb) < 1E-6)
      return CHSIT<T>(0.0, 0.0, r);

    // Hue
    T t = ::acos(0.5*(rg + rb)/::sqrt(rg*rg + rb*gb));

    if (b > g)
      t = 0.5*M_PI - t;

    T h = 2.0*t/M_PI;

    // Saturation
    T sum = r + g + b;

    // Intensity
    T i = sum/3.0;

    T s = 1.0 - std::min(r, std::min(g, b))/i;

    return CHSIT<T>(h, s, i);
  }

  static uint clampI(int v) {
    return (v >= 0 ? (v <= 255 ? v : 255) : 0);
  }
};

typedef CRGBUtilT<double> CRGBUtil;

#endif
