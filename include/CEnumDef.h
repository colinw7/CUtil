#ifndef CENUM_DEF_H
#define CENUM_DEF_H

#include <map>

template<typename T>
class CEnum {
 public:
  typedef std::map<T,std::string> EnumToStringMap;
  typedef std::map<std::string,T> StringToEnumMap;

 public:
  CEnum() { init(); }

  void init();

  CEnum *add(T n, const std::string &name) {
    enumToString_[n] = name;

    stringToEnum_[name] = n;

    return this;
  }

  bool toString(T t, std::string &s) {
    typename EnumToStringMap::const_iterator p = enumToString_.find(t);

    if (p == enumToString_.end())
      return false;

    s = (*p).second;

    return true;
  }

  bool fromString(const std::string &s, T &t) {
    typename StringToEnumMap::const_iterator p = stringToEnum_.find(s);

    if (p == stringToEnum_.end())
      return false;

    t = (*p).second;

    return true;
  }

 private:
  EnumToStringMap enumToString_;
  StringToEnumMap stringToEnum_;
};

template<typename T>
bool
CEnumToString(T t, std::string &s)
{
  extern CEnum<T> enum_map;

  return enum_map.toString(t, s);
}

template<typename T>
bool
CStringToEnum(const std::string &s, T &t)
{
  extern CEnum<T> enum_map;

  return enum_map.fromString(s, t);
}

#define CENUM_START(E) enum E {
#define CENUM_END(E) };
#define CENUM_ITEM(E,S,N) E,
#define CENUM_VALUE(E,S,N,V) E = V,

#endif
