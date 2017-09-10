#ifndef CRGBA_H
#define CRGBA_H

#include <CRGB.h>

#ifdef USE_CRGB_NAME
#include <CRGBName.h>
#endif

#include <cassert>

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

enum CRGBAComponent {
  CRGBA_COMPONENT_NONE =0,
  CRGBA_COMPONENT_RED  =(1<<0),
  CRGBA_COMPONENT_GREEN=(1<<1),
  CRGBA_COMPONENT_BLUE =(1<<2),
  CRGBA_COMPONENT_ALPHA=(1<<3)
};

//---

class CRGBA {
 private:
  typedef uint (*IdProc)(double r, double g, double b, double a);

  static uint clampI(int v) {
    return (v >= 0 ? (v <= 255 ? v : 255) : 0);
  }

 public:
  struct IValT { };

  static IdProc setIdProc(IdProc proc) {
    static IdProc id_proc_ = defIdProc;

    if (proc)
      id_proc_ = proc;

    return id_proc_;
  }

  static uint defIdProc(double r, double g, double b, double a) {
    return encodeARGB(ivalue(r), ivalue(g), ivalue(b), ivalue(a));
  }

  static uint calcId(double r, double g, double b, double a) {
    IdProc id_proc = setIdProc(0);

    return id_proc(r, g, b, a);
  }

  static const IValT &IVal() { static IValT ival; return ival; }

  static CRGBA fromRGBAI(int r, int g, int b, int a=255) {
    return CRGBA(rvalue(r), rvalue(g), rvalue(b), rvalue(a));
  }

  static int iround(double r) {
    if (r < 0)
      return int(r - 0.5);
    else
      return int(r + 0.5);
  }

  static int ivalue(double r) {
    return iround(r*255.0);
  }

  static double rvalue(int i) {
    return i/255.0;
  }

  //-------

  CRGBA() :
   r_(0.0), g_(0.0), b_(0.0), a_(0.0), id_(0), id_set_(false) {
  }

  CRGBA(double r, double g, double b, double a=1.0) :
   r_(r), g_(g), b_(b), a_(a), id_(0), id_set_(false) {
  }

  explicit CRGBA(double gray, double a=1.0) :
   r_(gray), g_(gray), b_(gray), a_(a), id_(0), id_set_(false) {
  }

  CRGBA(const IValT &, int r, int g, int b, int a=255) :
   r_(rvalue(r)), g_(rvalue(g)), b_(rvalue(b)), a_(rvalue(a)), id_(0), id_set_(false) {
  }

#ifdef USE_CRGB_NAME
  explicit CRGBA(const std::string &name) :
   r_(0), g_(0), b_(0), a_(0), id_(0), id_set_(false) {
    CRGBName::lookup(name, &r_, &g_, &b_, &a_);
  }

  explicit CRGBA(const std::string &name, double a) :
   id_(0), id_set_(false) {
    CRGBName::lookup(name, &r_, &g_, &b_, &a_);

    a_ = a;
  }
#endif

  CRGBA(const CRGBA &rgba) :
   r_(rgba.r_), g_(rgba.g_), b_(rgba.b_), a_(rgba.a_), id_(rgba.id_), id_set_(rgba.id_set_) {
  }

  CRGBA(const CRGB &rgb, double a=1.0) :
   r_(rgb.getRed()), g_(rgb.getGreen()), b_(rgb.getBlue()), a_(a), id_(0), id_set_(false) {
  }

 ~CRGBA() { }

  CRGBA &operator=(const CRGBA &rgba) {
    if (&rgba == this)
      return *this;

    r_ = rgba.r_; g_ = rgba.g_; b_ = rgba.b_; a_ = rgba.a_;

    id_ = rgba.id_; id_set_ = rgba.id_set_;

    return *this;
  }

  CRGBA &operator=(const CRGB &rgb) {
    r_ = rgb.getRed  ();
    g_ = rgb.getGreen();
    b_ = rgb.getBlue ();
    a_ = 1.0;

    id_set_ = false;

    return *this;
  }

  CRGBA operator+() const {
    return *this;
  }

  CRGBA operator-() const {
    return CRGBA(-r_, -g_, -b_, a_);
  }

  CRGBA &operator+=(double rhs) {
    r_ += rhs;
    g_ += rhs;
    b_ += rhs;

    id_set_ = false;

    return *this;
  }

  CRGBA &operator+=(const CRGBA &rhs) {
    r_ += rhs.r_;
    g_ += rhs.g_;
    b_ += rhs.b_;
    a_ += rhs.a_;

    id_set_ = false;

    return *this;
  }

  CRGBA operator+(double rhs) const {
    CRGBA t = *this;

    t += rhs;

    return t;
  }

  CRGBA operator+(const CRGBA &rhs) const {
    CRGBA t = *this;

    t += rhs;

    return t;
  }

  CRGBA &operator-=(double rhs) {
    r_ -= rhs;
    g_ -= rhs;
    b_ -= rhs;

    id_set_ = false;

    return *this;
  }

  CRGBA &operator-=(const CRGBA &rhs) {
    r_ -= rhs.r_;
    g_ -= rhs.g_;
    b_ -= rhs.b_;
    a_ -= rhs.a_;

    id_set_ = false;

    return *this;
  }

  CRGBA operator-(double rhs) const {
    CRGBA t = *this;

    t -= rhs;

    return t;
  }

  CRGBA operator-(const CRGBA &rhs) const {
    CRGBA t = *this;

    t -= rhs;

    return t;
  }

  CRGBA &operator*=(double rhs) {
    r_ *= rhs;
    g_ *= rhs;
    b_ *= rhs;
    a_ *= rhs;

    id_set_ = false;

    return *this;
  }

  CRGBA &operator*=(const CRGBA &rhs) {
    r_ *= rhs.r_;
    g_ *= rhs.g_;
    b_ *= rhs.b_;
    a_ *= rhs.a_;

    id_set_ = false;

    return *this;
  }

  CRGBA operator*(const CRGBA &rhs) const {
    CRGBA t = *this;

    t *= rhs;

    return t;
  }

  CRGBA &operator/=(double rhs) {
    double irhs = 1.0/rhs;

    r_ *= irhs;
    g_ *= irhs;
    b_ *= irhs;
    a_ *= irhs;

    id_set_ = false;

    return *this;
  }

  CRGBA &operator/=(const CRGBA &rhs) {
    r_ /= rhs.r_;
    g_ /= rhs.g_;
    b_ /= rhs.b_;
    a_ /= rhs.a_;

    id_set_ = false;

    return *this;
  }

  CRGBA operator/(double rhs) const {
    CRGBA t = *this;

    t /= rhs;

    return t;
  }

  CRGBA operator/(const CRGBA &rhs) const {
    CRGBA t = *this;

    t /= rhs;

    return t;
  }

  //------

  friend bool operator< (const CRGBA &lhs, const CRGBA &rhs) {
    return (lhs.getId() < rhs.getId());
  }

  friend bool operator<=(const CRGBA &lhs, const CRGBA &rhs) {
    return (lhs.getId() <= rhs.getId());
  }

  friend bool operator> (const CRGBA &lhs, const CRGBA &rhs) {
    return (lhs.getId() > rhs.getId());
  }

  friend bool operator>=(const CRGBA &lhs, const CRGBA &rhs) {
    return (lhs.getId() >= rhs.getId());
  }

  friend bool operator==(const CRGBA &lhs, const CRGBA &rhs) {
    return (lhs.getId() == rhs.getId());
  }

  friend bool operator!=(const CRGBA &lhs, const CRGBA &rhs) {
    return ! (lhs.getId() == rhs.getId());
  }

  //------

  friend bool operator==(const CRGBA &lhs, const CRGB &rhs) {
    return (lhs.getId() == calcId(rhs.getRed(), rhs.getGreen(), rhs.getBlue(), 1.0));
  }

  friend bool operator!=(const CRGBA &lhs, const CRGB &rhs) {
    return ! (lhs.getId() == calcId(rhs.getRed(), rhs.getGreen(), rhs.getBlue(), 1.0));
  }

  //------

  friend CRGBA operator*(const CRGBA &lhs, double rhs) {
    return CRGBA(lhs.r_*rhs, lhs.g_*rhs, lhs.b_*rhs, lhs.a_*rhs);
  }

  friend CRGBA operator*(double lhs, const CRGBA &rhs) {
    return CRGBA(lhs*rhs.r_, lhs*rhs.g_, lhs*rhs.b_, lhs*rhs.a_);
  }

  void print(std::ostream &os) const {
    os << "CRGBA(" << r_ << "," << g_ << "," << b_ << "," << a_ << ")";
  }

  friend std::ostream &operator<<(std::ostream &os, const CRGBA &rgba) {
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

  CRGBA &zero() {
    r_ = g_ = b_ = a_ = 0.0;

    id_set_ = false;

    return *this;
  }

  CRGBA &setRed  (double r) { r_ = r; id_set_ = false; return *this; }
  CRGBA &setGreen(double g) { g_ = g; id_set_ = false; return *this; }
  CRGBA &setBlue (double b) { b_ = b; id_set_ = false; return *this; }
  CRGBA &setAlpha(double a) { a_ = a; id_set_ = false; return *this; }

  CRGBA &setGray(double g, double a=1.0) {
    r_ = g; g_ = g; b_ = g; a_ = a;

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

  CRGBA &scaleRGB(double f) {
    r_ *= f;
    g_ *= f;
    b_ *= f;

    id_set_ = false;

    return *this;
  }

  CRGBA &scaleAlpha(double a) {
    a_ *= a;

    id_set_ = false;

    return *this;
  }

  CRGBA &setRGB(double r, double g, double b) {
    r_ = r; g_ = g; b_ = b;

    id_set_ = false;

    return *this;
  }

  CRGBA &setRGB(const CRGB &rgb) {
    r_ = rgb.getRed();
    g_ = rgb.getGreen();
    b_ = rgb.getBlue();

    id_set_ = false;

    return *this;
  }

  CRGBA &setRGBA(double r, double g, double b, double a=1.0) {
    r_ = r; g_ = g; b_ = b; a_ = a;

    id_set_ = false;

    return *this;
  }

  CRGBA &setRGBA(const CRGBA &rgba) {
    r_ = rgba.r_; g_ = rgba.g_; b_ = rgba.b_; a_ = rgba.a_;

    id_set_ = false;

    return *this;
  }

  CRGBA &setGrayI(uint ig, uint ia=255) {
    return setGray(rvalue(ig), ia);
  }

  CRGBA &setRGBAI(uint ir, uint ig, uint ib, uint ia=255) {
    return setRGBA(rvalue(ir), rvalue(ig), rvalue(ib), rvalue(ia));
  }

  CRGB getRGB() const {
    return CRGB(r_, g_, b_);
  }

  void getRGBA(double *r, double *g, double *b, double *a) const {
    *r = r_; *g = g_; *b = b_; *a = a_;
  }

  void getRGBAI(uint *r, uint *g, uint *b, uint *a) const {
    *r = ivalue(r_);
    *g = ivalue(g_);
    *b = ivalue(b_);
    *a = ivalue(a_);
  }

  double getRed  () const { return r_; }
  double getGreen() const { return g_; }
  double getBlue () const { return b_; }
  double getAlpha() const { return a_; }

  uint getRedI  () const { return clampI(ivalue(r_)); }
  uint getGreenI() const { return clampI(ivalue(g_)); }
  uint getBlueI () const { return clampI(ivalue(b_)); }
  uint getAlphaI() const { return clampI(ivalue(a_)); }

  double getComponent(CRGBAComponent component) const {
    switch (component) {
      case CRGBA_COMPONENT_RED  : return r_;
      case CRGBA_COMPONENT_GREEN: return g_;
      case CRGBA_COMPONENT_BLUE : return b_;
      case CRGBA_COMPONENT_ALPHA: return a_;
      default: assert(false);     return 0.0;
    }
  }

  void setComponent(CRGBAComponent component, double value) {
    switch (component) {
      case CRGBA_COMPONENT_RED  : r_ = value; break;
      case CRGBA_COMPONENT_GREEN: g_ = value; break;
      case CRGBA_COMPONENT_BLUE : b_ = value; break;
      case CRGBA_COMPONENT_ALPHA: a_ = value; break;
      default: assert(false); break;
    }
  }

  const CRGBA &normalize() {
    r_ *= a_;
    g_ *= a_;
    b_ *= a_;
    a_  = 1.0;

    return *this;
  }

  CRGBA normalized() const {
    return CRGBA(r_*a_, g_*a_, b_*a_, 1.0);
  }

  uint getId() const {
    if (! id_set_) {
      CRGBA *th = const_cast<CRGBA *>(this);

      th->id_ = calcId(r_, g_, b_, a_);

      th->id_set_ = true;
    }

    return id_;
  }

  double getClampRed() const {
    return std::max(0.0, std::min(1.0, r_));
  }

  double getClampGreen() const {
    return std::max(0.0, std::min(1.0, g_));
  }

  double getClampBlue() const {
    return std::max(0.0, std::min(1.0, b_));
  }

  double getClampAlpha() const {
    return std::max(0.0, std::min(1.0, a_));
  }

  double getGray() const {
    return (CRGBA_R_FACTOR*r_ + CRGBA_G_FACTOR*g_ + CRGBA_B_FACTOR*b_);
  }

  uint getGrayI() const { return ivalue(getGray()); }

  double getClampGray() const {
    return clamped().getGray();
  }

  CRGBA getGrayRGBA() const {
    double gray = getGray();

    return CRGBA(gray, gray, gray, a_);
  }

  double getIntensity() const {
    return std::max(r_, std::max(g_, b_));
  }

  //---

  double getLightRed(double f=CRGBA_LIGHT_FACTOR) const {
    return std::min(r_*f, 1.0);
  }

  double getLightGreen(double f=CRGBA_LIGHT_FACTOR) const {
    return std::min(g_*f, 1.0);
  }

  double getLightBlue(double f=CRGBA_LIGHT_FACTOR) const {
    return std::min(b_*f, 1.0);
  }

  double getLightGray(double f=CRGBA_LIGHT_FACTOR) const {
    double gray = getGray();

    return std::min(gray*f, 1.0);
  }

  CRGBA getLightRGBA(double f=CRGBA_LIGHT_FACTOR) const {
    return CRGBA(getLightRed(f), getLightGreen(f), getLightBlue(f), a_);
  }

  //---

  double getDarkRed(double f=CRGBA_DARK_FACTOR) const {
    return std::min(r_*f, 1.0);
  }

  double getDarkGreen(double f=CRGBA_DARK_FACTOR) const {
    return std::min(g_*f, 1.0);
  }

  double getDarkBlue(double f=CRGBA_DARK_FACTOR) const {
    return std::min(b_*f, 1.0);
  }

  double getDarkGray(double f=CRGBA_DARK_FACTOR) const {
    double gray = getGray();

    return std::min(gray*f, 1.0);
  }

  CRGBA getDarkRGBA(double f=CRGBA_DARK_FACTOR) const {
    return CRGBA(getDarkRed(f), getDarkGreen(f), getDarkBlue(f), a_);
  }

  //---

  double getInverseRed() const {
    return 1.0 - r_;
  }

  double getInverseGreen() const {
    return 1.0 - g_;
  }

  double getInverseBlue() const {
    return 1.0 - b_;
  }

  double getInverseGray() const {
    double gray = getGray();

    return 1.0 - gray;
  }

  CRGBA getInverseRGBA() const {
    return CRGBA(getInverseRed(), getInverseGreen(), getInverseBlue(), a_);
  }

  const CRGBA &toGray() {
    double gray = getGray();

    r_ = gray;
    g_ = gray;
    b_ = gray;

    id_set_ = false;

    return *this;
  }

  const CRGBA &toBW() {
    double gray = getGray();

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

  CRGBA bwContrast() const {
    double gray = getGray();

    if (gray > 0.5)
      gray = 0;
    else
      gray = 1;

    return CRGBA(gray, gray, gray);
  }

  // TODO: clamp by scaling by largest color to retain color ?

  const CRGBA &clamp(double cmin=0.0, double cmax=1.0) {
    r_ = std::max(cmin, std::min(cmax, r_));
    g_ = std::max(cmin, std::min(cmax, g_));
    b_ = std::max(cmin, std::min(cmax, b_));
    a_ = std::max(cmin, std::min(cmax, a_));

    id_set_ = false;

    return *this;
  }

  CRGBA clamped(double cmin=0.0, double cmax=1.0) const {
    return CRGBA(std::max(cmin, std::min(cmax, r_)),
                 std::max(cmin, std::min(cmax, g_)),
                 std::max(cmin, std::min(cmax, b_)),
                 std::max(cmin, std::min(cmax, a_)));
  }

  const CRGBA &blend(const CRGBA &rgb, double factor) {
    double factor1 = 1.0 - factor;

    r_ = r_*factor + rgb.r_*factor1;
    g_ = g_*factor + rgb.g_*factor1;
    b_ = b_*factor + rgb.b_*factor1;
    a_ = a_*factor + rgb.a_*factor1;

    id_set_ = false;

    return *this;
  }

  CRGBA blended(const CRGBA &rgb, double factor) const {
    CRGBA c = *this;

    c.blend(rgb, factor);

    return c;
  }

  // combine new color on top of old color
  const CRGBA &combine(const CRGBA &rgb) {
    double a1 = 1.0 - a_;
    double a2 = 1.0 - rgb.a_;

    double af = 1.0 - a1*a2;

    if (af > 0.0) {
      r_ = r_*a_*a2/af + rgb.r_*rgb.a_/af;
      g_ = g_*a_*a2/af + rgb.g_*rgb.a_/af;
      b_ = b_*a_*a2/af + rgb.b_*rgb.a_/af;
      a_ = af;
    }
    else {
      r_ = 0.0;
      g_ = 0.0;
      b_ = 0.0;
      a_ = 0.0;
    }

    id_set_ = false;

    return *this;
  }

  CRGBA combined(const CRGBA &rgb) const {
    CRGBA rgba1(*this);

    rgba1.combine(rgb);

    return rgba1;
  }

  CRGBA modeCombine(const CRGBA &src,
                    CRGBACombineMode src_mode=CRGBA_COMBINE_SRC_ALPHA,
                    CRGBACombineMode dst_mode=CRGBA_COMBINE_ONE_MINUS_SRC_ALPHA,
                    CRGBACombineFunc func=CRGBA_COMBINE_ADD,
                    const CRGBA &factor=CRGBA(0,0,0,1)) {
    return modeCombine(src, *this, src_mode, dst_mode, func, factor);
  }

  static CRGBA modeCombine(const CRGBA &src, const CRGBA &dst,
                           CRGBACombineMode src_mode=CRGBA_COMBINE_SRC_ALPHA,
                           CRGBACombineMode dst_mode=CRGBA_COMBINE_ONE_MINUS_SRC_ALPHA,
                           CRGBACombineFunc func=CRGBA_COMBINE_ADD,
                           const CRGBA &factor=CRGBA(0,0,0,1)) {
    CRGBA sf(1,1,1,1);
    CRGBA df(0,0,0,0);

    double a;

    switch (src_mode) {
      case CRGBA_COMBINE_ZERO:
        sf = CRGBA(0,0,0,0);
        break;
      case CRGBA_COMBINE_ONE:
        sf = CRGBA(1,1,1,1);
        break;
      case CRGBA_COMBINE_SRC_COLOR:
        sf = src;
        break;
      case CRGBA_COMBINE_DST_COLOR:
        sf = dst;
        break;
      case CRGBA_COMBINE_ONE_MINUS_SRC_COLOR:
        sf = CRGBA(1,1,1,1) - src;
        break;
      case CRGBA_COMBINE_ONE_MINUS_DST_COLOR:
        sf = CRGBA(1,1,1,1) - dst;
        break;
      case CRGBA_COMBINE_SRC_ALPHA:
        a  = src.getAlpha();
        sf = CRGBA(a,a,a,a);
        break;
      case CRGBA_COMBINE_DST_ALPHA:
        a  = dst.getAlpha();
        sf = CRGBA(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_SRC_ALPHA:
        a  = 1.0 - src.getAlpha();
        sf = CRGBA(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_DST_ALPHA:
        a  = 1.0 - dst.getAlpha();
        sf = CRGBA(a,a,a,a);
        break;
      case CRGBA_COMBINE_SRC_ALPHA_SATURATE:
        a  = std::min(src.getAlpha(), 1 - dst.getAlpha());
        sf = CRGBA(a,a,a,1);
        break;
      case CRGBA_COMBINE_DST_ALPHA_SATURATE:
        a  = std::min(dst.getAlpha(), 1 - src.getAlpha());
        sf = CRGBA(a,a,a,1);
        break;
      case CRGBA_COMBINE_CONSTANT_COLOR:
        sf = factor;
        break;
      case CRGBA_COMBINE_ONE_MINUS_CONSTANT_COLOR:
        sf = CRGBA(1,1,1,1) - factor;
        break;
      case CRGBA_COMBINE_CONSTANT_ALPHA:
        a = factor.getAlpha();
        sf = CRGBA(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_CONSTANT_ALPHA:
        a = 1.0 - factor.getAlpha();
        sf = CRGBA(a,a,a,a);
        break;
      default:
        break;
    }

    switch (dst_mode) {
      case CRGBA_COMBINE_ZERO:
        df = CRGBA(0,0,0,0);
        break;
      case CRGBA_COMBINE_ONE:
        df = CRGBA(1,1,1,1);
        break;
      case CRGBA_COMBINE_SRC_COLOR:
        df = src;
        break;
      case CRGBA_COMBINE_DST_COLOR:
        df = dst;
        break;
      case CRGBA_COMBINE_ONE_MINUS_SRC_COLOR:
        df = CRGBA(1,1,1,1) - src;
        break;
      case CRGBA_COMBINE_ONE_MINUS_DST_COLOR:
        df = CRGBA(1,1,1,1) - dst;
        break;
      case CRGBA_COMBINE_SRC_ALPHA:
        a  = src.getAlpha();
        df = CRGBA(a,a,a,a);
        break;
      case CRGBA_COMBINE_DST_ALPHA:
        a  = dst.getAlpha();
        df = CRGBA(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_SRC_ALPHA:
        a  = 1.0 - src.getAlpha();
        df = CRGBA(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_DST_ALPHA:
        a  = 1.0 - dst.getAlpha();
        df = CRGBA(a,a,a,a);
        break;
      case CRGBA_COMBINE_CONSTANT_COLOR:
        df = factor;
        break;
      case CRGBA_COMBINE_ONE_MINUS_CONSTANT_COLOR:
        df = CRGBA(1,1,1,1) - factor;
        break;
      case CRGBA_COMBINE_CONSTANT_ALPHA:
        a = factor.getAlpha();
        df = CRGBA(a,a,a,a);
        break;
      case CRGBA_COMBINE_ONE_MINUS_CONSTANT_ALPHA:
        a = 1.0 - factor.getAlpha();
        df = CRGBA(a,a,a,a);
        break;
      default:
        break;
    }

    CRGBA rgba_s = sf*src;
    CRGBA rgba_d = df*dst;

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

  static CRGBA porterDuffCombine(const CRGBA &src, const CRGBA &dst, CRGBACombineFunc func) {
    // Porter Duff source, destination and both factors
    double Asrc  = src.a_*(1 - dst.a_);
    double Adest = dst.a_*(1 - src.a_);
    double Aboth = src.a_*dst.a_;

    CRGBA res;

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
    else if (func == CRGBA_COMBINE_CLEAR    ) { res    = CRGBA(0,0,0,0);
                                                res.a_ = 0;                            }

    // assert ?
    return res;
  }

  static CRGBA arithmeticCombine(const CRGBA &src, const CRGBA &dst,
                                 double k1, double k2, double k3, double k4) {
    // + k4 is + CRGBA(k4, k4, k4, 0);
#if 0
    return k1*src*dst + k2*src + k3*dst + k4;
#else
    double a = k1*src.a_*dst.a_ + k2*src.a_ + k3*dst.a_;

    if (a > 0.0) {
      double r = k1*src.r_*dst.r_ + k2*src.r_ + k3*dst.r_ + k4;
      double g = k1*src.g_*dst.g_ + k2*src.g_ + k3*dst.g_ + k4;
      double b = k1*src.b_*dst.b_ + k2*src.b_ + k3*dst.b_ + k4;

      return CRGBA(r, g, b, a).clamped();
    }
    else
      return CRGBA(0, 0, 0, 0);
#endif
  }

#if 0
  static CRGB blendCombine(const CRGBA &src, const CRGBA &dst, CRGBABlendMode mode) {
    double qa = src.getAlpha();
    double qb = dst.getAlpha();

    CRGB ca = src.getRGB();
    CRGB cb = dst.getRGB();

    if      (mode == CRGBA_BLEND_NORMAL)
      return (1 - qa)*cb + ca;
    else if (mode == CRGBA_BLEND_MULTIPLY)
      return (1 - qa)*cb + (1 - qb)*ca + ca*cb;
    else if (mode == CRGBA_BLEND_SCREEN)
      return cb + ca - ca*cb;
    else if (mode == CRGBA_BLEND_DARKEN)
      return CRGB::minParts((1 - qa)*cb + ca, (1 - qb)*ca + cb);
    else if (mode == CRGBA_BLEND_LIGHTEN)
      return CRGB::maxParts((1 - qa)*cb + ca, (1 - qb)*ca + cb);
    else
      return ca;
  }
#endif

  static CRGBA blendCombine(const CRGBA &src, const CRGBA &dst, CRGBABlendMode mode) {
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

  static CRGBA minParts(const CRGBA &rgba_s, const CRGBA &rgba_d) {
    return CRGBA(std::min(rgba_s.r_, rgba_d.r_),
                 std::min(rgba_s.g_, rgba_d.g_),
                 std::min(rgba_s.b_, rgba_d.b_),
                 std::min(rgba_s.a_, rgba_d.a_));
  }

  static CRGBA maxParts(const CRGBA &rgba_s, const CRGBA &rgba_d) {
    return CRGBA(std::max(rgba_s.r_, rgba_d.r_),
                 std::max(rgba_s.g_, rgba_d.g_),
                 std::max(rgba_s.b_, rgba_d.b_),
                 std::max(rgba_s.a_, rgba_d.a_));
  }

  const CRGBA &invert() {
    r_ = 1.0 - r_;
    g_ = 1.0 - g_;
    b_ = 1.0 - b_;

    id_set_ = false;

    return *this;
  }

  CRGBA inverse() const {
    CRGBA rgba(*this);

    return rgba.invert();
  }

  const CRGBA &toSepia() {
    double gray = getGray();

    r_ = gray + CRGBA_SEPIA_R2;
    g_ = gray + CRGBA_SEPIA_G2;
    b_ = gray + CRGBA_SEPIA_B2;

    clamp();

    id_set_ = false;

    return *this;
  }

  CRGBA sepia() {
    CRGBA rgba(*this);

    return rgba.toSepia();
  }

  bool isTransparent() const {
    return a_ <= 0.01;
  }

  CRGBA solid() const {
    CRGBA rgba(*this);

    rgba.a_ = 1.0;

    return rgba;
  }

  CRGBA bwColor() const {
    if (getGray() < 0.5)
      return CRGBA(1,1,1);
    else
      return CRGBA(0,0,0);
  }

  void setAlphaByGray(bool positive=true) {
    double g = getGray();

    if (! positive) g = 1.0 - g;

    setAlpha(g);
  }

  void setGrayByAlpha(bool positive=true) {
    double a = getAlpha();

    if (! positive) a = 1.0 - a;

    setRGBA(a, a, a, 1);
  }

  void setAlphaByColor(const CRGBA &rgba, double a=1.0) {
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

  static void decodeARGB(uint id, CRGBA &rgba) {
    uint r, g, b, a;

    decodeARGB(id, &r, &g, &b, &a);

    rgba = CRGBA(rvalue(r), rvalue(g), rvalue(b), rvalue(a));
  }

  //CHSV  toHSV () const;
  //CHSL  toHSL () const;
  //CCMYK toCMYK() const;
  //CHSB  toHSB () const;

 private:
  double r_, g_, b_, a_;
  uint   id_;
  bool   id_set_;
};

//------

//inline CHSV  CRGBA::toHSV () const { return CRGBUtil::RGBtoHSV (getRGB()); }
//inline CHSL  CRGBA::toHSL () const { return CRGBUtil::RGBtoHSL (getRGB()); }
//inline CCMYK CRGBA::toCMYK() const { return CRGBUtil::RGBtoCMYK(getRGB()); }
//inline CHSB  CRGBA::toHSB () const { return CRGBUtil::RGBtoHSB (getRGB()); }

#endif
