#ifndef CRGB_H
#define CRGB_H

#include <cstdio>
#include <iostream>
#include <sys/types.h>

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

template<typename T>
class CRGBT {
 private:
  T r_, g_, b_;

 public:
  CRGBT() { }

  CRGBT(T r, T g, T b) :
   r_(r), g_(g), b_(b) {
  }

  explicit CRGBT(T gray) :
   r_(gray), g_(gray), b_(gray) {
  }

  CRGBT(const CRGBT &rgb) :
   r_(rgb.r_), g_(rgb.g_), b_(rgb.b_) {
  }

 ~CRGBT() { }

  CRGBT &operator=(const CRGBT &rgb) {
    if (this == &rgb)
      return *this;

    r_ = rgb.r_;
    g_ = rgb.g_;
    b_ = rgb.b_;

    return *this;
  }

  CRGBT operator+() const {
    return CRGBT(r_, g_, b_);
  }

  CRGBT operator-() const {
    return CRGBT(-r_, -g_, -b_);
  }

  CRGBT &operator+=(const CRGBT &rhs) {
    r_ += rhs.r_;
    g_ += rhs.g_;
    b_ += rhs.b_;

    return *this;
  }

  CRGBT operator+(const CRGBT &rhs) const {
    return CRGBT(r_ + rhs.r_, g_ + rhs.g_, b_ + rhs.b_);
  }

  CRGBT &operator-=(const CRGBT &rhs) {
    r_ -= rhs.r_;
    g_ -= rhs.g_;
    b_ -= rhs.b_;

    return *this;
  }

  CRGBT operator-(const CRGBT &rhs) const {
    return CRGBT(r_ - rhs.r_, g_ - rhs.g_, b_ - rhs.b_);
  }

  CRGBT &operator*=(const CRGBT &rhs) {
    r_ *= rhs.r_;
    g_ *= rhs.g_;
    b_ *= rhs.b_;

    return *this;
  }

  CRGBT &operator*=(T rhs) {
    r_ *= rhs;
    g_ *= rhs;
    b_ *= rhs;

    return *this;
  }

  CRGBT operator*(const CRGBT &rhs) const {
    return CRGBT(r_*rhs.r_, g_*rhs.g_, b_*rhs.b_);
  }

  CRGBT &operator/=(const CRGBT &rhs) {
    r_ /= rhs.r_;
    g_ /= rhs.g_;
    b_ /= rhs.b_;

    return *this;
  }

  CRGBT &operator/=(T rhs) {
    T irhs = 1.0/rhs;

    r_ *= irhs;
    g_ *= irhs;
    b_ *= irhs;

    return *this;
  }

  CRGBT operator/(const CRGBT &rhs) const {
    return CRGBT(r_/rhs.r_, g_/rhs.g_, b_/rhs.b_);
  }

  CRGBT operator/(T rhs) const {
    T irhs = 1.0/rhs;

    return CRGBT(r_*irhs, g_*irhs, b_*irhs);
  }

  //------

  int cmp(const CRGBT &rhs) const {
    if      (r_ < rhs.r_) return -1;
    else if (r_ > rhs.r_) return 1;
    else if (g_ < rhs.g_) return -1;
    else if (g_ > rhs.g_) return 1;
    else if (b_ < rhs.b_) return -1;
    else if (b_ > rhs.b_) return 1;
    else                  return 0;
  }

  friend bool operator==(const CRGBT &lhs, const CRGBT &rhs) {
    return lhs.cmp(rhs) == 0;
  }

  friend bool operator!=(const CRGBT &lhs, const CRGBT &rhs) {
    return lhs.cmp(rhs) != 0;
  }

  friend bool operator<(const CRGBT &lhs, const CRGBT &rhs) {
    return lhs.cmp(rhs) < 0;
  }

  friend bool operator<=(const CRGBT &lhs, const CRGBT &rhs) {
    return lhs.cmp(rhs) <= 0;
  }

  friend bool operator>(const CRGBT &lhs, const CRGBT &rhs) {
    return lhs.cmp(rhs) > 0;
  }

  friend bool operator>=(const CRGBT &lhs, const CRGBT &rhs) {
    return lhs.cmp(rhs) >= 0;
  }

  //------

  friend CRGBT operator*(const CRGBT &lhs, T rhs) {
    return CRGBT(lhs.r_*rhs, lhs.g_*rhs, lhs.b_*rhs);
  }

  friend CRGBT operator*(T lhs, const CRGBT &rhs) {
    return CRGBT(lhs*rhs.r_, lhs*rhs.g_, lhs*rhs.b_);
  }

  void print(std::ostream &os) const {
    os << "CRGB(" << r_ << "," << g_ << "," << b_ << ")";
  }

  friend std::ostream &operator<<(std::ostream &os, const CRGBT &rgb) {
    rgb.print(os);

    return os;
  }

  std::string toString() const {
    char buffer[16];

    uint r, g, b;

    getRGBI(&r, &g, &b);

    sprintf(buffer, "#%02X%02X%02X", r, g, b);

    return buffer;
  }

  void zero() { r_ = g_ = b_ = 0.0; }

  void setRed  (T r) { r_ = r; };
  void setGreen(T g) { g_ = g; };
  void setBlue (T b) { b_ = b; };

  void setRGB(T r, T g, T b) {
    r_ = r; g_ = g; b_ = b;
  }

  void setRGBI(uint r, uint g, uint b) {
    r_ = int(r/255.0); g_ = int(g/255.0); b_ = int(b/255.0);
  }

  T getRed  () const { return r_; }
  T getGreen() const { return g_; }
  T getBlue () const { return b_; }

  uint getRedI  () const { return uint(r_*CRGB_IFACTOR); }
  uint getGreenI() const { return uint(g_*CRGB_IFACTOR); }
  uint getBlueI () const { return uint(b_*CRGB_IFACTOR); }

  void getRGB(T *r, T *g, T *b) const {
    *r = r_; *g = g_; *b = b_;
  }

  void getRGBI(uint *r, uint *g, uint *b) const {
    *r = uint(r_*CRGB_IFACTOR);
    *g = uint(g_*CRGB_IFACTOR);
    *b = uint(b_*CRGB_IFACTOR);
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

  T getGray() const {
    return (CRGB_R_FACTOR*r_ + CRGB_G_FACTOR*g_ + CRGB_B_FACTOR*b_);
  }

  T getClampGray() const {
    return getClamp().getGray();
  }

  CRGBT getGrayRGB() const {
    T gray = getGray();

    return CRGBT(gray, gray, gray);
  }

  T getLightRed() const {
    return std::min(r_*CRGB_LIGHT_FACTOR, 1.0);
  }

  T getLightGreen() const {
    return std::min(g_*CRGB_LIGHT_FACTOR, 1.0);
  }

  T getLightBlue() const {
    return std::min(b_*CRGB_LIGHT_FACTOR, 1.0);
  }

  T getLightGray() const {
    T gray = getGray();

    return std::min(gray*CRGB_LIGHT_FACTOR, 1.0);
  }

  CRGBT getLightRGB() const {
    return CRGBT(getLightRed(), getLightGreen(), getLightBlue());
  }

  T getDarkRed() const {
    return std::min(r_*CRGB_DARK_FACTOR, 1.0);
  }

  T getDarkGreen() const {
    return std::min(g_*CRGB_DARK_FACTOR, 1.0);
  }

  T getDarkBlue() const {
    return std::min(b_*CRGB_DARK_FACTOR, 1.0);
  }

  T getDarkGray() const {
    T gray = getGray();

    return std::min(gray*CRGB_DARK_FACTOR, 1.0);
  }

  CRGBT getDarkRGB() const {
    return CRGBT(getDarkRed(), getDarkGreen(), getDarkBlue());
  }

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

  CRGBT getInverseRGB() const {
    return CRGBT(getInverseRed(), getInverseGreen(), getInverseBlue());
  }

  const CRGBT &toGray() {
    T gray = getGray();

    r_ = gray;
    g_ = gray;
    b_ = gray;

    return *this;
  }

  const CRGBT &clamp() {
    r_ = std::max(0.0, std::min(1.0, r_));
    g_ = std::max(0.0, std::min(1.0, g_));
    b_ = std::max(0.0, std::min(1.0, b_));

    return *this;
  }

  CRGBT getClamp() const {
    return CRGBT(std::max(0.0, std::min(1.0, r_)),
                 std::max(0.0, std::min(1.0, g_)),
                 std::max(0.0, std::min(1.0, b_)));
  }

  CRGBT blend(const CRGBT &rgb, T factor) const {
    T factor1 = 1.0 - factor;

    return CRGBT(r_*factor + rgb.r_*factor1,
                 g_*factor + rgb.g_*factor1,
                 b_*factor + rgb.b_*factor1);
  }

  const CRGBT &invert() {
    r_ = 1.0 - r_;
    g_ = 1.0 - g_;
    b_ = 1.0 - b_;

    return *this;
  }

  CRGBT inverse() const {
    CRGBT rgb(*this);

    return rgb.invert();
  }

  const CRGBT &toSepia() {
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

  static CRGBT decodeRGB(uint rgb) {
    return CRGBT(((rgb & 0xff0000) >> 16)/255.0,
                 ((rgb & 0x00ff00) >>  8)/255.0,
                 ((rgb & 0x0000ff) >>  0)/255.0);
  }
};

typedef CRGBT<double> CRGB;

#endif
