#ifndef RANGE_ITR_H
#define RANGE_ITR_H

#include <cassert>
#include <vector>
#include <functional>
#include <iostream>

/*

// https://docs.oracle.com/javase/8/docs/api/java/util/stream/IntStream.html

// Stream<Color> stream = IntStream.range(1, 5).mapToObj(i -> getColor(i));
// Stream<Integer> stream = IntStream.range(1, 5).boxed();
// DoubleStream stream = IntStream.range(1, 5).mapToDouble(i -> i);

// LongStream stream = IntStream.range(1, 5).mapToLong(i -> i);

// IntStream.range(1, 5).anyMatch(i -> i % 2 == 0);
// > true

// IntStream.range(1, 5).allMatch(i -> i % 2 == 0);
// > false

// IntStream.range(1, 5).noneMatch(i -> i % 2 == 0);
// > false

// IntStream.range(1, 5).filter(i -> i % 2 == 0).allMatch(i -> i % 2 == 0);
// > true

// IntStream.range(1, 5).filter(i -> i % 2 == 0).noneMatch(i -> i % 2 != 0);
// > true

// IntStream.range(1, 5).max().getAsInt();
// > 4
// IntStream.range(1, 5).min().getAsInt();
// > 1

// IntStream.range(1, 5).reduce(1, (x, y) -> x * y)
// > 24

// IntStream.range(1, 5).parallel().forEach(i -> heavyOperation());

*/

template<typename T, typename RES=T>
class RangeItrT {
 public:
  typedef std::function<T (T)>    Map;
  typedef std::function<bool (T)> Filter;
  typedef std::function<T ()>     Generate;

  //---

  class Data {
   public:
    Data() { }

    virtual ~Data() { }

    virtual void reset() = 0;

    virtual bool next() = 0;

    virtual T value() const = 0;

    virtual Data *dup() const = 0;
  };

  class RangeData : public Data {
   public:
    RangeData(T start, T end, T step) :
     start_(start), end_(end), step_(step) {
      reset();
    }

    RangeData(T start, T end) :
     start_(start), end_(end) {
      step_ = (start_ < end_ ? 1 : -1);

      reset();
    }

    RangeData(T start) :
     start_(start), step_(1), hasEnd_(false) {
      reset();
    }

    void reset() override {
      value_ = start_;
    };

    bool next() override {
      value_ += step_;

      return (! hasEnd_ || value_ < end_);
    }

    T value() const override {
      return value_;
    }

    void setStep(T step) {
      step_ = step;
    }

    RangeData *dup() const override {
      return new RangeData(start_, end_, step_, hasEnd_);
    }

    friend bool operator==(const RangeData &r1, const RangeData &r2) {
      return (r1.start_ == r2.start_) && (r1.end_   == r2.end_) &&
             (r1.step_  == r2.step_ ) && (r1.value_ == r2.value_);
    }

   private:
    RangeData(T start, T end, T step, bool hasEnd) :
     start_(start), end_(end), step_(step), hasEnd_(hasEnd) {
      reset();
    }

   private:
    T    start_  { 0 };
    T    end_    { 0 };
    T    step_   { 1 };
    bool hasEnd_ { true };
    T    value_  { 0 };
  };

  //---

  class ListData : public Data {
   public:
    ListData(std::initializer_list<T> list) :
     list_(list) {
    }

    ListData(const std::vector<T> &list) :
     list_(list) {
    }

    void reset() override {
      pos_ = 0;
    }

    bool next() override {
      ++pos_;

      return (pos_ < int(list_.size()));
    }

    T value() const override {
      return list_[pos_];
    }

    ListData *dup() const override {
      return new ListData(list_);
    }

    friend bool operator==(const ListData &l1, const ListData &l2) {
      if (l1.list_.pos_ != l2.list_.pos_) return false;

      if (l1.list_.size() != l2.list_.size()) return false;

      for (unsigned int i = 0; i < l1.size(); ++i)
        if (l1.list_[i] != l2.list_[i])
          return false;

      return true;
    }

   private:
    std::vector<T> list_;
    int            pos_ { 0 };
  };

  //---

  class GenData : public Data {
   public:
    GenData(Generate gen) :
     gen_(gen) {
    }

    void reset() override { }

    bool next() override { return true; }

    T value() const override {
      return gen_();
    }

    GenData *dup() const override {
      return new GenData(gen_);
    }

   private:
    Generate gen_;
  };

  //---

  class MapData : public Data {
   public:
    MapData(Data *data, Map map) :
     data_(data->dup()), map_(map) {
      assert(data_);
    }

   ~MapData() {
     delete data_;
    }

    void reset() override { data_->reset(); }

    bool next() override { return data_->next(); }

    T value() const override {
      return map_(data_->value());
    }

    MapData *dup() const override {
      return new MapData(data_, map_);
    }

   private:
    Data* data_ { 0 };
    Map   map_;
  };

  //---

  class FilterData : public Data {
   public:
    FilterData(Data *data, Filter filter) :
     data_(data->dup()), filter_(filter) {
      assert(data_);
    }

   ~FilterData() {
     delete data_;
    }

    void reset() override { data_->reset(); }

    bool next() override {
      bool isEnd = data_->next();

      while (! isEnd && ! filter_(data_->value()))
        isEnd = data_->next();

      return isEnd;
    }

    T value() const override {
      return data_->value();
    }

    FilterData *dup() const override {
      return new FilterData(data_, filter_);
    }

   private:
    Data*  data_ { 0 };
    Filter filter_;
  };

  //---

  class Iterator {
   private:
    enum class Type {
      LIST,
      LIST_PAIR,
      RANGE,
      GENERATE,
      MAP,
      FILTER,
      END
    };

   private:
    struct RawValue {
      RawValue(Iterator *i) : i_(i) { }

      T value() const { return i_->value(); }

      Iterator *i_;
    };

    struct PairValue {
      PairValue(Iterator *i) : i_(i) { }

      std::pair<int,T> value() const { return i_->pairValue(); }

      Iterator *i_;
    };

   public:
    Iterator(const T &start, const T &end, const T &step) :
     type_(Type::RANGE), data_(new RangeData(start, end, step)) {
      reset();
    }
    Iterator(const T &start, const T &end) :
     type_(Type::RANGE), data_(new RangeData(start, end)) {
      reset();
    }
    Iterator(const T &start) :
     type_(Type::RANGE), data_(new RangeData(start)) {
      reset();
    }

    Iterator(std::initializer_list<T> list) :
     type_(Type::LIST), data_(new ListData(list)) {
      reset();
    }

    Iterator(const std::vector<T> &list) :
     type_(Type::LIST), data_(new ListData(list)) {
      reset();
    }

    Iterator(Generate g) :
     type_(Type::GENERATE), data_(new GenData(g)) {
      reset();
    }

    Iterator(const Iterator &i, Map map) :
     type_(Type::MAP), data_(new MapData(i.data_, map)) {
      reset();
    }

    Iterator(const Iterator &i, Filter filter) :
     type_(Type::FILTER), data_(new FilterData(i.data_, filter)) {
      reset();
    }

    Iterator() :
     type_(Type::END), isEnd_(true) {
    }

    Iterator(const Iterator &it) :
     type_(it.type_), data_(it.data_ ? it.data_->dup() : 0), limit_(it.limit_),
     isEnd_(type_ == Type::END) {
      if (type_ != Type::END)
        reset();
    }

   ~Iterator() {
      delete data_;
    }

    Iterator operator++() {
      assert(! isEnd_);

      next();

      ++count_;

      if (limit_ > 0 && count_ >= limit_)
        isEnd_ = true;

      return *this;
    }

    Iterator operator++(int) {
      assert(! isEnd_);

      Iterator i = *this;

      next();

      ++count_;

      if (limit_ > 0 && count_ > limit_)
        isEnd_ = true;

      return i;
    }

    RES operator*() {
      typedef typename std::conditional<std::is_same<T,RES>::value,
        RawValue, PairValue>::type ValueType;

      return ValueType(this).value();
    }

    friend bool operator==(const Iterator &i1, const Iterator &i2) {
      if (i1.isEnd_ && i2.isEnd_) return true;
      if (i1.isEnd_ || i2.isEnd_) return false;

      return false;
    }

    friend bool operator!=(const Iterator &i1, const Iterator &i2) {
      return ! (i1 == i2);
    }

    Iterator limit(int n) const {
      Iterator it(*this);

      it.limit_ = n;

      return it;
    }

    Iterator step(T step) const {
      Iterator it(*this);

      assert(type_ == Type::RANGE);

      static_cast<RangeData *>(it.data_)->setStep(step);

      return it;
    }

   private:
    void reset() {
      data_->reset();
    }

    void next() {
      if (! data_->next())
        isEnd_ = true;
    }

    T value() const {
      return data_->value();
    }

    std::pair<int,T> pairValue() const {
      return std::pair<int,T>(count_, data_->value());
    }

   private:
    Iterator &operator=(const Iterator &it);

   private:
    Type  type_;
    Data* data_   { 0 };
    int   count_  { 0 };
    int   limit_  { -1 };
    bool  isEnd_  { false };
    bool  isPair_ { false };
  };

  //------

  typedef Iterator       iterator;
  typedef const Iterator const_iterator;

 public:
  // RangeItrT<int>.of(1, 2, 3)
  // > 1, 2, 3
  static RangeItrT of(std::initializer_list<T> l) {
    return RangeItrT(l);
  }

  static RangeItrT of(const std::vector<T> &l) {
    return RangeItrT(l);
  }

  static RangeItrT<T,std::pair<int,T>> ofPair(const std::vector<T> &l) {
    return RangeItrT<T,std::pair<int,T>>::of(l);
  }

  // RangeItrT<int>.range(0, 21, 2)
  // > 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20
  static RangeItrT range(T start, T end, T step) {
    return RangeItrT(start, end, step);
  }
  // RangeItrT<int>.range(1, 3)
  // > 1, 2
  static RangeItrT range(T start, T end) {
    return RangeItrT(start, end);
  }
  static RangeItrT range(T start) {
    return RangeItrT(start);
  }

  // RangeItrT<int>.rangeClosed(1, 3)
  // > 1, 2, 3
  static RangeItrT rangeClosed(T start, T end, T step) {
    return RangeItrT(start, start < end ? end + step : end - step, step);
  }
  static RangeItrT rangeClosed(T start, T end) {
    return RangeItrT(start, start < end ? end + 1 : end - 1);
  }

  // RangeItrT<int>.generate(rand()).limit(3)
  // > 4, 1, 7
  static RangeItrT generate(Generate g) {
    return RangeItrT(g);
  }

  // IntStream.iterate(0, i -> i + 2).limit(3)
  // > 0, 2, 4
  static RangeItrT iterate(T start, Map map) {
    return RangeItrT(start).map(map);
  }

  //---

  RangeItrT(std::initializer_list<T> list) :
   start_(list) {
  }

  RangeItrT(T start, T end, T step) :
   start_(start, end, step) {
  }

  RangeItrT(T start, T end) :
   start_(start, end) {
  }

  RangeItrT(T start) :
   start_(start) {
  }

  iterator begin() { return start_; }
  iterator end  () { return end_  ; }

  const_iterator begin() const { return start_; }
  const_iterator end  () const { return end_  ; }

  //---

  // IntStream.range(1, 5).map(i -> i * i);
  // > 1, 4, 9, 16
  RangeItrT map(Map map) const {
    return RangeItrT(start_, map);
  }

  //---

  RangeItrT limit(int n) const {
    return RangeItrT(start_.limit(n));
  }

  //---

  RangeItrT step(T step) const {
    return RangeItrT(start_.step(step));
  }

  //---

  // RangeItrT<int>::rangeClosed(1, 12).filter([](int i) -> int { return (i % 3) == 0; }));
  // > 3, 6, 9, 12
  RangeItrT filter(Filter f) const {
    return RangeItrT(start_, f);
  }

  //---

  void print(std::ostream &os=std::cout) const {
    bool first = true;

    for (auto v : *this) {
      if (! first) os << ", ";

      os << v;

      first = false;
    }

    os << std::endl;
  }

  void printPair(std::ostream &os=std::cout) const {
    bool first = true;

    for (auto v : *this) {
      if (! first) os << ", ";

      os << v.first << ":" << v.second;

      first = false;
    }

    os << std::endl;
  }

  friend std::ostream &operator<<(std::ostream &os, const RangeItrT &r) {
    r.print(os);

    return os;
  }

 private:
  RangeItrT(const Iterator &start) :
   start_(start), end_() {
  }

  RangeItrT(const Iterator &start, Map f) :
   start_(start, f), end_() {
  }

  RangeItrT(const Iterator &start, Filter f) :
   start_(start, f), end_() {
  }

  RangeItrT(Generate f) :
   start_(f), end_() {
  }

 private:
  Iterator start_;
  Iterator end_;
};

typedef RangeItrT<int>          IRangeItr;
typedef RangeItrT<unsigned int> UIRangeItr;
typedef RangeItrT<double>       RRangeItr;
typedef RangeItrT<std::string>  SRangeItr;

typedef RangeItrT<double,std::pair<int,double>> RRangePair;

#endif
