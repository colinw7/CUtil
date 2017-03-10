#ifndef CMULT_ARRAY_H
#define CMULT_ARRAY_H

#include <CRefPtr.h>
#include <vector>
#include <cstring>

template<class T>
class CMultiArrayT {
 private:
  struct Dims {
    uint  dims_buffer[3];
    uint *dims;
    uint  num_dims;
    uint  num_data;

    Dims() {
      num_dims = 0;

      init();

      setNumData();
    }

    explicit Dims(uint d1) {
      num_dims = 1;

      init();

      dims[0] = d1;

      setNumData();
    }

    Dims(uint d1, uint d2) {
      num_dims = 2;

      init();

      dims[0] = d1;
      dims[1] = d2;

      setNumData();
    }

    Dims(uint d1, uint d2, uint d3) {
      num_dims = 3;

      init();

      dims[0] = d1;
      dims[1] = d2;
      dims[2] = d3;

      setNumData();
    }

    Dims(const uint *dims1, uint num_dims1) {
      num_dims = num_dims1;

      init();

      if (num_dims > 0)
        memcpy(dims, dims1, num_dims*sizeof(dims[0]));

      setNumData();
    }

    explicit Dims(const std::vector<uint> &dims1) {
      num_dims = dims1.size();

      init();

      std::vector<uint>::const_iterator p1 = dims1.begin();
      std::vector<uint>::const_iterator p2 = dims1.end  ();

      for (uint i = 0; p1 != p2; ++p1, ++i)
        dims[i] = *p1;

      setNumData();
    }

    Dims(const Dims &dims1) {
      num_dims = dims1.num_dims;

      init();

      if (num_dims > 0)
        memcpy(dims, dims1.dims, num_dims*sizeof(dims1.dims[0]));

      setNumData();
    }

   ~Dims() {
      if (num_dims > 3)
        delete [] dims;
    }

    Dims &operator=(const Dims &dims1) {
      if (num_dims > 3)
        delete [] dims;

      num_dims = dims1.num_dims;

      init();

      if (num_dims > 0)
        memcpy(dims, dims1.dims, num_dims*sizeof(dims1.dims[0]));

      setNumData();

      return *this;
    }

    void init() {
      if (num_dims <= 3)
        dims = dims_buffer;
      else
        dims = new uint [num_dims];
    }

    void setNumData() {
      num_data = (num_dims > 0 ? dims[0] : 0);

      for (uint i = 1; i < num_dims; ++i)
        num_data *= dims[i];
    }

    void getDims(std::vector<uint> &dims1) const {
      for (uint i = 0; i < num_dims; ++i)
        dims1.push_back(dims[i]);
    }

    bool operator==(const Dims &dims) const {
      if (num_data != dims.num_data || num_dims != dims.num_dims)
        return false;

      for (uint i = 0; i < num_dims; ++i)
        if (dims[i] != dims.dims[i])
          return false;

      return true;
    }
  };

  //--------

  struct Slice {
    uint  start_buffer[3];
    uint  len_buffer[3];

    uint *start;
    uint *len;
    uint  num;

    Slice() :
     start(nullptr), len(nullptr), num(0) {
    }

    Slice(uint start1, uint len1) {
      start_buffer[0] = start1;
      len_buffer  [0] = len1;

      start = start_buffer;
      len   = len_buffer  ;
      num   = 1           ;
    }

    Slice(uint start1, uint len1, uint start2, uint len2) {
      start_buffer[0] = start1;
      len_buffer  [0] = len1;
      start_buffer[1] = start2;
      len_buffer  [1] = len2;

      start = start_buffer;
      len   = len_buffer  ;
      num   = 2           ;
    }

    Slice(uint start1, uint len1, uint start2, uint len2,
          uint start3, uint len3) {
      start_buffer[0] = start1;
      len_buffer  [0] = len1;
      start_buffer[1] = start2;
      len_buffer  [1] = len2;
      start_buffer[2] = start3;
      len_buffer  [2] = len3;

      start = start_buffer;
      len   = len_buffer  ;
      num   = 3           ;
    }

    Slice(const uint *start1, const uint *len1, uint num1) {
      num = num1;

      if (num < 3) {
        start = start_buffer;
        len   = len_buffer  ;
      }
      else {
        start = new uint [num];
        len   = new uint [num];
      }

      memcpy(start, start1, num*sizeof(uint));
      memcpy(len  , len1  , num*sizeof(uint));
    }

    Slice(const std::vector<uint> &start1, const std::vector<uint> &len1) {
      num = start1.size();

      if (num < 3) {
        start = start_buffer;
        len   = len_buffer  ;
      }
      else {
        start = new uint [num];
        len   = new uint [num];
      }

      for (uint i = 0; i < num; ++i) {
        start[i] = start1[i];
        len  [i] = len1  [i];
      }
    }

    Slice(const Slice &slice) {
      if (slice.num > 3) {
        start = new uint [slice.num];
        len   = new uint [slice.num];

        memcpy(start, slice.start, slice.num*sizeof(uint));
        memcpy(len  , slice.len  , slice.num*sizeof(uint));
      }
      else {
        memcpy(start_buffer, slice.start_buffer, 3*sizeof(uint));
        memcpy(len_buffer  , slice.len_buffer  , 3*sizeof(uint));

        start = start_buffer;
        len   = len_buffer  ;
      }

      num = slice.num;
    }

   ~Slice() {
      if (num > 3)
        delete [] start;

      if (num > 3)
        delete [] len;
    }

    Slice &operator=(const Slice &slice) {
      if (num > 3)
        delete [] start;

      if (num > 3)
        delete [] len;

      if (slice.num > 3) {
        start = new uint [slice.num];
        len   = new uint [slice.num];

        memcpy(start, slice.start, slice.num*sizeof(uint));
        memcpy(len  , slice.len  , slice.num*sizeof(uint));
      }
      else {
        memcpy(start_buffer, slice.start_buffer, 3*sizeof(uint));
        memcpy(len_buffer  , slice.len_buffer  , 3*sizeof(uint));

        start = start_buffer;
        len   = len_buffer  ;
      }

      num = slice.num;

      return *this;
    }

    void print(std::ostream &os) const {
      for (uint i = 0; i < num; ++i)
        os << "(" << start[i] << ", " << start[i] + len[i] << ")";
    }

    friend std::ostream &operator<<(std::ostream &os, const Slice &slice) {
      slice.print(os);

      return os;
    }
  };

  typedef std::vector<Slice> SliceList;

  //--------

  class Data {
   public:
    class Iterator {
     private:
      Data *data_;
      uint *dims_;
      bool *mask_;
      uint *dims1_;
      uint  num_dims_;
      uint  num_data_;
      uint  pos_;

     public:
      Iterator(const Data &data, uint *dims, bool *mask, uint *dims1) :
       dims_(dims), mask_(mask), dims1_(dims1), pos_(0) {
        data_ = const_cast<Data *>(&data);

        num_dims_ = data_->dims_.num_dims;
        num_data_ = data_->dims_.num_data;
      }

      bool begin() {
        pos_ = 0;

        memset(dims1_, 0, num_dims_*sizeof(uint));

        while (pos_ < num_data_ && mask_[pos_])
          ++pos_;

        return (pos_ < num_data_);
      }

      bool next() {
        incPos();

        ++pos_;

        while (pos_ < num_data_ && mask_[pos_])
          ++pos_;

        return (pos_ < num_data_);
      }

     private:
      void incPos() {
        assert(num_dims_ > 0);

        ++dims1_[0];

        if (dims1_[0] >= dims_[0] && num_dims_ > 1) {
          uint d1 = 1;

          ++dims1_[d1];

          while (dims1_[d1] >= dims_[d1] && d1 < num_dims_ - 1) {
            ++d1;

            ++dims1_[d1];
          }

          for (uint d2 = 0; d2 < d1; ++d2)
            dims1_[d2] = 0;
        }
      }

     public:
      bool isPos(const Dims &pos) const {
        for (uint i = 0; i < num_dims_; ++i)
          if (dims1_[i] != pos.dims[i])
            return false;

        return true;
      }

      bool isLinearPos(uint pos) const {
        return (pos_ == pos);
      }

      uint *dims() const { return dims1_; }

      uint numDims() const { return num_dims_; }

      uint pos() const { return pos_; }

      bool isStartPos() {
        return (dims1_[0] == 0);
      }
    };

    //--------

   private:
    Dims  dims_;
    T    *data_;

   public:
    Data() {
      init(nullptr);
    }

    Data(uint d1, const T *data) :
     dims_(d1) {
      init(data);
    }

    Data(uint d1, uint d2, const T *data) :
     dims_(d1, d2) {
      init(data);
    }

    Data(uint d1, uint d2, uint d3, const T *data) :
     dims_(d1, d2, d3) {
      init(data);
    }

    Data(const uint *dims, uint num_dims, const T *data) :
     dims_(dims, num_dims) {
      init(data);
    }

    Data(const uint *dims, uint num_dims, const std::vector<T> &data) :
     dims_(dims, num_dims) {
      init(data);
    }

    Data(const uint *dims, uint num_dims, const T &data) :
     dims_(dims, num_dims) {
      init(data);
    }

    Data(const std::vector<uint> &dims, const T *data) :
     dims_(dims) {
      init(data);
    }

    Data(const std::vector<uint> &dims, const std::vector<T> &data) :
     dims_(dims) {
      init(data);
    }

    Data(const std::vector<uint> &dims, const T &data) :
     dims_(dims) {
      init(data);
    }

    Data(const Data &data) :
     dims_(data.dims_) {
      init(data.data_);
    }

   ~Data() {
      delete [] data_;
    }

    Data &operator=(const Data &data) {
      delete [] data_;

      dims_ = data.dims_;

      init(data.data_);

      return *this;
    }

    Data *dup() const {
      return new Data(*this);
    }

    uint getNumDims() const {
      return dims_.num_dims;
    }

    uint getNumData() const {
      return dims_.num_data;
    }

    uint *getDims() const {
      return dims_.dims;
    }

    void getDims(uint **dims, uint *num_dims) const {
      *dims     = dims_.dims;
      *num_dims = dims_.num_dims;
    }

    void getDims(std::vector<uint> &dims) const {
      for (uint i = 0; i < dims_.num_dims; ++i)
        dims.push_back(dims_.dims[i]);
    }

    uint getDim(uint i) const {
      return dims_.dims[i];
    }

    const T &getLinearValue(uint ind) const {
      assert(ind < dims_.num_data);

      return data_[ind];
    }

    void setLinearValue(uint ind, const T &value) {
      assert(ind < dims_.num_data);

      data_[ind] = value;
    }

    const T &getValue(uint s1) const {
      assert(dims_.num_dims == 1);

      return getValue(Dims(s1));
    }

    const T &getValue(uint s1, uint s2) const {
      assert(dims_.num_dims == 2);

      return getValue(Dims(s1, s2));
    }

    const T &getValue(uint s1, uint s2, uint s3) const {
      assert(dims_.num_dims == 3);

      return getValue(Dims(s1, s2, s3));
    }

    const T &getValue(uint *subscripts, uint num_subscripts) const {
      return getValue(Dims(subscripts, num_subscripts));
    }

   private:
    void init(const T *data) {
      data_ = new T [dims_.num_data];

      if (data) {
        for (uint i = 0; i < dims_.num_data; ++i)
          data_[i] = data[i];
      }
    }

    void init(const std::vector<T> &data) {
      data_ = new T [dims_.num_data];

      for (uint i = 0; i < dims_.num_data; ++i)
        data_[i] = data[i];
    }

    void init(const T &data) {
      data_ = new T [dims_.num_data];

      for (uint i = 0; i < dims_.num_data; ++i)
        data_[i] = data;
    }

    const T &getValue(const Dims & /*dims*/) const {
      return data_[0];
    }
  };

  //-------

 private:
  CRefPtr<Data>  data_;
  uint          *dims_;
  SliceList      slices_;
  bool          *mask_;
  uint           dims1_buffer_[3];
  uint          *dims1_;

  //--------

 public:
  typedef typename Data::Iterator DataIterator;

  CMultiArrayT() {
    data_ = new Data;

    init();
  }

  CMultiArrayT(uint d1, const T *data=nullptr) {
    data_ = new Data(d1, data);

    init();
  }

  CMultiArrayT(uint d1, uint d2, const T *data=nullptr) {
    data_ = new Data(d1, d2, data);

    init();
  }

  CMultiArrayT(uint d1, uint d2, uint d3, const T *data=nullptr) {
    data_ = new Data(d1, d2, d3, data);

    init();
  }

  CMultiArrayT(const uint *dims, uint num_dims, const T *data=nullptr) {
    data_ = new Data(dims, num_dims, data);

    init();
  }

  CMultiArrayT(const uint *dims, uint num_dims, const std::vector<T> &data) {
    data_ = new Data(dims, num_dims, data);

    init();
  }

  CMultiArrayT(const uint *dims, uint num_dims, const T &data) {
    data_ = new Data(dims, num_dims, data);

    init();
  }

  CMultiArrayT(const std::vector<uint> &dims, const T *data=nullptr) {
    data_ = new Data(dims, data);

    init();
  }

  CMultiArrayT(const std::vector<uint> &dims, const std::vector<T> &data) {
    data_ = new Data(dims, data);

    init();
  }

  CMultiArrayT(const std::vector<uint> &dims, const T &data) {
    data_ = new Data(dims, data);

    init();
  }

  CMultiArrayT(const CMultiArrayT &array) {
    data_ = new Data(*array.data_);

    init();
  }

 ~CMultiArrayT() {
    delete [] mask_;

    uint num_dims = getNumDims();

    if (num_dims > 3)
      delete [] dims1_;
  }

  const CMultiArrayT &operator=(const CMultiArrayT &array) {
    delete [] mask_;

    uint num_dims = getNumDims();

    if (num_dims > 3)
      delete [] dims1_;

    data_ = array.data_;

    data_.uniquify();

    init();

    return *this;
  }

  CMultiArrayT *slice(uint pos) const {
    return slice(pos, pos);
  }

  void slice(uint pos, CMultiArrayT &sarray) const {
    slice(pos, pos, sarray);
  }

  CMultiArrayT *slice(uint start, uint end) const {
    CMultiArrayT *array = new CMultiArrayT(data_);

    array->addSlice(start, end);

    return array;
  }

  void slice(uint start, uint end, CMultiArrayT &sarray) const {
    sarray = CMultiArrayT(data_);

    sarray.addSlice(start, end);
  }

  CMultiArrayT *slice(const uint *positions, uint num) const {
    CMultiArrayT *array = new CMultiArrayT(data_);

    array->addSlice(positions, positions, num);

    return array;
  }

  void slice(const uint *positions, uint num, CMultiArrayT &sarray) const {
    sarray = CMultiArrayT(data_);

    sarray.addSlice(positions, positions, num);
  }

  void slice(const std::vector<uint> &positions, CMultiArrayT &sarray) const {
    sarray = CMultiArrayT(data_);

    sarray.addSlice(positions, positions);
  }

  CMultiArrayT *slice(const uint *starts, uint *ends, uint num) const {
    CMultiArrayT *array = new CMultiArrayT(data_);

    array->addSlice(starts, ends, num);

    return array;
  }

  void slice(const uint *starts, uint *ends, uint num,
             CMultiArrayT &sarray) const {
    sarray = CMultiArrayT(data_);

    sarray.addSlice(starts, ends, num);
  }

  void addSlice(uint start, uint end) {
    assert(getNumDims() == 1);

    slices_.push_back(Slice(start, end - start + 1));

    setMask();
  }

  void addSlice(uint start1, uint end1, uint start2, uint end2) {
    assert(getNumDims() == 2);

    slices_.push_back(Slice(start1, end1 - start1 + 1,
                            start2, end2 - start2 + 1));

    setMask();
  }

  void addSlice(uint start1, uint end1, uint start2, uint end2,
                uint start3, uint end3) {
    assert(getNumDims() == 3);

    slices_.push_back(Slice(start1, end1 - start1 + 1,
                            start2, end2 - start2 + 1,
                            start3, end3 - start3 + 1));

    setMask();
  }

  void addSlice(const uint *starts, const uint *ends, uint num) {
    Slice slice(starts, ends, num);

    for (uint i = 0; i < num; ++i)
      slice.len[i] -= starts[i] - 1;

    slices_.push_back(slice);

    setMask();
  }

  void addSlice(const std::vector<uint> &starts, const std::vector<uint> &ends) {
    Slice slice(starts, ends);

    uint num = starts.size();

    for (uint i = 0; i < num; ++i)
      slice.len[i] -= starts[i] - 1;

    slices_.push_back(slice);

    setMask();
  }

  CMultiArrayT flattened() {
    std::vector<T> data;

    DataIterator i(*data_, dims_, mask_, dims1_);

    uint num_dims = i.numDims();

    std::vector<uint> dims;

    for (uint d = 0; d < num_dims; ++d)
      dims.push_back(0);

    for (bool b = i.begin(); b; b = i.next()) {
      uint *dims1 = i.dims();

      for (uint d = 0; d < num_dims; ++d)
        dims[d] = std::max(dims[d], dims1[d] + 1);

      const T &value = data_->getLinearValue(i.pos());

      data.push_back(value);
    }

    return CMultiArrayT(dims, data);
  }

  bool getLinearValue(uint ind, T &value) const {
    return getLinearValueI(ind, value);
  }

  bool getValue(uint s1, T &value) const {
    assert(getNumDims() == 1);

    return getValueI(Dims(s1), value);
  }

  bool getValue(uint s1, uint s2, T &value) const {
    assert(getNumDims() == 2);

    return getValueI(Dims(s1, s2), value);
  }

  bool getValue(uint s1, uint s2, uint s3, T &value) const {
    assert(getNumDims() == 3);

    return getValueI(Dims(s1, s2, s3), value);
  }

  bool getValue(uint *subscripts, uint num_subscripts, T &value) const {
    return getValueI(Dims(subscripts, num_subscripts), value);
  }

  bool setLinearValue(uint ind, const T &value) {
    return setLinearValueI(ind, value);
  }

  bool setValue(uint s1, const T &value) {
    assert(getNumDims() == 1);

    return setValueI(Dims(s1), value);
  }

  bool setValue(uint s1, uint s2, const T &value) {
    assert(getNumDims() == 2);

    return setValueI(Dims(s1, s2), value);
  }

  bool setValue(uint s1, uint s2, uint s3, const T &value) {
    assert(getNumDims() == 3);

    return setValueI(Dims(s1, s2, s3), value);
  }

  bool setValue(uint *subscripts, uint num_subscripts, const T &value) {
    return setValueI(Dims(subscripts, num_subscripts), value);
  }

  bool setValue(const std::vector<uint> &subscripts, const T &value) {
    return setValueI(Dims(subscripts), value);
  }

  bool subscriptToIndex(uint *subscripts, uint num_subscripts, uint *ind) {
    return dimsToPos(Dims(subscripts, num_subscripts), ind);
  }

  bool subscriptToIndex(const std::vector<uint> &subscripts, uint *ind) {
    return dimsToPos(Dims(subscripts), ind);
  }

  uint getNumDims() const {
    return data_->getNumDims();
  }

  uint getNumData() const {
    return data_->getNumData();
  }

  uint *getDims() const {
    return data_->getDims();
  }

  void getDims(uint **dims, uint *num_dims) const {
    data_->getDims(dims, num_dims);
  }

  void getDims(std::vector<uint> &dims) const {
    data_->getDims(dims);
  }

  uint getDim(uint i) const {
    return data_->getDim(i);
  }

  bool sameDimension(const CMultiArrayT &array) const {
    if (getNumData() != array.getNumData() ||
        getNumDims() != array.getNumDims())
      return false;

    for (uint i = 0; i < getNumDims(); ++i)
      if (getDim(i) != array.getDim(i))
        return false;

    return true;
  }

  friend std::ostream &operator<<(std::ostream &os, const CMultiArrayT &array) {
    array.print(os);

    return os;
  }

  void print(std::ostream &os) const {
    std::string sep   = "";
    bool        first = true;

    DataIterator i(*data_, dims_, mask_, dims1_);

    for (bool b = i.begin(); b; b = i.next()) {
      if (! first) {
        if (i.isStartPos()) {
          os << std::endl;

          sep = "";
        }
        else
          sep = " ";
      }

      os << sep << data_->getLinearValue(i.pos());

      first = false;
    }
  }

 private:
  CMultiArrayT(const CRefPtr<Data> &data) {
    data_ = data;

    init();
  }

  void init() {
    dims_ = getDims();

    mask_ = new bool [getNumData()];

    uint num_dims = getNumDims();

    if (num_dims <= 3)
      dims1_ = dims1_buffer_;
    else
      dims1_ = new uint [num_dims];

    memset(dims1_, 0, num_dims*sizeof(uint));

    setMask();
  }

  void setMask() {
    resetMask();

    uint num_dims = getNumDims();

    typename SliceList::const_iterator p1 = slices_.begin();
    typename SliceList::const_iterator p2 = slices_.end  ();

    for ( ; p1 != p2; ++p1) {
      const Slice &slice = *p1;

      DataIterator i(*data_, dims_, mask_, dims1_);

      for (bool b = i.begin(); b; b = i.next()) {
        for (uint j = 0; j < num_dims; ++j) {
          if (dims1_[j] < slice.start[j] ||
              dims1_[j] > (slice.start[j] + slice.len[j] - 1)) {
            mask_[i.pos()] = 1;
            break;
          }
        }
      }

      dims_ = slice.len;
    }
  }

  void resetMask() {
    dims_ = getDims();

    memset(mask_, 0, getNumData()*sizeof(bool));
  }

  bool setLinearValueI(uint ind, const T &value) {
    uint pos;

    if (! indToPos(ind, &pos))
      return false;

    data_->setLinearValue(pos, value);

    return true;
  }

  bool setValueI(const Dims &dims, const T &value) {
    uint pos;

    if (! dimsToPos(dims, &pos))
      return false;

    data_->setLinearValue(pos, value);

    return true;
  }

  bool getLinearValueI(uint ind, T &value) const {
    uint pos;

    if (! indToPos(ind, &pos))
      return false;

    value = data_->getLinearValue(pos);

    return true;
  }

  bool getValueI(const Dims &dims, T &value) const {
    uint pos;

    if (! dimsToPos(dims, &pos))
      return false;

    value = data_->getLinearValue(pos);

    return true;
  }

  bool indToPos(uint ind, uint *pos) const {
    if (slices_.empty()) {
      *pos = ind;

      return true;
    }

    DataIterator i(*data_, dims_, mask_, dims1_);

    bool b = i.begin();

    for ( ; b && ! i.isLinearPos(ind); b = i.next())
      ;

    if (b)
      *pos = i.pos();

    return b;
  }

  bool dimsToPos(const Dims &dims, uint *pos) const {
    DataIterator i(*data_, dims_, mask_, dims1_);

    bool b = i.begin();

    for ( ; b && ! i.isPos(dims); b = i.next())
      ;

    if (b)
      *pos = i.pos();

    return b;
  }
};

#endif
