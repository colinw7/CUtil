#ifndef CQBrush_H
#define CQBrush_H

#include <QBrush>

class CQBrush {
 public:
  CQBrush() { }

  explicit CQBrush(const QColor &c) :
   style_(Qt::SolidPattern), color_(c) {
  }

  explicit CQBrush(const QImage &image) :
   style_(Qt::TexturePattern), texture_(image) {
  }

  CQBrush &operator=(const CQBrush &brush) {
    return copy(brush);
  }

  CQBrush &copy(const CQBrush &brush) {
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

  bool isValid() const { return style_ != CQBRUSH_STYLE_NONE; }

  Qt::BrushStyle getStyle() const { return style_; }

  const QColor &getColor() const { assert(style_ == Qt::SolidPattern); return color_; }

  Qt::FillRule getFillRule() const { return fill_rule_; }

  Qt::BrushStyle   getPattern () const {
    assert(style_ == Qt::Dense1Pattern ); return pattern_ ; }
  const QImage&    getTexture () const {
    assert(style_ == Qt::TexturePattern ); return texture_ ; }
  const QGradient& getGradient() const {
    assert(style_ == Qt::LinearGradientPattern); return gradient_; }

  void setStyle   (Qt::BrushStyle style) { style_ = style; }
  void setColor   (const QColor &color ) { color_ = color; }
  void setFillRule(Qt::FillRule rule   ) { fill_rule_ = rule; }

  void setPattern (Qt::BrushStyle pattern) {
    style_ = Qt::Dense1Pattern        ; pattern_  = pattern ; }
  void setTexture (const QImage &texture) {
    style_ = Qt::TexturePattern       ; texture_  = texture ; }
  void setGradient(const QGradient &gradient)  {
    style_ = Qt::LinearGradientPattern; gradient_ = gradient; }

 private:
  Qt::BrushStyle style_     { Qt::SolidPattern };
  QColor         color_     { 0, 0, 0 };
  Qt::FillRule   fill_rule_ { Qt::OddEvenFill };
  Qt::BrushStyle pattern_   { Qt::HorPattern };
  QImage         texture_;
  QGradient      gradient_;
};

#endif
