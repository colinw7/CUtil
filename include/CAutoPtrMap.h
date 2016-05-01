#ifndef CAutoPtrMap_H
#define CAutoPtrMap_H

#include <map>

template<class KEY, class VALUE>
class CAutoPtrMap {
 private:
  typedef std::map<KEY,VALUE *> Map;

  Map map_;

 public:
  typedef typename Map::iterator       iterator;
  typedef typename Map::const_iterator const_iterator;
  typedef typename Map::value_type     value_type;

  CAutoPtrMap() { }

 ~CAutoPtrMap() {
    clear();
  }

  bool isValue(const KEY &key) const {
    return (map_.find(key) != map_.end());
  }

  void setValue(const KEY &key, VALUE *value) {
    if (value == NULL) {
      unsetValue(key);

      return;
    }

    typename Map::iterator p = map_.find(key);

    if (p != map_.end()) {
      delete (*p).second;

      map_[key] = value;
    }
    else
      map_[key] = value;
  }

  void unsetValue(const KEY &key) {
    typename Map::iterator p = map_.find(key);

    if (p != map_.end()) {
      delete (*p).second;

      map_.erase(p);
    }
  }

  VALUE *getValue(const KEY &key) const {
    typename Map::const_iterator p = map_.find(key);

    if (p == map_.end()) return NULL;

    return (*p).second;
  }

  void clear() {
    for (const auto &p : map_)
      delete p.second;

    map_.clear();
  }

  iterator begin() {
    return map_.begin();
  }

  const_iterator begin() const {
    return map_.begin();
  }

  iterator end() {
    return map_.end();
  }

  const_iterator end() const {
    return map_.end();
  }
};

#endif
