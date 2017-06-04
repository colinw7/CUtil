#ifndef CPEN_H
#define CPEN_H

#include <CRGBA.h>
#include <CLineDash.h>
#include <CILineDash.h>
#include <CLineCapType.h>
#include <CLineJoinType.h>

class CPen {
 public:
  CPen() {
    init();
  }

  explicit CPen(const CRGBA &c) :
   color_(c) {
    init();
  }

  CPen(const CPen &pen) {
    init();

    copy(pen);
  }

  CPen &operator=(const CPen &pen) {
    return copy(pen);
  }

  void init() {
    dash_.init();
  }

  CPen &copy(const CPen &pen) {
    if (&pen == this)
      return *this;

    color_       = pen.color_;
    width_       = pen.width_;
    dash_        = pen.dash_;
    cap_         = pen.cap_;
    join_        = pen.join_;
    mitre_limit_ = pen.mitre_limit_;
    flatness_    = pen.flatness_;

    return *this;
  }

  bool isValid() const { return width_ > 0.0; }

  const CRGBA     &getColor     () const { return color_      ; }
  double           getWidth     () const { return width_      ; }
  const CLineDash &getLineDash  () const { return dash_       ; }
  CLineCapType     getLineCap   () const { return cap_        ; }
  CLineJoinType    getLineJoin  () const { return join_       ; }
  double           getMitreLimit() const { return mitre_limit_; }
  double           getFlatness  () const { return flatness_   ; }

  void setColor     (const CRGBA     &color   ) { color_       = color; }
  void setWidth     (double           width   ) { width_       = width; }
  void setLineDash  (const CLineDash &dash    ) { dash_        = dash; }
  void setLineCap   (CLineCapType     cap     ) { cap_         = cap; }
  void setLineJoin  (CLineJoinType    join    ) { join_        = join; }
  void setMitreLimit(double           mitre   ) { mitre_limit_ = mitre; }
  void setFlatness  (double           flatness) { flatness_    = flatness; }

 private:
  CRGBA         color_ { 0, 0, 0 };
  double        width_ { 1.0 };
  CLineDash     dash_;
  CLineCapType  cap_ { LINE_CAP_TYPE_BUTT };
  CLineJoinType join_ { LINE_JOIN_TYPE_MITRE };
  double        mitre_limit_ { 0.0 };
  double        flatness_ { 0.0 };
};

//-------

class CIPen {
 public:
  CIPen() {
    init();
  }

  CIPen(const CIPen &pen) {
    init();

    copy(pen);
  }

  CIPen &operator=(const CIPen &pen) {
    return copy(pen);
  }

  void init() {
    dash_.init();
  }

  CIPen &copy(const CIPen &pen) {
    if (&pen == this)
      return *this;

    color_       = pen.color_;
    width_       = pen.width_;
    dash_        = pen.dash_;
    cap_         = pen.cap_;
    join_        = pen.join_;
    mitre_limit_ = pen.mitre_limit_;
    flatness_    = pen.flatness_;

    return *this;
  }

  const CRGBA      &getColor     () const { return color_      ; }
  uint              getWidth     () const { return width_      ; }
  const CILineDash &getLineDash  () const { return dash_       ; }
  CLineCapType      getLineCap   () const { return cap_        ; }
  CLineJoinType     getLineJoin  () const { return join_       ; }
  double            getMitreLimit() const { return mitre_limit_; }
  double            getFlatness  () const { return flatness_   ; }

  void setColor     (const CRGBA      &color   ) { color_       = color; }
  void setWidth     (uint              width   ) { width_       = width; }
  void setLineDash  (const CILineDash &dash    ) { dash_        = dash; }
  void setLineCap   (CLineCapType      cap     ) { cap_         = cap; }
  void setLineJoin  (CLineJoinType     join    ) { join_        = join; }
  void setMitreLimit(double            mitre   ) { mitre_limit_ = mitre; }
  void setFlatness  (double            flatness) { flatness_    = flatness; }

 private:
  CRGBA         color_ { 0, 0, 0 };
  uint          width_ { 1 };
  CILineDash    dash_;
  CLineCapType  cap_ { LINE_CAP_TYPE_BUTT };
  CLineJoinType join_ { LINE_JOIN_TYPE_MITRE };
  double        mitre_limit_ { 0.0 };
  double        flatness_ { 0.0 };
};

#endif
