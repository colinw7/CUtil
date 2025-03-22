#ifndef CEnumerate_H
#define CEnumerate_H

#include <tuple>
#include <cstddef>
#include <iterator>

template<typename T, typename TIter = decltype(std::begin(std::declval<T>())),
         typename = decltype(std::end(std::declval<T>()))>
constexpr auto CEnumerate(T &&iterable) {
  struct iterator {
    size_t i { 0 };
    TIter iter;
    bool operator!=(const iterator &other) const { return iter != other.iter; }
    void operator++() { ++i; ++iter; }
    auto operator*() const { return std::tie(i, *iter); }
  };

  struct iterable_wrapper {
    T iterable;
    auto begin() { return iterator{ 0, std::begin(iterable) }; }
    auto end  () { return iterator{ 0, std::end  (iterable) }; }
  };

  return iterable_wrapper{ std::forward<T>(iterable) };
}

#endif
