#ifndef CLINE_DASH_H
#define CLINE_DASH_H

#include <sys/types.h>

#include <CILineDash.h>

#include <vector>
#include <sstream>

class CLineDash {
 public:
  class Lengths {
    private:
     std::vector<double> lengths_;

    public:
     Lengths(double len, ...) :
      lengths_() {
       va_list vargs;

       va_start(vargs, len);

       while (len > 1E-3) {
         lengths_.push_back(len);

         len = va_arg(vargs, double);
       }
     }

     uint size() const {
       return lengths_.size();
     }

     double value(uint i) const {
       return lengths_[i];
     }
  };

 public:
  CLineDash() :
   lengths_ (),
   offset_  (0.0),
   ind_     (0),
   position_(0.0) {
    init();
  }

  CLineDash(const CLineDash &dash) :
   lengths_ (),
   offset_  (0.0),
   ind_     (0),
   position_(0.0) {
    init();

    copy(dash);
  }

  CLineDash(double *lengths, uint num_lengths, double offset=0.0) :
   lengths_ (),
   offset_  (0.0),
   ind_     (0),
   position_(0.0) {
    init();

    lengths_.resize(num_lengths);

    offset_ = offset;

    for (uint i = 0; i < num_lengths; ++i)
      lengths_[i] = lengths[i];
  }

  CLineDash(const Lengths &lengths, double offset=0.0) :
   lengths_ (),
   offset_  (0.0),
   ind_     (0),
   position_(0.0) {
    init();

    uint num_lengths = lengths.size();

    lengths_.resize(num_lengths);

    offset_ = offset;

    for (uint i = 0; i < num_lengths; ++i)
      lengths_[i] = lengths.value(i);
  }

  CLineDash(ushort pattern) :
   lengths_ (),
   offset_  (0.0),
   ind_     (0),
   position_(0.0) {
    init();

    setDashes(pattern);
  }

 ~CLineDash() { }

  CLineDash &operator=(const CLineDash &dash) {
    return copy(dash);
  }

  void init() {
    lengths_.clear();

    offset_   = 0.0;
    ind_      = 0;
    position_ = 0.0;
  }

  bool operator==(const CLineDash &dash) const {
    if (ind_      != dash.ind_     ) return false;
    if (position_ != dash.position_) return false;
    if (offset_   != dash.offset_  ) return false;

    if (lengths_.size() != dash.lengths_.size()) return false;

    uint num_lengths = lengths_.size();

    for (uint i = 0; i < num_lengths; ++i)
      if (lengths_[i] != dash.lengths_[i]) return false;

    return true;
  }

  void scale(double factor) {
    offset_ *= factor;

    uint num_lengths = lengths_.size();

    for (uint i = 0; i < num_lengths; ++i)
      lengths_[i] *= factor;
  }

  CLineDash &copy(const CLineDash &dash) {
    if (&dash == this)
      return *this;

    lengths_  = dash.lengths_;
    offset_   = dash.offset_;
    ind_      = dash.ind_;
    position_ = dash.position_;

    return *this;
  }

  double        getOffset    () const { return offset_; }
  const double *getLengths   () const { return &lengths_[0]; }
  uint          getNumLengths() const { return lengths_.size(); }
  int           getInd       () const { return ind_; }
  double        getPosition  () const { return position_; }

  double getLength(int i) const { return lengths_[i]; }

  void setOffset(double offset) { offset_ = offset; }
  void setInd   (uint ind)      { ind_    = ind; }

  bool isSolid() const { return lengths_.empty(); }

  bool isDraw() const { return isSolid() || ! (ind_ & 1); }

  double getDelta() const { return lengths_[ind_] - position_; }

  void step(double delta) const {
    if (delta <= 0.0)
      return;

    double delta1 = lengths_[ind_] - position_;

    while (delta > delta1) {
      step();

      delta -= delta1;

      delta1 = lengths_[ind_];
    }

    CLineDash *th = const_cast<CLineDash *>(this);

    th->position_ += delta;
  }

  void step() const {
    CLineDash *th = const_cast<CLineDash *>(this);

    ++th->ind_;

    uint num_lengths = lengths_.size();

    if (ind_ >= num_lengths)
      th->ind_ = 0;

    th->position_ = 0.0;
  }

  void setDashes(std::vector<double> &lengths, double offset=0.0) {
    lengths_ = lengths;
    offset_  = offset;

    updateInd();
  }

  void setDashes(double *lengths, uint num_lengths, double offset=0.0) {
    lengths_.resize(num_lengths);

    offset_ = offset;

    for (uint i = 0; i < num_lengths; ++i)
      lengths_[i] = lengths[i];

    updateInd();
  }

  void setDashes(ushort pattern) {
    int bits[16];

    for (uint i = 0; i < 16; ++i) {
      uint mask = 1 << i;

      bits[i] = (pattern & mask) ? 1 : 0;
    }

    lengths_.resize(16);

    double dash_value[16];

    uint num_lengths = 0;

    uint i = 0;

    while (i < 16) {
      lengths_  [num_lengths] = 0;
      dash_value[num_lengths] = bits[i];

      while (i < 16 && bits[i] == dash_value[num_lengths]) {
        ++lengths_[num_lengths];

        ++i;
      }

      ++num_lengths;
    }

    offset_ = 0.0;

    if (dash_value[0] == 0) {
      offset_ = lengths_[0];

      for (uint i = 1; i < num_lengths; ++i)
        lengths_[i - 1] = lengths_[i];

      lengths_[num_lengths - 1] = offset_;
    }

    if (num_lengths == 1) {
      offset_     = 0.0;
      num_lengths = 0;
    }

    if (num_lengths & 1) {
      offset_ += lengths_[num_lengths - 1];

      lengths_[0] += lengths_[num_lengths - 1];

      --num_lengths;
    }
  }

  CILineDash getIDash() const {
    uint num_lengths = lengths_.size();

    int *lengths = new int [num_lengths + 1];

    for (uint i = 0; i < num_lengths; ++i)
      lengths[i] = int(lengths_[i]);

    CILineDash line_dash(lengths, num_lengths, int(offset_));

    delete [] lengths;

    return line_dash;
  }

  std::string toString() const {
    if (isSolid()) return "solid";

    std::stringstream ss;

    uint num_lengths = lengths_.size();

    for (uint i = 0; i < num_lengths; ++i) {
      if (i > 0) ss << ", ";

      ss << lengths_[i];
    }

    return ss.str();
  }

  bool fromString(const std::string &str) {
    if (str == "solid") {
      init();

      return true;
    }

    std::vector<double> lengths;

    uint pos = 0;
    uint len = str.size();

    while (pos < len && isspace(str[pos])) ++pos;

    while (pos < len) {
      if (pos < len && ! isdigit(str[pos]))
        return false;

      double num = 0;

      while (pos < len && isdigit(str[pos]))
        num = num*10 + (str[pos++] - '0');

      if (pos < len && str[pos] == '.') {
        double dec = 0;

        double f = 0.1;

        ++pos;

        while (pos < len && isdigit(str[pos])) {
          dec += (str[pos++] - '0')*f;

          f /= 10.0;
        }

        num += pos;
      }

      while (pos < len && isspace(str[pos])) ++pos;

      if (pos < len && str[pos] == ',') {
        ++pos;

        while (pos < len && isspace(str[pos])) ++pos;
      }

      lengths.push_back(num);
    }

    setDashes(lengths);

    return true;
  }

 private:
  void updateInd() {
    ind_      = 0;
    position_ = offset_;

    uint num_lengths = lengths_.size();

    while (num_lengths > 0 && position_ >= lengths_[ind_]) {
      position_ -= lengths_[ind_];

      ++ind_;

      if (ind_ >= num_lengths)
        ind_ = 0;
    }
  }

 private:
  std::vector<double> lengths_;
  double              offset_;
  uint                ind_;
  double              position_;
};

#endif
