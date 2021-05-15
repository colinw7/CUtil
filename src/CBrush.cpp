#include <CBrush.h>

#ifdef CBRUSH_IMAGE
#include <CImageLib.h>
#endif

CBrush::
CBrush()
{
}

CBrush::
CBrush(const CBrush &brush)
{
  copy(brush);
}

CBrush::
CBrush(const CRGBA &c) :
 style_(CBRUSH_STYLE_SOLID), color_(c)
{
}

#ifdef CBRUSH_IMAGE
CBrush::
CBrush(const CImagePtr &image) :
 style_(CBRUSH_STYLE_TEXTURE), texture_(image)
{
}
#endif

CBrush::
~CBrush()
{
}

CBrush &
CBrush::
operator=(const CBrush &brush)
{
  return copy(brush);
}

CBrush &
CBrush::
copy(const CBrush &brush)
{
  if (&brush == this)
    return *this;

  style_     = brush.style_;
  color_     = brush.color_;
  fill_rule_ = brush.fill_rule_;
  pattern_   = brush.pattern_;
#ifdef CBRUSH_IMAGE
  texture_   = brush.texture_;
#endif
  gradient_  = brush.gradient_;

  return *this;
}
