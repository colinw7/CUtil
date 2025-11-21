#ifndef CGLColor_H
#define CGLColor_H

struct CGLColor {
  CGLColor() = default;

  CGLColor(float r_, float g_, float b_, float a_=1.0) :
   r(r_), g(g_), b(b_), a(a_) {
  }

  float r { 0.0f };
  float g { 0.0f };
  float b { 0.0f };
  float a { 1.0f };
};

#endif
