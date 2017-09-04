#ifndef CRGB_NAME_H
#define CRGB_NAME_H

#include <CRGBA.h>
#include <map>
#include <string>

class CRGBName {
 public:
  static bool lookup(const std::string &name, double *r, double *g, double *b, double *a=0);
  static bool lookup(const std::string &name, float *r, float *g, float *b, float *a=0);

  static bool lookupHtml(const std::string &name, double *r, double *g, double *b, double *a=0);
  static bool lookupHtml(const std::string &name, float *r, float *g, float *b, float *a=0);

  //---

  static bool toRGBA(const std::string &name, CRGBA &rgba) {
    double r, g, b, a;

    if (! lookup(name, &r, &g, &b, &a))
      return false;

    rgba = CRGBA(r, g, b, a);

    return true;
  }

  static CRGBA toRGBA(const std::string &name, const CRGBA &def=CRGBA(0, 0, 0)) {
    CRGBA rgba;

    if (! toRGBA(name, rgba))
      rgba = def;

    return rgba;
  }

  static CRGBA toRGBA(const std::string &name, double a, const CRGBA &def=CRGBA(0, 0, 0)) {
    CRGBA rgba;

    if (! toRGBA(name, rgba))
      rgba = def;

    rgba.setAlpha(a);

    return rgba;
  }

  //---

  static bool toHtmlRGBA(const std::string &name, CRGBA &rgba) {
    double r, g, b, a;

    if (! lookupHtml(name, &r, &g, &b, &a))
      return false;

    rgba = CRGBA(r, g, b, a);

    return true;
  }

  //---

  static bool toRGB(const std::string &name, CRGB &rgb) {
    double r, g, b;

    if (! lookup(name, &r, &g, &b))
      return false;

    rgb = CRGB(r, g, b);

    return true;
  }

  static CRGB toRGB(const std::string &name, const CRGB &def=CRGB(0, 0, 0)) {
    CRGB rgb;

    if (! toRGB(name, rgb))
      rgb = def;

    return rgb;
  }

  //---

  static int numColorNames();

  static std::string colorName(int i);
  static CRGBA       colorRGBA(int i);

 private:
  static bool lookupName(const std::string &name,
                         double *r, double *g, double *b, double *a, bool html);
  static bool lookupName(const std::string &name,
                         float *r, float *g, float *b, float *a, bool html);

 private:
  typedef std::map<std::string, int> ColorMap;

  static ColorMap html_colormap_;
  static ColorMap colormap_;
  static bool     colormapSet_;
};

#endif
