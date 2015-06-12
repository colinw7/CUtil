#ifndef CRANGE_H
#define CRANGE_H

#include <cassert>
#include <vector>

/*

https://docs.oracle.com/javase/8/docs/api/java/util/stream/IntStream.html

IntStream.iterate(0, i -> i + 2).limit(3);
// > 0, 2, 4


IntStream.generate(() -> ThreadLocalRandom.current().nextInt(10)).limit(3);
// > 4, 1, 7

IntStream.range(1, 5).map(i -> i * i);
// > 1, 4, 9, 16

Stream<Color> stream = IntStream.range(1, 5).mapToObj(i -> getColor(i));
Stream<Integer> stream = IntStream.range(1, 5).boxed();
DoubleStream stream = IntStream.range(1, 5).mapToDouble(i -> i);

LongStream stream = IntStream.range(1, 5).mapToLong(i -> i);

IntStream.range(1, 5).anyMatch(i -> i % 2 == 0);
// > true

IntStream.range(1, 5).allMatch(i -> i % 2 == 0);
// > false

IntStream.range(1, 5).noneMatch(i -> i % 2 == 0);
// > false

IntStream.range(1, 5)
    .filter(i -> i % 2 == 0)
    .allMatch(i -> i % 2 == 0);
// > true

IntStream.range(1, 5)
    .filter(i -> i % 2 == 0)
    .noneMatch(i -> i % 2 != 0);
// > true

IntStream.range(1, 5).max().getAsInt();
// > 4
IntStream.range(1, 5).min().getAsInt();
// > 1

IntStream.range(1, 5).reduce(1, (x, y) -> x * y)
// > 24

IntStream.range(1, 5).parallel().forEach(i -> heavyOperation());

*/

template<typename T>
class RangeT {
 public:
  class Iterator {
   private:
    enum class Type {
      LIST,
      RANGE,
      END
    };

   public:
    Iterator(std::initializer_list<T> list) :
     type_(Type::LIST), list_(list) {
    }

    Iterator(const T &start, const T &end, const T &step) :
     type_(Type::RANGE), start_(start), end_(end), step_(step), pos_(start) {
    }

    Iterator() :
     type_(Type::END), isEnd_(true) {
    }

    Iterator operator++() {
      assert(! isEnd_);

      next();

      return *this;
    }

    Iterator operator++(int) {
      assert(! isEnd_);

      Iterator i = *this;

      next();

      return i;
    }

    T operator*() {
      assert(! isEnd_);

      if (type_ == Type::RANGE)
        return pos_;
      else
        return list_[pos_];
    }

    friend bool operator==(const Iterator &i1, const Iterator &i2) {
      if (i1.isEnd_ && i2.isEnd_) return true;
      if (i1.isEnd_ || i2.isEnd_) return false;

      if (i1.type_ != i2.type_) return false;

      if (i1.type_ == Type::RANGE) {
        return (i1.start_ == i2.start_) && (i1.end_ == i2.end_) &&
               (i1.step_  == i2.step_ ) && (i1.pos_ == i2.pos_);
      }
      else {
        if (i1.pos_ != i2.pos_) return false;

        if (i1.list_.size() != i2.list_.size()) return false;

        for (unsigned int i = 0; i < i1.list_.size(); ++i)
          if (i1.list_[i] != i2.list_[i])
            return false;

        return true;
      }
    }

    friend bool operator!=(const Iterator &i1, const Iterator &i2) {
      return ! (i1 == i2);
    }

   private:
    void next() {
      if (type_ == Type::RANGE) {
        pos_   += step_;
        isEnd_  = (pos_ >= end_);
      }
      else {
        ++pos_;

        isEnd_ = (pos_ >= list_.size());
      }
    }

   private:
    Type           type_;
    T              start_ { 0 };
    T              end_   { 0 };
    T              step_  { 1 };
    T              pos_   { 0 };
    std::vector<T> list_;
    bool           isEnd_ { false };
  };

  typedef Iterator       iterator;
  typedef const Iterator const_iterator;

 public:
  //CRange.of(1, 2, 3);
  // > 1, 2, 3
  static RangeT of(std::initializer_list<T> l) {
    return RangeT(l);
  }

  // IntStream.range(1, 3);
  // > 1, 2
  static RangeT range(T start, T end) {
    return RangeT(start, end, 1);
  }

  // IntStream.rangeClosed(1, 3);
  // > 1, 2, 3
  static RangeT rangeClosed(T start, T end) {
    return RangeT(start, end + 1, 1);
  }

  //---

  RangeT(std::initializer_list<T> list) :
   start_(list), end_() {
  }

  RangeT(T start, T end, T step=T(1)) :
   start_(start, end, step), end_() {
  }

  iterator begin() { return start_; }
  iterator end  () { return end_  ; }

  const_iterator begin() const { return start_; }
  const_iterator end  () const { return end_  ; }

 private:
  Iterator start_;
  Iterator end_;
};

typedef RangeT<int> IRange;

#endif
