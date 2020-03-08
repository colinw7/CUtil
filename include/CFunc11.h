#ifndef CFunc11_H
#define CFunc11_H

namespace CFunc11 {

template<typename T, typename ...Ts>
auto concat(T t, Ts ...ts) {
  if constexpr (sizeof...(ts) > 0) {
    return [=](auto ...parameters) {
      return t(concat(ts...)(parameters...));
    };
  }
  else {
    return t;
  }
}

}

#endif
