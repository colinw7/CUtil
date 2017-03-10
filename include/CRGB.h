#ifndef CRGB_H
#define CRGB_H

#include <cstdio>
#include <sys/types.h>
#include <iostream>

//#include <CHSV.h>
//#include <CHSL.h>
//#include <CCMYK.h>
//#include <CHSB.h>

#ifdef USE_CRGB_NAME
#include <CRGBName.h>
#endif

#define CRGB_LIGHT_FACTOR 1.25
#define CRGB_DARK_FACTOR  0.50

#define CRGB_R_FACTOR 0.3
#define CRGB_G_FACTOR 0.59
#define CRGB_B_FACTOR 0.11

#define CRGB_SEPIA_R1  0.299
#define CRGB_SEPIA_R2  0.191
#define CRGB_SEPIA_G1  0.587
#define CRGB_SEPIA_G2 -0.054
#define CRGB_SEPIA_B1  0.114
#define CRGB_SEPIA_B2 -0.221

#define CRGB_IFACTOR  255.0
#define CRGB_IFACTORI (1.0/255.0)

// red, green, blue
class CRGB {
 public:
  CRGB() { }

  CRGB(double r, double g, double b) :
   r_(r), g_(g), b_(b) {
  }

  explicit CRGB(double gray) :
   r_(gray), g_(gray), b_(gray) {
  }

#ifdef USE_CRGB_NAME
  explicit CRGB(std::string name) {
    CRGBName::lookup(name, &r_, &g_, &b_);
  }
#endif

  CRGB(const CRGB &rgb) :
   r_(rgb.r_), g_(rgb.g_), b_(rgb.b_) {
  }

 ~CRGB() { }

  CRGB &operator=(const CRGB &rgb) {
    if (this == &rgb)
      return *this;

    r_ = rgb.r_;
    g_ = rgb.g_;
    b_ = rgb.b_;

    return *this;
  }

  CRGB operator+() const {
    return CRGB(r_, g_, b_);
  }

  CRGB operator-() const {
    return CRGB(-r_, -g_, -b_);
  }

  CRGB &operator+=(const CRGB &rhs) {
    r_ += rhs.r_;
    g_ += rhs.g_;
    b_ += rhs.b_;

    return *this;
  }

  CRGB operator+(const CRGB &rhs) const {
    return CRGB(r_ + rhs.r_, g_ + rhs.g_, b_ + rhs.b_);
  }

  CRGB &operator-=(const CRGB &rhs) {
    r_ -= rhs.r_;
    g_ -= rhs.g_;
    b_ -= rhs.b_;

    return *this;
  }

  CRGB operator-(const CRGB &rhs) const {
    return CRGB(r_ - rhs.r_, g_ - rhs.g_, b_ - rhs.b_);
  }

  CRGB &operator*=(const CRGB &rhs) {
    r_ *= rhs.r_;
    g_ *= rhs.g_;
    b_ *= rhs.b_;

    return *this;
  }

  CRGB &operator*=(double rhs) {
    r_ *= rhs;
    g_ *= rhs;
    b_ *= rhs;

    return *this;
  }

  CRGB operator*(const CRGB &rhs) const {
    return CRGB(r_*rhs.r_, g_*rhs.g_, b_*rhs.b_);
  }

  CRGB &operator/=(const CRGB &rhs) {
    r_ /= rhs.r_;
    g_ /= rhs.g_;
    b_ /= rhs.b_;

    return *this;
  }

  CRGB &operator/=(double rhs) {
    double irhs = 1.0/rhs;

    r_ *= irhs;
    g_ *= irhs;
    b_ *= irhs;

    return *this;
  }

  CRGB operator/(const CRGB &rhs) const {
    return CRGB(r_/rhs.r_, g_/rhs.g_, b_/rhs.b_);
  }

  CRGB operator/(double rhs) const {
    double irhs = 1.0/rhs;

    return CRGB(r_*irhs, g_*irhs, b_*irhs);
  }

  friend CRGB operator*(const CRGB &lhs, double rhs) {
    return CRGB(lhs.r_*rhs, lhs.g_*rhs, lhs.b_*rhs);
  }

  friend CRGB operator*(double lhs, const CRGB &rhs) {
    return CRGB(lhs*rhs.r_, lhs*rhs.g_, lhs*rhs.b_);
  }

  //------

  int cmp(const CRGB &rhs) const {
    if      (r_ < rhs.r_) return -1;
    else if (r_ > rhs.r_) return 1;
    else if (g_ < rhs.g_) return -1;
    else if (g_ > rhs.g_) return 1;
    else if (b_ < rhs.b_) return -1;
    else if (b_ > rhs.b_) return 1;
    else                  return 0;
  }

  friend bool operator==(const CRGB &lhs, const CRGB &rhs) {
    return lhs.cmp(rhs) == 0;
  }

  friend bool operator!=(const CRGB &lhs, const CRGB &rhs) {
    return lhs.cmp(rhs) != 0;
  }

  friend bool operator<(const CRGB &lhs, const CRGB &rhs) {
    return lhs.cmp(rhs) < 0;
  }

  friend bool operator<=(const CRGB &lhs, const CRGB &rhs) {
    return lhs.cmp(rhs) <= 0;
  }

  friend bool operator>(const CRGB &lhs, const CRGB &rhs) {
    return lhs.cmp(rhs) > 0;
  }

  friend bool operator>=(const CRGB &lhs, const CRGB &rhs) {
    return lhs.cmp(rhs) >= 0;
  }

  //------

  void print(std::ostream &os) const {
    os << "CRGB(" << r_ << "," << g_ << "," << b_ << ")";
  }

  friend std::ostream &operator<<(std::ostream &os, const CRGB &rgb) {
    rgb.print(os);

    return os;
  }

  std::string toString() const {
    uint r, g, b;

    getRGBI(&r, &g, &b);

    char str[256];

    ::sprintf(str, "(%u,%u,%u)", r, g, b);

    return str;
  }

  std::string stringEncode() const {
    uint r, g, b;

    getRGBI(&r, &g, &b);

    char str[256];

    ::sprintf(str, "#%02X%02X%02X", r, g, b);

    return str;
  }

  void zero() { r_ = g_ = b_ = 0.0; }

  void setRed  (double r) { r_ = r; };
  void setGreen(double g) { g_ = g; };
  void setBlue (double b) { b_ = b; };

  void setRGB(double r, double g, double b) {
    r_ = r; g_ = g; b_ = b;
  }

  void setRGBI(uint r, uint g, uint b) {
    r_ = int(r/255.0); g_ = int(g/255.0); b_ = int(b/255.0);
  }

  double getRed  () const { return r_; }
  double getGreen() const { return g_; }
  double getBlue () const { return b_; }

  uint getRedI  () const { return uint(r_*CRGB_IFACTOR); }
  uint getGreenI() const { return uint(g_*CRGB_IFACTOR); }
  uint getBlueI () const { return uint(b_*CRGB_IFACTOR); }

  void getRGB(double *r, double *g, double *b) const {
    *r = r_; *g = g_; *b = b_;
  }

  void getRGBI(uint *r, uint *g, uint *b) const {
    *r = uint(r_*CRGB_IFACTOR);
    *g = uint(g_*CRGB_IFACTOR);
    *b = uint(b_*CRGB_IFACTOR);
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

  double getGray() const {
    return (CRGB_R_FACTOR*r_ + CRGB_G_FACTOR*g_ + CRGB_B_FACTOR*b_);
  }

  double getClampGray() const {
    return getClamp().getGray();
  }

  CRGB getGrayRGB() const {
    double gray = getGray();

    return CRGB(gray, gray, gray);
  }

  double getLightRed() const {
    return std::min(r_*CRGB_LIGHT_FACTOR, 1.0);
  }

  double getLightGreen() const {
    return std::min(g_*CRGB_LIGHT_FACTOR, 1.0);
  }

  double getLightBlue() const {
    return std::min(b_*CRGB_LIGHT_FACTOR, 1.0);
  }

  double getLightGray() const {
    double gray = getGray();

    return std::min(gray*CRGB_LIGHT_FACTOR, 1.0);
  }

  CRGB getLightRGB() const {
    return CRGB(getLightRed(), getLightGreen(), getLightBlue());
  }

  double getDarkRed() const {
    return std::min(r_*CRGB_DARK_FACTOR, 1.0);
  }

  double getDarkGreen() const {
    return std::min(g_*CRGB_DARK_FACTOR, 1.0);
  }

  double getDarkBlue() const {
    return std::min(b_*CRGB_DARK_FACTOR, 1.0);
  }

  double getDarkGray() const {
    double gray = getGray();

    return std::min(gray*CRGB_DARK_FACTOR, 1.0);
  }

  CRGB getDarkRGB() const {
    return CRGB(getDarkRed(), getDarkGreen(), getDarkBlue());
  }

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

  CRGB getInverseRGB() const {
    return CRGB(getInverseRed(), getInverseGreen(), getInverseBlue());
  }

  const CRGB &toGray() {
    double gray = getGray();

    r_ = gray;
    g_ = gray;
    b_ = gray;

    return *this;
  }

  const CRGB &clamp() {
    r_ = std::max(0.0, std::min(1.0, r_));
    g_ = std::max(0.0, std::min(1.0, g_));
    b_ = std::max(0.0, std::min(1.0, b_));

    return *this;
  }

  CRGB getClamp() const {
    return CRGB(std::max(0.0, std::min(1.0, r_)),
                std::max(0.0, std::min(1.0, g_)),
                std::max(0.0, std::min(1.0, b_)));
  }

  CRGB blend(const CRGB &rgb, double factor) const {
    double factor1 = 1.0 - factor;

    return CRGB(r_*factor + rgb.r_*factor1,
                g_*factor + rgb.g_*factor1,
                b_*factor + rgb.b_*factor1);
  }

  const CRGB &invert() {
    r_ = 1.0 - r_;
    g_ = 1.0 - g_;
    b_ = 1.0 - b_;

    return *this;
  }

  CRGB inverse() const {
    CRGB rgb(*this);

    return rgb.invert();
  }

  const CRGB &toSepia() {
    r_ = r_*CRGB_SEPIA_R1 + CRGB_SEPIA_R2;
    g_ = g_*CRGB_SEPIA_G1 + CRGB_SEPIA_G2;
    b_ = b_*CRGB_SEPIA_B1 + CRGB_SEPIA_B2;

    return *this;
  }

  uint encodeRGB() const {
    uint r, g, b;

    getRGBI(&r, &g, &b);

    return encodeRGB(r, g, b);
  }

  static uint encodeRGB(uint r, uint g, uint b) {
    return (((r & 0xff) << 16) |
            ((g & 0xff) <<  8) |
            ((b & 0xff) <<  0));
  }

  static CRGB decodeRGB(uint rgb) {
    return CRGB(((rgb & 0xff0000) >> 16)/255.0,
                ((rgb & 0x00ff00) >>  8)/255.0,
                ((rgb & 0x0000ff) >>  0)/255.0);
  }

  //CHSV  toHSV () const;
  //CHSL  toHSL () const;
  //CCMYK toCMYK() const;
  //CHSB  toHSB () const;

  static CRGB minParts(const CRGB &rgb_s, const CRGB &rgb_d) {
    return CRGB(std::min(rgb_s.r_, rgb_d.r_),
                 std::min(rgb_s.g_, rgb_d.g_),
                 std::min(rgb_s.b_, rgb_d.b_));
  }

  static CRGB maxParts(const CRGB &rgb_s, const CRGB &rgb_d) {
    return CRGB(std::max(rgb_s.r_, rgb_d.r_),
                 std::max(rgb_s.g_, rgb_d.g_),
                 std::max(rgb_s.b_, rgb_d.b_));
  }

 private:
  double r_, g_, b_;
};

//------

#include <CRGBUtil.h>

//inline CHSV  CRGB::toHSV () const { return CRGBUtil::RGBtoHSV (*this); }
//inline CHSL  CRGB::toHSL () const { return CRGBUtil::RGBtoHSL (*this); }
//inline CCMYK CRGB::toCMYK() const { return CRGBUtil::RGBtoCMYK(*this); }
//inline CHSB  CRGB::toHSB () const { return CRGBUtil::RGBtoHSB (*this); }

#endif
