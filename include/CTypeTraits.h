#ifndef CTYPE_TRAITS_H
#define CTYPE_TRAITS_H

// ArgT      : actual type
// BareT     : fully stripped type
// ConstT    : constant type
// RefT      : reference type
// RefBareT  : reference to fully stripped type
// RefConstT : constant reference to type

template<typename T>
class CTypeTraits {
 public:
  typedef T         ArgT;
  typedef T         BareT;
  typedef T const   ConstT;
  typedef T &       RefT;
  typedef T &       RefBareT;
  typedef T const & RefConstT;
};

template<typename T>
class CTypeTraits <T const> {
 public:
  typedef T const   ArgT;
  typedef T         BareT;
  typedef T const   ConstT;
  typedef T const & RefT;
  typedef T &       RefBareT;
  typedef T const & RefConstT;
};

template<typename T>
class CTypeTraits <T &> {
 public:
  typedef T &                              ArgT;
  typedef typename CTypeTraits<T>::BareT   BareT;
  typedef T const                          ConstT;
  typedef T &                              RefT;
  typedef typename CTypeTraits<T>::BareT & RefBareT;
  typedef T const &                        RefConstT;
};

template<typename T>
class CTypeTraits <T *> {
 public:
  typedef T *                              ArgT;
  typedef typename CTypeTraits<T>::BareT   BareT;
  typedef T const *                        ConstT;
  typedef T *                              RefT;
  typedef typename CTypeTraits<T>::BareT * RefBareT;
  typedef T const *                        RefConstT;
};

template<>
class CTypeTraits <void> {
 public:
  typedef void       ArgT;
  typedef void       BareT;
  typedef void const ConstT;
  typedef void       RefT;
  typedef void       RefBareT;
  typedef void       RefConstT;
};

#endif
