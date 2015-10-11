#ifndef CIVector_H
#define CIVector_H

#include <vector>
#include <cstddef>
#include <cassert>

template<typename T>
class CIVectorT {
 public:
  typedef std::pair<int,T> Pair;

  class Iterator {
   public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Pair                      value_type;

   private:
    struct IteratorState {
      const CIVectorT *iv;
      int              len, pos;
      bool             end;

      IteratorState() :
        iv(0), len(0), pos(0), end(true) {
      }

      IteratorState(const CIVectorT *iv1) :
        iv(iv1), len(iv1->size()), pos(0), end(pos >= len) {
      }

      void inc() {
        assert(pos < len);

        ++pos;

        end = (pos >= len);
      }

      value_type value() const {
        return Pair(pos, (*iv)[pos]);
      }
    };

   public:
    Iterator(const CIVectorT *iv) :
     state_(iv) {
    }

    Iterator() :
     state_() {
    }

    value_type operator->()       { return state_.value(); }
    value_type operator->() const { return state_.value(); }
    value_type operator* ()       { return state_.value(); }
    value_type operator* () const { return state_.value(); }

    Iterator &operator++() {
      state_.inc();

      return *this;
    }

    Iterator operator++(int) {
      Iterator t = *this;

      state_.inc();

      return t;
    }

    bool operator==(const Iterator &i) const {
      if (state_.end && i.state_.end) return true;

      if (! state_.end && ! i.state_.end)
        return (state_.pos == i.state_.pos);
      else
        return false;
    }

    bool operator!=(const Iterator &i) const {
      return ! operator==(i);
    }

   private:
    IteratorState state_;
  };

  //---

 public:
  typedef T                 value_type;
  typedef value_type &      reference;
  typedef value_type const &const_reference;

  typedef Iterator        iterator;
  typedef Iterator const &const_iterator;

 public:
  CIVectorT(const std::vector<T> &v) :
   v_(v) {
  }

  //------

 public:
  Iterator begin() const { return Iterator(this); }
  Iterator end  () const { return Iterator();}

  size_t size() const { return v_.size(); }

  const_reference &operator[](int i) const { return v_[i]; }
  reference       &operator[](int i)       { return v_[i]; }

 private:
  const std::vector<T> &v_;
};

template<typename T>
CIVectorT<T> CIVector(const std::vector<T> &v) {
  return CIVectorT<T>(v);
}

#endif
