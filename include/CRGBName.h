#ifndef CRGB_NAME_H
#define CRGB_NAME_H

#include <CRGBA.h>
#include <map>
#include <string>

class CRGBName {
 public:
  static bool lookup(const std::string &name, double *r, double *g, double *b, double *a=0);
  static bool lookup(const std::string &name, float *r, float *g, float *b, float *a=0);

  static bool toRGBA(const std::string &name, CRGBA &rgba) {
    double r, g, b, a;

    if (! lookup(name, &r, &g, &b, &a))
      return false;

    rgba = CRGBA(r, g, b, a);

    return true;
  }

  static bool toRGB(const std::string &name, CRGB &rgb) {
    double r, g, b;

    if (! lookup(name, &r, &g, &b))
      return false;

    rgb = CRGB(r, g, b);

    return true;
  }

  static CRGBA toRGBA(const std::string &name) {
    CRGBA rgba;

    if (! toRGBA(name, rgba))
      rgba = CRGBA(0, 0, 0);

    return rgba;
  }

  static CRGB toRGB(const std::string &name) {
    CRGB rgb;

    if (! toRGB(name, rgb))
      rgb = CRGB(0, 0, 0);

    return rgb;
  }

  static int numColorNames();

  static std::string colorName(int i);
  static CRGBA       colorRGBA(int i);

 private:
  typedef std::map<std::string, int> ColorMap;

  static ColorMap colormap_;
  static bool     colormapSet_;
};

#endif
