#ifndef CBRUSH_H
#define CBRUSH_H

#include <CRGBA.h>
#include <CBrushStyle.h>
#include <CFillType.h>
#include <CImageLib.h>
#include <CGenGradient.h>

enum class CBrushPattern {
  NONE,
  HORIZONTAL,
  VERTICAL,
  CROSS,
  DIAGONAL_UP,
  DIAGONAL_DOWN,
  DIAGONAL_CROSS,
  DOTTED1,
  DOTTED2,
  DOTTED3,
  DOTTED4,
  DOTTED5,
  DOTTED6,
  DOTTED7
};

class CBrush {
 public:
  using GradientPtr = CRefPtr<CGenGradient>;

 public:
  CBrush();

  explicit CBrush(const CRGBA &c);
  explicit CBrush(const CImagePtr &image);

 ~CBrush();

  CBrush &operator=(const CBrush &brush);

  CBrush &copy(const CBrush &brush);

  bool isValid() const { return style_ != CBRUSH_STYLE_NONE; }

  CBrushStyle getStyle() const { return style_; }

  const CRGBA &getColor() const { assert(style_ == CBRUSH_STYLE_SOLID); return color_; }

  CFillType getFillRule() const { return fill_rule_; }

  CBrushPattern getPattern () const { assert(style_ == CBRUSH_STYLE_PATTERN ); return pattern_ ; }
  CImagePtr     getTexture () const { assert(style_ == CBRUSH_STYLE_TEXTURE ); return texture_ ; }
  GradientPtr   getGradient() const { assert(style_ == CBRUSH_STYLE_GRADIENT); return gradient_; }

  void setStyle   (CBrushStyle style ) { style_ = style; }
  void setColor   (const CRGBA &color) { color_ = color; }
  void setFillRule(CFillType rule    ) { fill_rule_ = rule; }

  void setPattern (CBrushPattern pattern) { style_ = CBRUSH_STYLE_PATTERN ; pattern_  = pattern ; }
  void setTexture (CImagePtr texture    ) { style_ = CBRUSH_STYLE_TEXTURE ; texture_  = texture ; }
  void setGradient(GradientPtr gradient ) { style_ = CBRUSH_STYLE_GRADIENT; gradient_ = gradient; }

 private:
  CBrushStyle   style_     { CBRUSH_STYLE_SOLID };
  CRGBA         color_     { 0, 0, 0 };
  CFillType     fill_rule_ { FILL_TYPE_EVEN_ODD };
  CBrushPattern pattern_   { CBrushPattern::HORIZONTAL };
  CImagePtr     texture_;
  GradientPtr   gradient_;
};

#endif
