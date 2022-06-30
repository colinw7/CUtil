#ifndef CILineDash_H
#define CILineDash_H

#include <cstdarg>
#include <cstring>
#include <vector>
#include <sys/types.h>

class CILineDash {
 public:
  class Lengths {
    private:
     std::vector<int> lengths_;

    public:
     Lengths(int len, ...) :
      lengths_() {
       va_list vargs;

       va_start(vargs, len);

       while (len >= 0) {
         lengths_.push_back(len);

         len = va_arg(vargs, int);
       }

       va_end(vargs);
     }

     uint size() const {
       return uint(lengths_.size());
     }

     int value(uint i) const {
       return lengths_[i];
     }
  };

 public:
  CILineDash() {
    init();
  }

  CILineDash(const CILineDash &dash) {
    init();

    copy(dash);
  }

  CILineDash(int *lengths, uint num_lengths, int offset) {
    init();

    num_lengths_ = num_lengths;
    lengths_     = new int [num_lengths_ + 1];
    offset_      = offset;

    memcpy(lengths_, lengths, num_lengths*sizeof(int));
  }

  CILineDash(const Lengths &lengths, int offset) {
     init();

    num_lengths_ = lengths.size();
    lengths_     = new int [num_lengths_ + 1];
    offset_      = offset;

    for (uint i = 0; i < num_lengths_; ++i)
      lengths_[i] = lengths.value(i);
  }

  explicit CILineDash(ushort pattern) {
    init();

    int bits[16];

    for (uint i = 0; i < 16; ++i) {
      uint mask = 1 << i;

      bits[i] = (pattern & mask) ? 1 : 0;
    }

    lengths_ = new int [16];

    int dash_value[16];

    num_lengths_ = 0;

    uint i = 0;

    while (i < 16) {
      lengths_  [num_lengths_] = 0;
      dash_value[num_lengths_] = bits[i];

      while (i < 16 && bits[i] == dash_value[num_lengths_]) {
        ++lengths_[num_lengths_];

        ++i;
      }

      ++num_lengths_;
    }

    offset_ = 0;

    if (dash_value[0] == 0) {
      offset_ = lengths_[0];

      for (uint il = 1; il < num_lengths_; ++il)
        lengths_[il - 1] = lengths_[il];

      lengths_[num_lengths_ - 1] = offset_;
    }

    if (num_lengths_ == 1) {
      offset_      = 0;
      num_lengths_ = 0;
    }

    if (num_lengths_ & 1) {
      offset_ += lengths_[num_lengths_ - 1];

      lengths_[0] += lengths_[num_lengths_ - 1];

      --num_lengths_;
    }
  }

 ~CILineDash() {
    delete [] lengths_;
  }

  CILineDash &operator=(const CILineDash &dash) {
    return copy(dash);
  }

  void init() {
    lengths_     = nullptr;
    num_lengths_ = 0;
    offset_      = 0;
    ind_         = 0;
    position_    = 0;
  }

  void scale(int factor) {
    offset_ *= factor;

    for (uint i = 0; i < num_lengths_; ++i)
      lengths_[i] *= factor;
  }

  CILineDash &copy(const CILineDash &dash) {
    if (&dash == this)
      return *this;

    if (lengths_ != NULL)
      delete [] lengths_;

    lengths_     = new int [dash.num_lengths_];
    num_lengths_ = dash.num_lengths_;
    offset_      = dash.offset_;
    ind_         = dash.ind_;
    position_    = dash.position_;

    memcpy(lengths_, dash.lengths_, num_lengths_*sizeof(int));

    return *this;
  }

  int   getOffset    () const { return offset_; }
  int  *getLengths   () const { return lengths_; }
  uint  getNumLengths() const { return num_lengths_; }
  uint   getInd      () const { return ind_; }
  int   getPosition  () const { return position_; }

  int getLength(int i) const { return lengths_[i]; }

  void setOffset(int offset) { offset_ = offset; }
  void setInd   (uint ind)   { ind_    = ind; }

  bool isSolid() const { return num_lengths_ == 0; }

  bool isDraw() const { return isSolid() || ! (ind_ & 1); }

  int getDelta() const { return lengths_[ind_] - position_; }

  void step(int delta) const {
    if (delta <= 0 || isSolid())
      return;

    int delta1 = lengths_[ind_] - position_;

    while (delta > delta1) {
      step();

      delta -= delta1;

      delta1 = lengths_[ind_];
    }

    CILineDash *th = const_cast<CILineDash *>(this);

    th->position_ += delta;
  }

  void step() const {
    CILineDash *th = const_cast<CILineDash *>(this);

    ++th->ind_;

    if (ind_ >= num_lengths_)
      th->ind_ = 0;

    th->position_ = 0;
  }

  void setDashes(std::vector<int> &lengths, int offset=0) {
    delete [] lengths_;

    num_lengths_ = uint(lengths.size());
    lengths_     = new int [num_lengths_];
    offset_      = offset;

    for (uint i = 0; i < num_lengths_; ++i)
      lengths_[i] = lengths[i];

    updateInd();
  }

  void setDashes(int *lengths, uint num_lengths, int offset=0) {
    delete [] lengths_;

    num_lengths_ = num_lengths;
    lengths_     = new int [num_lengths_];
    offset_      = offset;

    memcpy(lengths_, lengths, num_lengths_*sizeof(int));

    updateInd();
  }

  ushort getShortPattern(int &factor) const {
    factor = 1;

    ushort pattern = 0;

    int bit = 0;

    if (offset_ > 0)
      bit += offset_;

    for (uint i = 0; i < num_lengths_; i += 2) {
      for (int j = 0; j < lengths_[i]; ++j) {
        pattern |= (1 << bit);

        ++bit;
      }

      for (int j = 0; j < lengths_[i]; ++j)
        ++bit;
    }

    return pattern;
  }

 private:
  void updateInd() {
    ind_      = 0;
    position_ = offset_;

    while (num_lengths_ > 0 && position_ >= lengths_[ind_]) {
      position_ -= lengths_[ind_];

      ++ind_;

      if (ind_ >= num_lengths_)
        ind_ = 0;
    }
  }

 private:
  int  *lengths_     { nullptr };
  uint  num_lengths_ { 0 };
  int   offset_      { 0 };
  uint  ind_         { 0 };
  int   position_    { 0 };
};

#endif
