#ifndef CUTIL_H
#define CUTIL_H

//#include <CAngleType.h>

#include <algorithm>
#include <string>
#include <optional>
#include <iostream>
#include <sstream>

class CUtil {
 public:
  static void setOStream(std::ostream &os) { os_ = &os; }

  //static std::string toString   (CAngleType angle_type);
  //static CAngleType  toAngleType(const std::string &str);

  // dummy proc for debugging stop
  static void breakpoint();

  // decode position of first but set in mask
  static void decodeMask(uint full_mask, uint *shift, uint *mask);
  static void decodeMask(ushort full_mask, ushort *shift, ushort *mask);

  template<typename Collection>
  static bool contains(Collection &&collection,
                       typename std::remove_reference<Collection>::type::value_type const &value) {
    return std::find(std::begin(collection), std::end(collection), value) != std::end(collection);
  }

  // print string
  static void printString(const std::string &str);

#if 0
  // print string separated with newline
  template<class T, class... Args>
  static void printSep(std::ostream &os, const std::string &sep, T arg, Args... args) {
    os << arg;

    if constexpr (sizeof...(Args) > 0) {
      os << sep;

      printSep(os, sep, args...);
    }
    else
      os << "\n";
  }
#endif

#if 0
  // print space separated with newline
  template<class T, class... Args>
  static void print(std::ostream &os, T arg, Args... args) {
    os << arg;

    if constexpr (sizeof...(Args) > 0) {
      os << " ";

      print(os, args...);
    }
    else
      os << "\n";
  }
#endif

  template<typename T>
  static std::optional<T> &updateMin(std::optional<T> &opt, const T &value) {
    if (opt) opt = std::min(opt.value(), value);
    else     opt = value;
    return opt;
  }

  template<typename T>
  static std::optional<T> &updateMax(std::optional<T> &opt, const T &value) {
    if (opt) opt = std::max(opt.value(), value);
    else     opt = value;
    return opt;
  }

  template<typename T>
  static std::optional<T> &updateMin(std::optional<T> &opt, const std::optional<T> &value) {
    if (value) {
      if (opt) opt = std::min(opt.value(), value.value());
      else     opt = value.value();
    }
    return opt;
  }

  template<typename T>
  static std::optional<T> &updateMax(std::optional<T> &opt, const std::optional<T> &value) {
    if (value) {
      if (opt) opt = std::max(opt.value(), value.value());
      else     opt = value.value();
    }
    return opt;
  }

  template<typename T>
  static void print(std::ostream &os, const std::optional<T> &value,
                    const std::string &unsetStr="<unset>") {
    if (value)
      os << value.value();
    else
      os << unsetStr;
  }

  template<typename T>
  static std::string toString(const T &t) {
    std::ostringstream ss;
    ss << t;
    return ss.str();
  }

 private:
  static std::ostream *os_;
};

#endif
