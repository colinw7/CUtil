#ifndef CFuncChain_H
#define CFuncChain_H

#include <vector>

template<typename DATA, typename FUNCTION>
class CFuncChainT {
 public:
  CFuncChainT() { }

  const DATA &data() const { return data_; }
  DATA &data() { return data_; }

  void setData(const DATA &v) { data_ = v; }

  friend CFuncChainT &operator<<(CFuncChainT &chain, const FUNCTION &fn) {
    chain.chain_.push_back(fn);

    return chain;
  }

  void call() {
    for (auto &fn : chain_)
      fn(data_);
  }

  template<typename T>
  void call(const T &t) {
    for (auto &fn : chain_)
      fn(t, data_);
  }

  template<typename T>
  void call(const std::vector<T> &values) {
    for (const auto &v : values) {
      for (auto &fn : chain_) {
        fn(v, data_);
      }
    }
  }

  template<typename T>
  void orderedCall(const std::vector<T> &values) {
    for (auto &fn : chain_) {
      for (const auto &v : values) {
        fn(v, data_);
      }
    }
  }

 private:
  typedef std::vector<FUNCTION> FunctionChain;

  DATA          data_;
  FunctionChain chain_;
};

#endif
