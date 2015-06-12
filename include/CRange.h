#ifndef CRANGE_H
#define CRANGE_H

#include <cassert>

/*

https://docs.oracle.com/javase/8/docs/api/java/util/stream/IntStream.html

IntStream.of(1, 2, 3);  
// > 1, 2, 3

IntStream.range(1, 3);  
// > 1, 2
IntStream.rangeClosed(1, 3);  
// > 1, 2, 3

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
   public:
    Iterator(const T &start, const T &end, const T &step) :
     start_(start), end_(end), step_(step), pos_(start), isEnd_(false) {
    }

    Iterator() :
     start_(0), end_(0), step_(0), pos_(0), isEnd_(true) {
    }

    Iterator operator++() {
      assert(! isEnd_);

      pos_   += step_;
      isEnd_  = (pos_ >= end_);

      return *this;
    }

    Iterator operator++(int) {
      assert(! isEnd_);

      Iterator i = *this;

      pos_   += step_;
      isEnd_  = (pos_ >= end_);

      return i;
    }

    T operator*() {
      assert(! isEnd_);

      return pos_;
    }

    friend bool operator==(const Iterator &i1, const Iterator &i2) {
      if (i1.isEnd_ && i2.isEnd_) return true;
      if (i1.isEnd_ || i2.isEnd_) return false;

      return (i1.start_ == i2.start_) && (i1.end_ == i2.end_) &&
              (i1.step_ == i2.step_ ) && (i1.pos_ == i2.pos_);
    }

    friend bool operator!=(const Iterator &i1, const Iterator &i2) {
      return ! (i1 == i2);
    }

   private:
    T    start_, end_, step_, pos_;
    bool isEnd_;
  };

  typedef Iterator       iterator;
  typedef const Iterator const_iterator;

 public:
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
