#ifndef CRGB_UTIL_H
#define CRGB_UTIL_H

#include <CRGB.h>
#include <CCMYK.h>
#include <CHSL.h>
#include <CHSV.h>
#include <CHSVA.h>
#include <CHSB.h>
#include <CHSI.h>
#include <CMathRound.h>
#include <cmath>

class CRGBUtil {
 public:
  static CRGB CMYKtoRGB(const CCMYK &cmyk) {
    double k = cmyk.getBlack();

    double max_color = std::max(cmyk.getCyan() + k,
                    std::max(cmyk.getMagenta() + k, cmyk.getYellow() + k));

    if (max_color > 1.0)
      k -= max_color - 1.0;

    if (k < 0.0)
      k = 0.0;

    double r = std::max(1.0 - (cmyk.getCyan()    + k), 0.0);
    double g = std::max(1.0 - (cmyk.getMagenta() + k), 0.0);
    double b = std::max(1.0 - (cmyk.getYellow()  + k), 0.0);

    return CRGB(r, g, b);
  }

  static CRGB HSLtoRGB(const CHSL &hsl) {
    double r = 0.0, g = 0.0, b = 0.0;

    double v = (hsl.getLuminance() <= 0.5) ?
            (hsl.getLuminance()*(1.0 + hsl.getSaturation())) :
            (hsl.getLuminance() + hsl.getSaturation() -
             hsl.getLuminance()*hsl.getSaturation());

    if (v > 0.0) {
      double m  = hsl.getLuminance() + hsl.getLuminance() - v;
      double sv = (v - m)/v;

      double h = hsl.getHue()*6.0;

      int sextant = int(h);

      double fract = h - sextant;

      double vsf = v * sv * fract;

      double mid1 = m + vsf;
      double mid2 = v - vsf;

      switch (sextant) {
        case 0: r = v   ; g = mid1; b = m   ; break;
        case 1: r = mid2; g = v   ; b = m   ; break;
        case 2: r = m   ; g = v   ; b = mid1; break;
        case 3: r = m   ; g = mid2; b = v   ; break;
        case 4: r = mid1; g = m   ; b = v   ; break;
        case 5: r = v   ; g = m   ; b = mid2; break;
      }
    }

    return CRGB(r, g, b);
  }

  static CRGB HSVtoRGB(const CHSV &hsv) {
    double r = hsv.getValue();
    double g = hsv.getValue();
    double b = hsv.getValue();

    if (hsv.getSaturation() > 0.0) {
      double h = hsv.getHue();

      while (h <    0.0) h += 360.0;
      while (h >= 360.0) h -= 360.0;

      h /= 60.0;

      int i = int(h);

      double f = h - i;

      double f1 = 1.0 - f;

      double p = hsv.getValue()*(1.0 - hsv.getSaturation());
      double q = hsv.getValue()*(1.0 - hsv.getSaturation()*f);
      double t = hsv.getValue()*(1.0 - hsv.getSaturation()*f1);

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

    return CRGB(r, g, b);
  }

  static CRGBA HSVAtoRGBA(const CHSVA &hsva) {
    CRGBA rgba = HSVtoRGB(hsva.getHSV());

    return rgba.setAlpha(hsva.getAlpha());
  }

  static CRGB HSBtoRGB(const CHSB &hsb) {
    CHSV hsv(hsb.getHue()*(360 - 1E-6), hsb.getSaturation(), hsb.getBrightness());

    return HSVtoRGB(hsv);
  }

  static CRGB HSItoRGB(const CHSI &hsb) {
    double h = hsb.getHue();
    double s = hsb.getSaturation();
  //double i = hsb.getIntensity();

    double hp = h*M_PI*0.5;

    int h1 = CMathRound::Round(hp)/120;

    double r = 0.0, g = 0.0, b = 0.0;

    double c1, c2;

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

    //return CRGB(0.0, 0.0, 0.0);
    return CRGB(r, g, b);
  }

  static CCMYK RGBtoCMYK(const CRGB &rgb) {
    double cyan    = 1.0 - rgb.getRed();
    double magenta = 1.0 - rgb.getGreen();
    double yellow  = 1.0 - rgb.getBlue();

    //------

    double black = std::min(std::min(cyan, magenta), yellow);

    black = std::min(std::max(black, 0.0), 1.0);

    //------

    cyan    -= black;
    magenta -= black;
    yellow  -= black;

    cyan    = std::min(std::max(cyan   , 0.0), 1.0);
    magenta = std::min(std::max(magenta, 0.0), 1.0);
    yellow  = std::min(std::max(yellow , 0.0), 1.0);

    return CCMYK(cyan, magenta, yellow, black);
  }

  static CHSV RGBtoHSV(const CRGB &rgb) {
    double r = rgb.getRed();
    double g = rgb.getGreen();
    double b = rgb.getBlue();

    double min_rgb = std::min(r, std::min(g, b));
    double max_rgb = std::max(r, std::max(g, b));

    double delta = max_rgb - min_rgb;

    double v = max_rgb;

    double s = 0.0;

    if (max_rgb > 0.0)
      s = delta/max_rgb;

    double h = 0.0;

    if (s > 0.0) {
      if      (r == max_rgb) h = 0.0 + (g - b)/delta;
      else if (g == max_rgb) h = 2.0 + (b - r)/delta;
      else                   h = 4.0 + (r - g)/delta;

      h *= 60.0;

      while (h <    0.0) h += 360.0;
      while (h >= 360.0) h -= 360.0;
    }

    return CHSV(h, s, v);
  }

  static CHSL RGBtoHSL(const CRGB &rgb) {
    double vm;
    double r2, g2, b2;

    double v = std::max(std::max(rgb.getRed(), rgb.getGreen()), rgb.getBlue());
    double m = std::min(std::min(rgb.getRed(), rgb.getGreen()), rgb.getBlue());

    double l = (m + v)*0.5;

    if (l <= 0.0)
      return CHSL(0.0, 0.0, 0.0);

    vm = v - m;

    if (vm <= 0.0)
      return CHSL(0.0, 0.0, 0.0);

    double s = vm;

    s /= (l <= 0.5) ? (v + m) : (2.0 - v - m);

    r2 = (v - rgb.getRed  ())/vm;
    g2 = (v - rgb.getGreen())/vm;
    b2 = (v - rgb.getBlue ())/vm;

    double h;

    if      (rgb.getRed  () == v) h = (rgb.getGreen() == m ? 5.0 + b2 : 1.0 - g2);
    else if (rgb.getGreen() == v) h = (rgb.getBlue () == m ? 1.0 + r2 : 3.0 - b2);
    else                          h = (rgb.getRed  () == m ? 3.0 + g2 : 5.0 - r2);

    h /= 6.0;

    return CHSL(h, s, l);
  }

  static CHSB RGBtoHSB(const CRGB &rgb) {
    CHSV hsv = RGBtoHSV(rgb);

    double hue        = hsv.getHue()/360.0;
    double saturation = hsv.getSaturation();
    double brightness = hsv.getValue();

    return CHSB(hue, saturation, brightness);
  }

  static CHSI RGBtoHSI(const CRGB &rgb) {
    double r = rgb.getRed();
    double g = rgb.getGreen();
    double b = rgb.getBlue();

    double rg = r - g;
    double rb = r - b;
    double gb = g - b;

    if (fabs(rg) < 1E-6 && fabs(rb) < 1E-6 && fabs(gb) < 1E-6)
      return CHSI(0.0, 0.0, r);

    // Hue
    double t = ::acos(0.5*(rg + rb)/::sqrt(rg*rg + rb*gb));

    if (b > g)
      t = 0.5*M_PI - t;

    double h = 2.0*t/M_PI;

    // Saturation
    double sum = r + g + b;

    // Intensity
    double i = sum/3.0;

    double s = 1.0 - std::min(r, std::min(g, b))/i;

    return CHSI(h, s, i);
  }

  static uint clampI(int v) {
    return uint(v >= 0 ? (v <= 255 ? v : 255) : 0);
  }

  //---

  struct LAB {
    double l, a, b;
  };

  // Convert sRGB to CIELAB (D65 illuminant)
  static LAB rgbToLab(const CRGBA &color) {
    // 1. Normalize and linearize sRGB
    auto pivotRgb = [](double c) {
      c /= 255.0;
      return (c > 0.04045) ? std::pow((c + 0.055) / 1.055, 2.4) : (c / 12.92);
    };

    double r = pivotRgb(color.r()) * 100.0;
    double g = pivotRgb(color.g()) * 100.0;
    double b = pivotRgb(color.b()) * 100.0;

    // 2. Convert RGB to XYZ
    double x = r * 0.4124564 + g * 0.3575761 + b * 0.1804375;
    double y = r * 0.2126729 + g * 0.7151522 + b * 0.0721750;
    double z = r * 0.0193339 + g * 0.1191920 + b * 0.9503041;

    // 3. Normalize for D65 white point and convert XYZ to LAB
    auto pivotXyz = [](double t) {
      return (t > 0.008856) ? std::cbrt(t) : (7.787 * t) + (16.0 / 116.0);
    };

    double fx = pivotXyz(x / 95.047);
    double fy = pivotXyz(y / 100.000);
    double fz = pivotXyz(z / 108.883);

    return { (116.0 * fy) - 16.0, 500.0 * (fx - fy), 200.0 * (fy - fz) };
  }

  // Calculate CIE76 Delta E
  static double colorDiff(const CRGBA &c1, const CRGBA &c2) {
    auto lab1 = rgbToLab(c1);
    auto lab2 = rgbToLab(c2);

    auto dl = lab1.l - lab2.l;
    auto da = lab1.a - lab2.a;
    auto db = lab1.b - lab2.b;

    return std::sqrt(dl*dl + da*da + db*db);
  }

  static void setColorCmpDelta(double d) {
    *colorCmpDeltaP() = d;
  }

  struct ColorCmp {
    bool operator()(const CRGBA &lhs, const CRGBA &rhs) const {
      auto d = colorDiff(lhs, rhs);

      return (d < *colorCmpDeltaP());
    }
  };

 private:
  static double *colorCmpDeltaP() {
    static double delta = 1.0;
    return &delta;
  }
};

#endif
