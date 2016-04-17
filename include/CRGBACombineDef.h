#ifndef CRGBACombineDef_H
#define CRGBACombineDef_H

#include <CRGBA.h>

struct CRGBACombineDef {
  CRGBACombineMode src_mode { CRGBA_COMBINE_SRC_ALPHA };
  CRGBACombineMode dst_mode { CRGBA_COMBINE_ONE_MINUS_SRC_ALPHA };
  CRGBACombineFunc func     { CRGBA_COMBINE_ADD };
  CRGBA            factor   { 0, 0, 0, 1 };
  double           k1       { 0.0 };
  double           k2       { 0.0 };
  double           k3       { 0.0 };
  double           k4       { 0.0 };

  CRGBACombineDef() { }

  CRGBA combine(const CRGBA &rgba1, const CRGBA &rgba2) const {
    if      (func == CRGBA_COMBINE_ARITHMETIC)
      return CRGBA::arithmeticCombine(rgba1, rgba2, k1, k2, k3, k4);
    else if (func == CRGBA_COMBINE_SRC       || func == CRGBA_COMBINE_ATOP ||
             func == CRGBA_COMBINE_OVER      || func == CRGBA_COMBINE_IN ||
             func == CRGBA_COMBINE_OUT       || func == CRGBA_COMBINE_DEST ||
             func == CRGBA_COMBINE_DEST_ATOP || func == CRGBA_COMBINE_DEST_OVER ||
             func == CRGBA_COMBINE_DEST_IN   || func == CRGBA_COMBINE_DEST_OUT ||
             func == CRGBA_COMBINE_CLEAR     || func == CRGBA_COMBINE_XOR)
      return CRGBA::porterDuffCombine(rgba1, rgba2, func);
    else
      return CRGBA::modeCombine(rgba1, rgba2, src_mode, dst_mode, func, factor);
  }
};

#endif
