#ifndef CTextBox_H
#define CTextBox_H

#include <iostream>

class CTextBox {
 public:
  CTextBox() { }

  CTextBox(int w, int h) :
   x_(0), y_(0), width_(w), ascent_(h), descent_(0) {
  }

  CTextBox(int x, int y, int w, int h) :
   x_(x), y_(y), width_(w), ascent_(h), descent_(0) {
  }

  CTextBox(int x, int y, int w, int a, int d) :
   x_(x), y_(y), width_(w), ascent_(a), descent_(d) {
  }

  int x() const { return x_; }
  void setX(int x1) { x_ = x1; }

  int y() const { return y_; }
  void setY(int y1) { y_ = y1; }

  int width() const { return width_; }
  void setWidth(int w) { width_ = w; }

  int ascent() const { return ascent_; }
  void setAscent(int a) { ascent_ = a; }

  int descent() const { return descent_; }
  void setDescent(int d) { descent_ = d; }

  int height() const { return ascent() + descent(); }
  void setHeight(int h) { ascent_ = h; descent_ = 0; }

  int xmin() const { return x(); }
  int ymin() const { return y(); }
  int xmax() const { return x() + width (); }
  int ymax() const { return y() + height(); }

  int left  () const { return xmin(); }
  int bottom() const { return ymin(); }
  int right () const { return xmax(); }
  int top   () const { return ymax(); }

  int xmid() const { return (xmin() + xmax())/2; }
  int ymid() const { return (ymin() + ymax())/2; }

  void reset() {
    x_       = 0;
    y_       = 0;
    width_   = 0;
    ascent_  = 0;
    descent_ = 0;
  }

  void setSize(int w, int h) {
    setWidth (w);
    setHeight(h);
  }

  void resetSize() {
    width_   = 0;
    ascent_  = 0;
    descent_ = 0;
  }

  bool insideX(int x) const { return (x >= xmin() && x <= xmax()); }
  bool insideY(int y) const { return (y >= ymin() && y <= ymax()); }

  bool inside(int x, int y) const { return insideX(x) && insideY(y); }

  void print(std::ostream &os) const {
    os << "(" << x() << "," << y() << ") ";
    os << "(" << width() << "," << ascent() << "," << descent() << ")";
  }

  friend std::ostream &operator<<(std::ostream &os, const CTextBox &box) {
    box.print(os);

    return os;
  }

  friend bool operator==(const CTextBox &lhs, const CTextBox &rhs) {
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.width() == rhs.width() &&
            lhs.ascent() == rhs.ascent() && lhs.descent() == rhs.descent());
  }

  friend bool operator!=(const CTextBox &lhs, const CTextBox &rhs) {
    return ! (lhs == rhs);
  }

 private:
  int x_       { 0 };
  int y_       { 0 };
  int width_   { 0 };
  int ascent_  { 0 };
  int descent_ { 0 };
};

#endif
