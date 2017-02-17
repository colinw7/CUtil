#ifndef CBRUSH_H
#define CBRUSH_H

#include <CRGBA.h>
#include <CBrushStyle.h>
#include <CFillType.h>
#include <CImage.h>
#include <CAutoPtr.h>
#include <CGenGradient.h>

enum CBrushPattern {
  CBRUSH_PATTERN_NONE,
  CBRUSH_PATTERN_HORIZONTAL,
  CBRUSH_PATTERN_VERTICAL,
  CBRUSH_PATTERN_CROSS,
  CBRUSH_PATTERN_DIAGONAL_UP,
  CBRUSH_PATTERN_DIAGONAL_DOWN,
  CBRUSH_PATTERN_DIAGONAL_CROSS,
  CBRUSH_PATTERN_DOTTED1,
  CBRUSH_PATTERN_DOTTED2,
  CBRUSH_PATTERN_DOTTED3,
  CBRUSH_PATTERN_DOTTED4,
  CBRUSH_PATTERN_DOTTED5,
  CBRUSH_PATTERN_DOTTED6,
  CBRUSH_PATTERN_DOTTED7
};

class CBrush {
 public:
  typedef CRefPtr<CGenGradient> GradientPtr;

 public:
  CBrush() { }

  explicit CBrush(const CRGBA &c) :
   style_(CBRUSH_STYLE_SOLID), color_(c) {
  }

  explicit CBrush(const CImagePtr &image) :
   style_(CBRUSH_STYLE_TEXTURE), texture_(image) {
  }

  CBrush &operator=(const CBrush &brush) {
    return copy(brush);
  }

  CBrush &copy(const CBrush &brush) {
    if (&brush == this)
      return *this;

    style_     = brush.style_;
    color_     = brush.color_;
    fill_rule_ = brush.fill_rule_;
    pattern_   = brush.pattern_;
    texture_   = brush.texture_;
    gradient_  = brush.gradient_;

    return *this;
  }

  CBrushStyle getStyle() const { return style_; }

  const CRGBA& getColor() const { assert(style_ == CBRUSH_STYLE_SOLID); return color_; }

  CFillType getFillRule() const { return fill_rule_; }

  CBrushPattern getPattern () const { assert(style_ == CBRUSH_STYLE_PATTERN ); return pattern_ ; }
  CImagePtr     getTexture () const { assert(style_ == CBRUSH_STYLE_TEXTURE ); return texture_ ; }
  GradientPtr   getGradient() const { assert(style_ == CBRUSH_STYLE_GRADIENT); return gradient_; }

  void setStyle   (CBrushStyle style    ) { style_ = style; }
  void setColor   (const CRGBA &color   ) { color_ = color; }
  void setFillRule(CFillType rule       ) { fill_rule_ = rule; }

  void setPattern (CBrushPattern pattern) { style_ = CBRUSH_STYLE_PATTERN ; pattern_  = pattern ; }
  void setTexture (CImagePtr texture    ) { style_ = CBRUSH_STYLE_TEXTURE ; texture_  = texture ; }
  void setGradient(GradientPtr gradient ) { style_ = CBRUSH_STYLE_GRADIENT; gradient_ = gradient; }

 private:
  CBrushStyle   style_ { CBRUSH_STYLE_SOLID };
  CRGBA         color_ { 0, 0, 0 };
  CFillType     fill_rule_ { FILL_TYPE_EVEN_ODD };
  CBrushPattern pattern_ { CBRUSH_PATTERN_HORIZONTAL };
  CImagePtr     texture_;
  GradientPtr   gradient_;
};

#endif
