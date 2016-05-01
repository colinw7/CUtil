#ifndef CRGBA_H
#define CRGBA_H

#include <cassert>

#include <CRGB.h>

#ifdef USE_CRGB_NAME
#include <CRGBName.h>
#endif

#include <CColorComponent.h>

#define CRGBA_LIGHT_FACTOR 1.25
#define CRGBA_DARK_FACTOR  0.50

#define CRGBA_R_FACTOR 0.3
#define CRGBA_G_FACTOR 0.59
#define CRGBA_B_FACTOR 0.11

#define CRGBA_SEPIA_R1  0.299
#define CRGBA_SEPIA_G1  0.587
#define CRGBA_SEPIA_B1  0.114

#define CRGBA_SEPIA_R2  0.191
#define CRGBA_SEPIA_G2 -0.054
#define CRGBA_SEPIA_B2 -0.221

#define CRGBA_IFACTOR  255.0
#define CRGBA_IFACTORI (1.0/255.0)

enum CRGBACombineMode {
  CRGBA_COMBINE_ZERO                    ,
  CRGBA_COMBINE_ONE                     ,
  CRGBA_COMBINE_DST_COLOR               ,
  CRGBA_COMBINE_SRC_COLOR               ,
  CRGBA_COMBINE_ONE_MINUS_DST_COLOR     ,
  CRGBA_COMBINE_ONE_MINUS_SRC_COLOR     ,
  CRGBA_COMBINE_SRC_ALPHA               ,
  CRGBA_COMBINE_ONE_MINUS_SRC_ALPHA     ,
  CRGBA_COMBINE_DST_ALPHA               ,
  CRGBA_COMBINE_ONE_MINUS_DST_ALPHA     ,
  CRGBA_COMBINE_SRC_ALPHA_SATURATE      ,
  CRGBA_COMBINE_DST_ALPHA_SATURATE      ,
  CRGBA_COMBINE_CONSTANT_COLOR          ,
  CRGBA_COMBINE_ONE_MINUS_CONSTANT_COLOR,
  CRGBA_COMBINE_CONSTANT_ALPHA          ,
  CRGBA_COMBINE_ONE_MINUS_CONSTANT_ALPHA
};

enum CRGBACombineFunc {
  CRGBA_COMBINE_ADD             ,
  CRGBA_COMBINE_SUBTRACT        ,
  CRGBA_COMBINE_REVERSE_SUBTRACT,
  CRGBA_COMBINE_MULTIPLY        ,
  CRGBA_COMBINE_MIN             ,
  CRGBA_COMBINE_MAX             ,

  CRGBA_COMBINE_OVER            ,
  CRGBA_COMBINE_IN              ,
  CRGBA_COMBINE_OUT             ,
  CRGBA_COMBINE_ATOP            ,
  CRGBA_COMBINE_XOR             ,
  CRGBA_COMBINE_ARITHMETIC      ,
  CRGBA_COMBINE_SRC             ,
  CRGBA_COMBINE_DEST            ,
  CRGBA_COMBINE_DEST_ATOP       ,
  CRGBA_COMBINE_DEST_OVER       ,
  CRGBA_COMBINE_DEST_IN         ,
  CRGBA_COMBINE_DEST_OUT        ,
  CRGBA_COMBINE_CLEAR           ,
};

enum CRGBABlendMode {
  CRGBA_BLEND_NORMAL,
  CRGBA_BLEND_MULTIPLY,
  CRGBA_BLEND_SCREEN,
  CRGBA_BLEND_DARKEN,
  CRGBA_BLEND_LIGHTEN
};

template<typename T>
class CRGBAT {
 private:
  typedef CRGBT<T>     RGB;
  typedef CRGBUtilT<T> Util;

  typedef uint (*IdProc)(T r, T g, T b, T a);

 public:
  struct IValT { };

  static IdProc setIdProc(IdProc proc) {
    static IdProc id_proc_ = defIdProc;

    if (proc)
      id_proc_ = proc;

    return id_proc_;
  }

  static uint defIdProc(T r, T g, T b, T a) {
    return encodeARGB(uint(r*255), uint(g*255), uint(b*255), uint(a*255));
  }

  static uint calcId(T r, T g, T b, T a) {
    IdProc id_proc = setIdProc(0);

    return id_proc(r, g, b, a);
  }

  static const IValT &IVal() { static IValT ival; return ival; }

  static CRGBAT fromRGBAI(int r, int g, int b, int a=255) {
    return CRGBAT(r/255.0, g/255.0, b/255.0, a/255.0);
  }

  //-------

  CRGBAT() :
   r_(0.0), g_(0.0), b_(0.0), a_(0.0), id_(0), id_set_(false) {
  }

  CRGBAT(T r, T g, T b, T a=1.0) :
   r_(r), g_(g), b_(b), a_(a), id_(0), id_set_(false) {
  }

  explicit CRGBAT(T gray, T a=1.0) :
   r_(gray), g_(gray), b_(gray), a_(a), id_(0), id_set_(false) {
  }

  CRGBAT(const IValT &, int r, int g, int b, int a=255) :
   r_(r/255.0), g_(g/255.0), b_(b/255.0), a_(a/255.0), id_(0), id_set_(false) {
  }

#ifdef USE_CRGB_NAME
  explicit CRGBAT(const std::string &name) :
   r_(0), g_(0), b_(0), a_(0), id_(0), id_set_(false) {
    CRGBName::lookup(name, &r_, &g_, &b_, &a_);
  }

  explicit CRGBAT(const std::string &name, double a) :
   id_(0), id_set_(false) {
    CRGBName::lookup(name, &r_, &g_, &b_, &a_);

    a_ = a;
  }
#endif

  CRGBAT(const CRGBAT &rgba) :
   r_(rgba.r_), g_(rgba.g_), b_(rgba.b_), a_(rgba.a_), id_(rgba.id_), id_set_(rgba.id_set_) {
  }

  CRGBAT(const RGB &rgb, double a=1.0) :
   r_(rgb.getRed()), g_(rgb.getGreen()), b_(rgb.getBlue()), a_(a), id_(0), id_set_(false) {
  }

 ~CRGBAT() { }

  CRGBAT &operator=(const CRGBAT &rgba) {
    if (&rgba == this)
      return *this;

    r_ = rgba.r_; g_ = rgba.g_; b_ = rgba.b_; a_ = rgba.a_;

    id_ = rgba.id_; id_set_ = rgba.id_set_;

    return *this;
  }

  CRGBAT &operator=(const RGB &rgb) {
    r_ = rgb.getRed  ();
    g_ = rgb.getGreen();
    b_ = rgb.getBlue ();
    a_ = 1.0;

    id_set_ = false;

    return *this;
  }

  CRGBAT operator+() const {
    return *this;
  }

  CRGBAT operator-() const {
    return CRGBAT(-r_, -g_, -b_, a_);
  }

  CRGBAT &operator+=(T rhs) {
    r_ += rhs;
    g_ += rhs;
    b_ += rhs;

    id_set_ = false;

    return *this;
  }

  CRGBAT &operator+=(const CRGBAT &rhs) {
    r_ += rhs.r_;
    g_ += rhs.g_;
    b_ += rhs.b_;
    a_ += rhs.a_;

    id_set_ = false;

    return *this;
  }

  CRGBAT operator+(T rhs) const {
    CRGBAT t = *this;

    t += rhs;

    return t;
  }

  CRGBAT operator+(const CRGBAT &rhs) const {
    CRGBAT t = *this;

    t += rhs;

    return t;
  }

  CRGBAT &operator-=(T rhs) {
    r_ -= rhs;
    g_ -= rhs;
    b_ -= rhs;

    id_set_ = false;

    return *this;
  }

  CRGBAT &operator-=(const CRGBAT &rhs) {
    r_ -= rhs.r_;
    g_ -= rhs.g_;
    b_ -= rhs.b_;
    a_ -= rhs.a_;

    id_set_ = false;

    return *this;
  }

  CRGBAT operator-(T rhs) const {
    CRGBAT t = *this;

    t -= rhs;

    return t;
  }

  CRGBAT operator-(const CRGBAT &rhs) const {
    CRGBAT t = *this;

    t -= rhs;

    return t;
  }

  CRGBAT &operator*=(T rhs) {
    r_ *= rhs;
    g_ *= rhs;
    b_ *= rhs;
    a_ *= rhs;

    id_set_ = false;

    return *this;
  }

  CRGBAT &operator*=(const CRGBAT &rhs) {
    r_ *= rhs.r_;
    g_ *= rhs.g_;
    b_ *= rhs.b_;
    a_ *= rhs.a_;

    id_set_ = false;

    return *this;
  }

  CRGBAT operator*(const CRGBAT &rhs) const {
    CRGBAT t = *this;

    t *= rhs;

    return t;
  }

  CRGBAT &operator/=(T rhs) {
    T irhs = 1.0/rhs;

    r_ *= irhs;
    g_ *= irhs;
    b_ *= irhs;
    a_ *= irhs;

    id_set_ = false;

    return *this;
  }

  CRGBAT &operator/=(const CRGBAT &rhs) {
    r_ /= rhs.r_;
    g_ /= rhs.g_;
    b_ /= rhs.b_;
    a_ /= rhs.a_;

    id_set_ = false;

    return *this;
  }

  CRGBAT operator/(T rhs) const {
    CRGBAT t = *this;

    t /= rhs;

    return t;
  }

  CRGBAT operator/(const CRGBAT &rhs) const {
    CRGBAT t = *this;

    t /= rhs;

    return t;
  }

  //------

  friend bool operator< (const CRGBAT &lhs, const CRGBAT &rhs) {
    return (lhs.getId() < rhs.getId());
  }

  friend bool operator<=(const CRGBAT &lhs, const CRGBAT &rhs) {
    return (lhs.getId() <= rhs.getId());
  }

  friend bool operator> (const CRGBAT &lhs, const CRGBAT &rhs) {
    return (lhs.getId() > rhs.getId());
  }

  friend bool operator>=(const CRGBAT &lhs, const CRGBAT &rhs) {
    return (lhs.getId() >= rhs.getId());
  }

  friend bool operator==(const CRGBAT &lhs, const CRGBAT &rhs) {
    return (lhs.getId() == rhs.getId());
  }

  friend bool operator!=(const CRGBAT &lhs, const CRGBAT &rhs) {
    return ! (lhs.getId() == rhs.getId());
  }

  //------

  friend bool operator==(const CRGBAT &lhs, const RGB &rhs) {
    return (lhs.getId() == calcId(rhs.r, rhs.g, rhs.b, 1.0));
  }

  friend bool operator!=(const CRGBAT &lhs, const RGB &rhs) {
    return ! (lhs.getId() == calcId(rhs.r, rhs.g, rhs.b, 1.0));
  }

  //------

  friend CRGBAT operator*(const CRGBAT &lhs, T rhs) {
    return CRGBAT(lhs.r_*rhs, lhs.g_*rhs, lhs.b_*rhs, lhs.a_*rhs);
  }

  friend CRGBAT operator*(T lhs, const CRGBAT &rhs) {
    return CRGBAT(lhs*rhs.r_, lhs*rhs.g_, lhs*rhs.b_, lhs*rhs.a_);
  }

  void print(std::ostream &os) const {
    os << "CRGBA(" << r_ << "," << g_ << "," << b_ << "," << a_ << ")";
  }

  friend std::ostream &operator<<(std::ostream &os, const CRGBAT &rgba) {
    rgba.print(os);

    return os;
  }

  std::string toString() const {
    uint r, g, b, a;

    getRGBAI(&r, &g, &b, &a);

    char str[256];

    ::sprintf(str, "(%u,%u,%u,%u)", r, g, b, a);

    return str;
  }

  std::string stringEncode() const {
    uint r, g, b, a;

    getRGBAI(&r, &g, &b, &a);

    char str[256];

    ::sprintf(str, "#%02x%02x%02x%02x", r, g, b, a);

    return str;
  }

  CRGBAT &zero() {
    r_ = g_ = b_ = a_ = 0.0;

    id_set_ = false;

    return *this;
  }

  CRGBAT &setRed  (T r) { r_ = r; id_set_ = false; return *this; }
  CRGBAT &setGreen(T g) { g_ = g; id_set_ = false; return *this; }
  CRGBAT &setBlue (T b) { b_ = b; id_set_ = false; return *this; }
  CRGBAT &setAlpha(T a) { a_ = a; id_set_ = false; return *this; }

  CRGBAT &setGray(T g) {
    r_ = g; g_ = g; b_ = g;

    id_set_ = false;

    return *this;
  }

#ifdef USE_CRGB_NAME
  bool setName(const std::string &name) {
    double r, g, b, a;

    if (! CRGBName::lookup(name, &r, &g, &b, &a))
      return false;

    r_ = r; g_ = g; b_ = b; a_ = a;

    id_set_ = false;

    return true;
  }
#endif

  CRGBAT &scaleRGB(T f) {
    r_ *= f;
    g_ *= f;
    b_ *= f;

    id_set_ = false;

    return *this;
  }

  CRGBAT &scaleAlpha(T a) {
    a_ *= a;

    id_set_ = false;

    return *this;
  }

  CRGBAT &setRGB(T r, T g, T b) {
    r_ = r; g_ = g; b_ = b;

    id_set_ = false;

    return *this;
  }

  CRGBAT &setRGB(const RGB &rgb) {
    r_ = rgb.getRed();
    g_ = rgb.getGreen();
    b_ = rgb.getBlue();

    id_set_ = false;

    return *this;
  }

  CRGBAT &setRGBA(T r, T g, T b, T a=1.0) {
    r_ = r; g_ = g; b_ = b; a_ = a;

    id_set_ = false;

    return *this;
  }

  CRGBAT &setRGBA(const CRGBAT &rgba) {
    r_ = rgba.r_; g_ = rgba.g_; b_ = rgba.b_; a_ = rgba.a_;

    id_set_ = false;

    return *this;
  }

  CRGBAT &setGrayI(uint ig, uint ia=255) {
    return setGray(ig*CRGBA_IFACTORI, ia);
  }

  CRGBAT &setRGBAI(uint ir, uint ig, uint ib, uint ia=255) {
    return setRGBA(ir*CRGBA_IFACTORI, ig*CRGBA_IFACTORI, ib*CRGBA_IFACTORI, ia*CRGBA_IFACTORI);
  }

  RGB getRGB() const {
    return RGB(r_, g_, b_);
  }

  void getRGBA(T *r, T *g, T *b, T *a) const {
    *r = r_; *g = g_; *b = b_; *a = a_;
  }

  void getRGBAI(uint *r, uint *g, uint *b, uint *a) const {
    *r = uint(r_*CRGBA_IFACTOR);
    *g = uint(g_*CRGBA_IFACTOR);
    *b = uint(b_*CRGBA_IFACTOR);
    *a = uint(a_*CRGBA_IFACTOR);
  }

  T getRed  () const { return r_; }
  T getGreen() const { return g_; }
  T getBlue () const { return b_; }
  T getAlpha() const { return a_; }

  uint getRedI  () const { return Util::clampI(r_*CRGBA_IFACTOR); }
  uint getGreenI() const { return Util::clampI(g_*CRGBA_IFACTOR); }
  uint getBlueI () const { return Util::clampI(b_*CRGBA_IFACTOR); }
  uint getAlphaI() const { return Util::clampI(a_*CRGBA_IFACTOR); }

  T getComponent(CColorComponent component) const {
    switch (component) {
      case CCOLOR_COMPONENT_RED  : return r_;
      case CCOLOR_COMPONENT_GREEN: return g_;
      case CCOLOR_COMPONENT_BLUE : return b_;
      case CCOLOR_COMPONENT_ALPHA: return a_;
      default: assert(false);      return 0.0;
    }
  }

  void setComponent(CColorComponent component, double value) {
    switch (component) {
      case CCOLOR_COMPONENT_RED  : r_ = value; break;
      case CCOLOR_COMPONENT_GREEN: g_ = value; break;
      case CCOLOR_COMPONENT_BLUE : b_ = value; break;
      case CCOLOR_COMPONENT_ALPHA: a_ = value; break;
      default: assert(false); break;
    }
  }

  uint getId() const {
    if (! id_set_) {
      CRGBAT *th = const_cast<CRGBAT *>(this);

      th->id_ = calcId(r_, g_, b_, a_);

      th->id_set_ = true;
    }

    return id_;
  }

  T getClampRed() const {
    return std::max(0.0, std::min(1.0, r_));
  }

  T getClampGreen() const {
    return std::max(0.0, std::min(1.0, g_));
  }

  T getClampBlue() const {
    return std::max(0.0, std::min(1.0, b_));
  }

  T getClampAlpha() const {
    return std::max(0.0, std::min(1.0, a_));
  }

  T getGray() const {
    return (CRGBA_R_FACTOR*r_ + CRGBA_G_FACTOR*g_ + CRGBA_B_FACTOR*b_);
  }

  uint getGrayI() const {
    return uint(getGray()*CRGBA_IFACTOR);
  }

  T getClampGray() const {
    return clamped().getGray();
  }

  CRGBAT getGrayRGBA() const {
    T gray = getGray();

    return CRGBAT(gray, gray, gray, a_);
  }

  T getIntensity() const {
    return std::max(r_, std::max(g_, b_));
  }

  //---

  T getLightRed(double f=CRGBA_LIGHT_FACTOR) const {
    return std::min(r_*f, 1.0);
  }

  T getLightGreen(double f=CRGBA_LIGHT_FACTOR) const {
    return std::min(g_*f, 1.0);
  }

  T getLightBlue(double f=CRGBA_LIGHT_FACTOR) const {
    return std::min(b_*f, 1.0);
  }

  T getLightGray(double f=CRGBA_LIGHT_FACTOR) const {
    T gray = getGray();

    return std::min(gray*f, 1.0);
  }

  CRGBAT getLightRGBA(double f=CRGBA_LIGHT_FACTOR) const {
    return CRGBAT(getLightRed(f), getLightGreen(f), getLightBlue(f), a_);
  }

  //---

  T getDarkRed(double f=CRGBA_DARK_FACTOR) const {
    return std::min(r_*f, 1.0);
  }

  T getDarkGreen(double f=CRGBA_DARK_FACTOR) const {
    return std::min(g_*f, 1.0);
  }

  T getDarkBlue(double f=CRGBA_DARK_FACTOR) const {
    return std::min(b_*f, 1.0);
  }

  T getDarkGray(double f=CRGBA_DARK_FACTOR) const {
    T gray = getGray();

    return std::min(gray*f, 1.0);
  }

  CRGBAT getDarkRGBA(double f=CRGBA_DARK_FACTOR) const {
    return CRGBAT(getDarkRed(f), getDarkGreen(f), getDarkBlue(f), a_);
  }

  //---

  T getInverseRed() const {
    return 1.0 - r_;
  }

  T getInverseGreen() const {
    return 1.0 - g_;
  }

  T getInverseBlue() const {
    return 1.0 - b_;
  }

  T getInverseGray() const {
    T gray = getGray();

    return 1.0 - gray;
  }

  CRGBAT getInverseRGBA() const {
    return CRGBAT(getInverseRed(), getInverseGreen(), getInverseBlue(), a_);
  }

  const CRGBAT &toGray() {
    T gray = getGray();

    r_ = gray;
    g_ = gray;
    b_ = gray;

    id_set_ = false;

    return *this;
  }

  const CRGBAT &toBW() {
    T gray = getGray();

    if (gray > 0.5)
      gray = 1;
    else
      gray = 0;

    r_ = gray;
    g_ = gray;
    b_ = gray;

    id_set_ = false;

    return *this;
  }

  CRGBAT bwContrast() const {
    T gray = getGray();

    if (gray > 0.5)
      gray = 0;
    else
      gray = 1;

    return CRGBAT(gray, gray, gray);
  }

  // TODO: clamp by scaling by largest color to retain color ?

  const CRGBAT &clamp(double cmin=0.0, double cmax=1.0) {
    r_ = std::max(cmin, std::min(cmax, r_));
    g_ = std::max(cmin, std::min(cmax, g_));
    b_ = std::max(cmin, std::min(cmax, b_));
    a_ = std::max(cmin, std::min(cmax, a_));

    id_set_ = false;

    return *this;
  }

  CRGBAT clamped(double cmin=0.0, double cmax=1.0) const {
    return CRGBAT(std::max(cmin, std::min(cmax, r_)),
                  std::max(cmin, std::min(cmax, g_)),
                  std::max(cmin, std::min(cmax, b_)),
                  std::max(cmin, std::min(cmax, a_)));
  }

  const CRGBAT &blend(const CRGBAT &rgb, T factor) const {
    T factor1 = 1.0 - factor;

    r_ = r_*factor + rgb.r_*factor1;
    g_ = g_*factor + rgb.g_*factor1;
    b_ = b_*factor + rgb.b_*factor1;
    a_ = a_*factor + rgb.a_*factor1;

    id_set_ = false;

    return *this;
  }

  CRGBAT blended(const CRGBAT &rgb, T factor) const {
    T factor1 = 1.0 - factor;

    return CRGBAT(r_*factor + rgb.r_*factor1,
                  g_*factor + rgb.g_*factor1,
                  b_*factor + rgb.b_*factor1,
                  a_*factor + rgb.a_*factor1);
  }

  // combine new color on top of old color
  const CRGBAT &combine(const CRGBAT &rgb) const {
    T a1 = 1.0 - rgb.a_;

    r_ = r_*a1 + rgb.r_*rgb.a_;
    g_ = g_*a1 + rgb.g_*rgb.a_;
    b_ = b_*a1 + rgb.b_*rgb.a_;
    a_ = a_*a1 + rgb.a_;

    id_set_ = false;

    return *this;
  }

  CRGBAT combined(const CRGBAT &rgb) const {
    T a1 = 1.0 - rgb.a_;

    return CRGBAT(r_*a1 + rgb.r_*rgb.a_,
                  g_*a1 + rgb.g_*rgb.a_,
                  b_*a1 + rgb.b_*rgb.a_,
                  a_*a1 + rgb.a_);
  }

  CRGBAT modeCombine(const CRGBAT &src,
                     CRGBACombineMode src_mode=CRGBA_COMBINE_SRC_ALPHA,
                     CRGBACombineMode dst_mode=CRGBA_COMBINE_ONE_MINUS_SRC_ALPHA,
                     CRGBACombineFunc func=CRGBA_COMBINE_ADD,
                     const CRGBAT &factor=CRGBAT(0,0,0,1)) {
    return modeCombine(src, *this, src_mode, dst_mode, func, factor);
  }

  static CRGBAT modeCombine(const CRGBAT &src, const CRGBAT &dst,
                            CRGBACombineMode src_mode=CRGBA_COMBINE_SRC_ALPHA,
                            CRGBACombineMode dst_mode=CRGBA_COMBINE_ONE_MINUS_SRC_ALPHA,
                            CRGBACombineFunc func=CRGBA_COMBINE_ADD,
                            const CRGBAT &factor=CRGBAT(0,0,0,1)) {
    CRGBAT sf(1,1,1,1);
    CRGBAT df(0,0,0,0);

    double a;

    switch (src_mode) {
      case CRGBA_COMBINE_ZERO:
        sf = CRGBAT(0,0,0,0);
        break;
      case CRGBA_COMBINE_ONE:
        sf = CRGBAT(1,1,1,1);
        break;
      case CRGBA_COMBINE_SRC_COLOR:
        sf = src;
        break;
      case CRGBA_COMBINE_DST_COLOR:
        sf = dst;
        break;
      case CRGBA_COMBINE_ONE_MINUS_SRC_COLOR:
        sf = CRGBAT(1,1,1,1) - src;
        break;
      case CRGBA_COMBINE_ONE_MINUS_DST_COLOR:
        sf = CRGBAT(1,1,1,1) - dst;
        break;
      case CRGBA_COMBINE_SRC_ALPHA:
        a  = src.getAlpha();
        sf = CRGBAT(a,a,a,a);
        break;
      case CRGBA_COMBINE_DST_ALPHA:
        a  = dst.getAlpha();
        sf = CRGBAT(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_SRC_ALPHA:
        a  = 1.0 - src.getAlpha();
        sf = CRGBAT(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_DST_ALPHA:
        a  = 1.0 - dst.getAlpha();
        sf = CRGBAT(a,a,a,a);
        break;
      case CRGBA_COMBINE_SRC_ALPHA_SATURATE:
        a  = std::min(src.getAlpha(), 1 - dst.getAlpha());
        sf = CRGBAT(a,a,a,1);
        break;
      case CRGBA_COMBINE_DST_ALPHA_SATURATE:
        a  = std::min(dst.getAlpha(), 1 - src.getAlpha());
        sf = CRGBAT(a,a,a,1);
        break;
      case CRGBA_COMBINE_CONSTANT_COLOR:
        sf = factor;
        break;
      case CRGBA_COMBINE_ONE_MINUS_CONSTANT_COLOR:
        sf = CRGBAT(1,1,1,1) - factor;
        break;
      case CRGBA_COMBINE_CONSTANT_ALPHA:
        a = factor.getAlpha();
        sf = CRGBAT(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_CONSTANT_ALPHA:
        a = 1.0 - factor.getAlpha();
        sf = CRGBAT(a,a,a,a);
        break;
      default:
        break;
    }

    switch (dst_mode) {
      case CRGBA_COMBINE_ZERO:
        df = CRGBAT(0,0,0,0);
        break;
      case CRGBA_COMBINE_ONE:
        df = CRGBAT(1,1,1,1);
        break;
      case CRGBA_COMBINE_SRC_COLOR:
        df = src;
        break;
      case CRGBA_COMBINE_DST_COLOR:
        df = dst;
        break;
      case CRGBA_COMBINE_ONE_MINUS_SRC_COLOR:
        df = CRGBAT(1,1,1,1) - src;
        break;
      case CRGBA_COMBINE_ONE_MINUS_DST_COLOR:
        df = CRGBAT(1,1,1,1) - dst;
        break;
      case CRGBA_COMBINE_SRC_ALPHA:
        a  = src.getAlpha();
        df = CRGBAT(a,a,a,a);
        break;
      case CRGBA_COMBINE_DST_ALPHA:
        a  = dst.getAlpha();
        df = CRGBAT(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_SRC_ALPHA:
        a  = 1.0 - src.getAlpha();
        df = CRGBAT(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_DST_ALPHA:
        a  = 1.0 - dst.getAlpha();
        df = CRGBAT(a,a,a,a);
        break;
      case CRGBA_COMBINE_CONSTANT_COLOR:
        df = factor;
        break;
      case CRGBA_COMBINE_ONE_MINUS_CONSTANT_COLOR:
        df = CRGBAT(1,1,1,1) - factor;
        break;
      case CRGBA_COMBINE_CONSTANT_ALPHA:
        a = factor.getAlpha();
        df = CRGBAT(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_CONSTANT_ALPHA:
        a = 1.0 - factor.getAlpha();
        df = CRGBAT(a,a,a,a);
        break;
      default:
        break;
    }

    CRGBAT rgba_s = sf*src;
    CRGBAT rgba_d = df*dst;

    if      (func == CRGBA_COMBINE_ADD)
      return rgba_s + rgba_d;
    else if (func == CRGBA_COMBINE_SUBTRACT)
      return rgba_s - rgba_d;
    else if (func == CRGBA_COMBINE_REVERSE_SUBTRACT)
      return rgba_d - rgba_s;
    else if (func == CRGBA_COMBINE_MULTIPLY)
      return rgba_s * rgba_d;
    else if (func == CRGBA_COMBINE_MIN)
      return minParts(rgba_s, rgba_d);
    else if (func == CRGBA_COMBINE_MAX)
      return maxParts(rgba_s, rgba_d);
    else if (func == CRGBA_COMBINE_SRC       || func == CRGBA_COMBINE_ATOP ||
             func == CRGBA_COMBINE_OVER      || func == CRGBA_COMBINE_IN ||
             func == CRGBA_COMBINE_OUT       || func == CRGBA_COMBINE_DEST ||
             func == CRGBA_COMBINE_DEST_ATOP || func == CRGBA_COMBINE_DEST_OVER ||
             func == CRGBA_COMBINE_DEST_IN   || func == CRGBA_COMBINE_DEST_OUT ||
             func == CRGBA_COMBINE_CLEAR     || func == CRGBA_COMBINE_XOR)
      return porterDuffCombine(src, dst, func);

    // assert ?
    return rgba_s;
  }

  static CRGBAT porterDuffCombine(const CRGBAT &src, const CRGBAT &dst,
                                  CRGBACombineFunc func) {
    // Porter Duff source, destination and both factors
    double Asrc  = src.a_*(1 - dst.a_);
    double Adest = dst.a_*(1 - src.a_);
    double Aboth = src.a_*dst.a_;

    CRGBAT res;

    // s, 0, s
    if      (func == CRGBA_COMBINE_SRC      ) { res    = Asrc*src +             Aboth*src;
                                                res.a_ = Asrc     +             Aboth; }
    // 0, d, s
    else if (func == CRGBA_COMBINE_ATOP     ) { res =               Adest*dst + Aboth*src;
                                                res.a_ =            Adest     + Aboth; }
    // s, d, s
    else if (func == CRGBA_COMBINE_OVER     ) { res    = Asrc*src + Adest*dst + Aboth*src;
                                                res.a_ = Asrc     + Adest     + Aboth; }
    // 0, 0, s
    else if (func == CRGBA_COMBINE_IN       ) { res    =                        Aboth*src;
                                                res.a_ =                        Aboth; }
    // s, 0, 0
    else if (func == CRGBA_COMBINE_OUT      ) { res    = Asrc*src;
                                                res.a_ = Asrc;                         }
    // 0, d, d
    else if (func == CRGBA_COMBINE_DEST     ) { res    =            Adest*dst + Aboth*dst;
                                                res.a_ =            Adest     + Aboth; }
    // s, 0, d
    else if (func == CRGBA_COMBINE_DEST_ATOP) { res    = Asrc*src             + Aboth*dst;
                                                res.a_ = Asrc                 + Aboth; }
    // s, d, d
    else if (func == CRGBA_COMBINE_DEST_OVER) { res    = Asrc*src + Adest*dst + Aboth*dst;
                                                res.a_ = Asrc     + Adest     + Aboth; }
    // 0, 0, d
    else if (func == CRGBA_COMBINE_DEST_IN  ) { res    =                        Aboth*dst;
                                                res.a_ =                        Aboth; }
    // 0, d, 0
    else if (func == CRGBA_COMBINE_DEST_OUT ) { res    =            Adest*dst;
                                                res.a_ =            Adest;             }
    // s, d, 0
    else if (func == CRGBA_COMBINE_XOR      ) { res    = Asrc*src + Adest*dst;
                                                res.a_ = Asrc     + Adest;             }
    // 0, 0, 0
    else if (func == CRGBA_COMBINE_CLEAR    ) { res    = CRGBAT(0,0,0,0);
                                                res.a_ = 0;                            }

    // assert ?
    return res;
  }

  static CRGBAT arithmeticCombine(const CRGBAT &src, const CRGBAT &dst,
                                  double k1, double k2, double k3, double k4) {
    return k1*src*dst + k2*src + k3*dst + k4;
  }

#if 0
  static RGB blendCombine(const CRGBAT &src, const CRGBAT &dst, CRGBABlendMode mode) {
    double qa = src.getAlpha();
    double qb = dst.getAlpha();

    RGB ca = src.getRGB();
    RGB cb = dst.getRGB();

    if      (mode == CRGBA_BLEND_NORMAL)
      return (1 - qa)*cb + ca;
    else if (mode == CRGBA_BLEND_MULTIPLY)
      return (1 - qa)*cb + (1 - qb)*ca + ca*cb;
    else if (mode == CRGBA_BLEND_SCREEN)
      return cb + ca - ca*cb;
    else if (mode == CRGBA_BLEND_DARKEN)
      return RGB::minParts((1 - qa)*cb + ca, (1 - qb)*ca + cb);
    else if (mode == CRGBA_BLEND_LIGHTEN)
      return RGB::maxParts((1 - qa)*cb + ca, (1 - qb)*ca + cb);
    else
      return ca;
  }
#endif

  static CRGBAT blendCombine(const CRGBAT &src, const CRGBAT &dst, CRGBABlendMode mode) {
    double qa = src.getAlpha();
    double qb = dst.getAlpha();

    if      (mode == CRGBA_BLEND_NORMAL)
      return (1 - qa)*dst + src;
    else if (mode == CRGBA_BLEND_MULTIPLY)
      return (1 - qa)*dst + (1 - qb)*src + src*dst;
    else if (mode == CRGBA_BLEND_SCREEN)
      return dst + src - src*dst;
    else if (mode == CRGBA_BLEND_DARKEN)
      return minParts((1 - qa)*dst + src, (1 - qb)*src + dst);
    else if (mode == CRGBA_BLEND_LIGHTEN)
      return maxParts((1 - qa)*dst + src, (1 - qb)*src + dst);
    else
      return src;
  }

  static CRGBAT minParts(const CRGBAT &rgba_s, const CRGBAT &rgba_d) {
    return CRGBAT(std::min(rgba_s.r_, rgba_d.r_),
                  std::min(rgba_s.g_, rgba_d.g_),
                  std::min(rgba_s.b_, rgba_d.b_),
                  std::min(rgba_s.a_, rgba_d.a_));
  }

  static CRGBAT maxParts(const CRGBAT &rgba_s, const CRGBAT &rgba_d) {
    return CRGBAT(std::max(rgba_s.r_, rgba_d.r_),
                  std::max(rgba_s.g_, rgba_d.g_),
                  std::max(rgba_s.b_, rgba_d.b_),
                  std::max(rgba_s.a_, rgba_d.a_));
  }

  const CRGBAT &invert() {
    r_ = 1.0 - r_;
    g_ = 1.0 - g_;
    b_ = 1.0 - b_;

    id_set_ = false;

    return *this;
  }

  CRGBAT inverse() const {
    CRGBAT rgba(*this);

    return rgba.invert();
  }

  const CRGBAT &toSepia() {
    T gray = getGray();

    r_ = gray + CRGBA_SEPIA_R2;
    g_ = gray + CRGBA_SEPIA_G2;
    b_ = gray + CRGBA_SEPIA_B2;

    clamp();

    id_set_ = false;

    return *this;
  }

  CRGBAT sepia() {
    CRGBAT rgba(*this);

    return rgba.toSepia();
  }

  bool isTransparent() const {
    return a_ <= 0.01;
  }

  CRGBAT solid() const {
    CRGBAT rgba(*this);

    rgba.a_ = 1.0;

    return rgba;
  }

  CRGBAT bwColor() const {
    if (getGray() < 0.5)
      return CRGBAT(1,1,1);
    else
      return CRGBAT(0,0,0);
  }

  void setAlphaByGray(bool positive=true) {
    T g = getGray();

    if (! positive) g = 1.0 - g;

    setAlpha(g);
  }

  void setGrayByAlpha(bool positive=true) {
    T a = getAlpha();

    if (! positive) a = 1.0 - a;

    setRGBA(a, a, a, 1);
  }

  void setAlphaByColor(const CRGBAT &rgba, T a=1.0) {
    if (*this == rgba)
      setAlpha(a);
  }

  uint encodeRGBA() const {
    uint r, g, b, a;

    getRGBAI(&r, &g, &b, &a);

    return encodeRGBA(r, g, b, a);
  }

  uint encodeARGB() const {
    uint r, g, b, a;

    getRGBAI(&r, &g, &b, &a);

    return encodeARGB(r, g, b, a);
  }

  uint encodeRGB() const {
    uint r, g, b, a;

    getRGBAI(&r, &g, &b, &a);

    return encodeRGB(r, g, b);
  }

  static uint encodeRGBA(uint r, uint g, uint b, uint a=255) {
    return (((r & 0xff) << 24) |
            ((g & 0xff) << 16) |
            ((b & 0xff) <<  8) |
            ((a & 0xff) <<  0));
  }

  static uint encodeARGB(uint r, uint g, uint b, uint a=255) {
    return (((a & 0xff) << 24) |
            ((r & 0xff) << 16) |
            ((g & 0xff) <<  8) |
            ((b & 0xff) <<  0));
  }

  static uint encodeRGB(uint r, uint g, uint b) {
    return (((r & 0xff) << 16) |
            ((g & 0xff) <<  8) |
            ((b & 0xff) <<  0));
  }

  static void decodeARGB(uint id, uint *r, uint *g, uint *b, uint *a) {
    *a = (id >> 24) & 0xFF;
    *r = (id >> 16) & 0xFF;
    *g = (id >>  8) & 0xFF;
    *b = (id      ) & 0xFF;
  }

  static void decodeARGB(uint id, CRGBAT &rgba) {
    uint r, g, b, a;

    decodeARGB(id, &r, &g, &b, &a);

    rgba = CRGBAT(r/255.0, g/255.0, b/255.0, a/255.0);
  }

  CHSVT<T>  toHSV () const { return Util::RGBtoHSV (getRGB()); }
  CHSLT<T>  toHSL () const { return Util::RGBtoHSL (getRGB()); }
  CCMYKT<T> toCMYK() const { return Util::RGBtoCMYK(getRGB()); }
  CHSBT<T>  toHSB () const { return Util::RGBtoHSB (getRGB()); }

 private:
  T    r_, g_, b_, a_;
  uint id_;
  bool id_set_;
};

typedef CRGBAT<double> CRGBA;

#endif
