#ifndef CColor_H
#define CColor_H

#include <CRGBA.h>
#include <CHSV.h>
#include <CRGBUtil.h>

// wrapper around RGB, HSV colors
class CColor {
 public:
  enum class Type {
    NONE,
    RGB,
    HSV
  };

 public:
  CColor() { }

  CColor(const CRGB &rgb, double a=1.0) {
    setRGB(rgb.getRed(), rgb.getGreen(), rgb.getBlue());

    setAlpha(a);
  }

  CColor(const CRGBA &rgba) {
    setRGB(rgba.getRed(), rgba.getGreen(), rgba.getBlue());

    setAlpha(rgba.getAlpha());
  }

  CColor(const CHSV &hsv, double a=1.0) {
    setHSV(hsv.getHue()/360.0, hsv.getSaturation(), hsv.getValue());

    setAlpha(a);
  }

  CColor(const CColor &c) {
    type_ = c.type_;

    if      (type_ == Type::RGB) {
      RGB *rgb = static_cast<RGB *>(c.component_);

      setRGB(rgb->r(), rgb->g(), rgb->b());
    }
    else if (type_ == Type::HSV) {
      HSV *hsv = static_cast<HSV *>(c.component_);

      setHSV(hsv->h(), hsv->s(), hsv->v());
    }

    alpha_ = c.alpha_;
  }

 ~CColor() {
    delete component_;
  }

  CColor &operator=(const CColor &c) {
    type_ = c.type_;

    if (type_ == Type::NONE) {
      delete component_;

      component_ = 0;
    }

    if      (type_ == Type::RGB) {
      RGB *rgb = static_cast<RGB *>(c.component_);

      setRGB(rgb->r(), rgb->g(), rgb->b());
    }
    else if (type_ == Type::HSV) {
      HSV *hsv = static_cast<HSV *>(c.component_);

      setHSV(hsv->h(), hsv->s(), hsv->v());
    }

    alpha_ = c.alpha_;

    return *this;
  }

  const Type &type() const { return type_; }

  double alpha() const { return alpha_; }
  void setAlpha(double a) { alpha_ = a; };

  void setRGB(double r, double g, double b) {
    if (! component_) component_ = new Component;

    type_ = Type::RGB;

    RGB *rgb = static_cast<RGB *>(component_);

    rgb->setRgb(r, g, b);
  }

  void setHSV(double h, double s, double v) {
    if (! component_) component_ = new Component;

    type_ = Type::HSV;

    HSV *hsv = static_cast<HSV *>(component_);

    hsv->setHsv(h, s, v);
  }

  CRGB rgb() const {
    if (type_ == Type::NONE) return CRGB();

    if (type_ == Type::HSV) {
      HSV *hsv = static_cast<HSV *>(component_);

      return CRGBUtil::HSVtoRGB(hsv->hsv());
    }

    RGB *rgb = static_cast<RGB *>(component_);

    return rgb->rgb();
  }

  CRGBA rgba() const {
    CRGB rgb = this->rgb();

    return CRGBA(rgb, alpha_);
  }

  CHSV hsv() const {
    if (type_ == Type::NONE) return CHSV();

    if (type_ == Type::RGB) {
      RGB *rgb = static_cast<RGB *>(component_);

      return CRGBUtil::RGBtoHSV(rgb->rgb());
    }

    HSV *hsv = static_cast<HSV *>(component_);

    return hsv->hsv();
  }

  static CColor interp(const CColor &bg, const CColor &fg, double f) {
    if (bg.type_ == Type::NONE && fg.type_ == Type::NONE) return CColor();

    if (bg.type_ == Type::NONE) return fg;
    if (fg.type_ == Type::NONE) return bg;

    if      (bg.type_ == fg.type_) {
      if      (bg.type_ == Type::RGB) {
        CRGB rgb = (1.0 - f)*bg.rgb() + f*fg.rgb();

        return CColor(rgb);
      }
      else if (fg.type_ == Type::HSV) {
        CHSV hsv = (1.0 - f)*bg.hsv() + f*fg.hsv();

        return CColor(hsv);
      }
      else
        return CColor();
    }
    else if (bg.type_ == Type::HSV)
      return interp(bg.rgb(), fg, f);
    else if (fg.type_ == Type::HSV)
      return interp(bg, fg.rgb(), f);
    else
      return CColor();
  }

 private:
  class Component {
   public:
    Component() { }

   protected:
    Component(double v1, double v2, double v3) :
     c1(v1), c2(v2), c3(v3) {
    }

   protected:
    double c1 { 1.0 };
    double c2 { 1.0 };
    double c3 { 1.0 };
  };

  class RGB : public Component {
   public:
    RGB() { }

    RGB(double r, double g, double b) :
     Component(r, g, b) {
    }

    double r() const { return c1; };
    double g() const { return c2; }
    double b() const { return c3; }

    void setRgb(double r, double g, double b) {
      c1 = r; c2 = g; c3 = b;
    }

    CRGB rgb() { return CRGB(c1, c2, c3); }
  };

  class HSV : public Component {
   public:
    HSV() { }

    HSV(double h, double s, double v) :
     Component(h, s, v) {
    }

    double h() const { return c1; };
    double s() const { return c2; }
    double v() const { return c3; }

    void setHsv(double h, double s, double v) {
      c1 = h; c2 = s; c3 = v;
    }

    CHSV hsv() { return CHSV(c1*360.0, c2, c3); }
  };

  Type       type_      { Type::NONE };
  Component *component_ { 0 };
  double     alpha_     { 1.0 };
};

#endif
