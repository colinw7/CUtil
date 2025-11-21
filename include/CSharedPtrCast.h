#ifndef CSharedPtr_H
#define CSharedPtr_H

template<typename T, typename T1>
T *CSharedPtrCast(const std::shared_ptr<T1> &p) {
  return dynamic_cast<T *>(p.get());
}

#endif
