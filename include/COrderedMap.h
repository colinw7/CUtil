#ifndef COrderedMap_H
#define COrderedMap_H

#include <map>
#include <cassert>

template<typename KEY, typename VALUE>
class COrderedMap {
 private:
  using KeyIndMap   = std::map<KEY,int>;
  using IndKeyMap   = std::map<int,KEY>;
  using IndValueMap = std::map<int,VALUE>;
  using KeyValue    = std::pair<KEY,VALUE>;

 public:
  class iterator {
   public:
    typedef iterator                  self_type;
    typedef VALUE                     value_type;
    typedef KeyValue&                 reference;
    typedef KeyValue*                 pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int                       difference_type;

    iterator(COrderedMap *map, typename IndKeyMap::iterator p) :
     map_(map), p_(p) {
    }

    self_type operator++() { auto i = *this; p_++; return i; }
    self_type operator++(int) { p_++; return *this; }

    reference operator*() { updateKeyValue(); return keyValue_; }

    pointer operator->() { updateKeyValue(); return &keyValue_; }

    bool operator==(const self_type &rhs) { return p_ == rhs.p_; }
    bool operator!=(const self_type &rhs) { return p_ != rhs.p_; }

    self_type &operator=(const VALUE &value) {
      map_->setIndValue(p_->first, value);
      return *this;
    }

   private:
    void updateKeyValue() const {
      keyValue_ = KeyValue(p_->second, map_->indValue(p_->first));
    }

   private:
    COrderedMap*                 map_;
    typename IndKeyMap::iterator p_;
    mutable KeyValue             keyValue_;
  };

  class const_iterator {
   public:
    typedef const_iterator            self_type;
    typedef VALUE                     value_type;
    typedef KeyValue const &          reference;
    typedef KeyValue const *          pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int                       difference_type;

    const_iterator(COrderedMap const *map, typename IndKeyMap::const_iterator p) :
     map_(map), p_(p) {
    }

    self_type operator++() { auto i = *this; p_++; return i; }
    self_type operator++(int) { p_++; return *this; }

    reference operator*() { updateKeyValue(); return keyValue_; }

    pointer operator->() { updateKeyValue(); return &keyValue_; }

    bool operator==(const self_type &rhs) { return p_ == rhs.p_; }
    bool operator!=(const self_type &rhs) { return p_ != rhs.p_; }

   private:
    void updateKeyValue() const {
      keyValue_ = KeyValue(p_->second, map_->indValue(p_->first));
    }

   private:
    COrderedMap const *                map_;
    typename IndKeyMap::const_iterator p_;
    mutable KeyValue                   keyValue_;
  };

 public:
  COrderedMap() { }

  std::size_t size() const { return indKeyMap_.size(); }

  void insert(const KEY &key, const VALUE &value) {
    auto p = keyIndMap_.find(key);

    if (p == keyIndMap_.end()) {
      int ind = keyIndMap_.size();

      p = keyIndMap_.insert(p, typename KeyIndMap::value_type(key, ind));

      indKeyMap_[ind] = key;
    }

    indValueMap_[(*p).second] = value;
  }

  iterator operator[](const KEY &key) {
    auto p = keyIndMap_.find(key);

    if (p == keyIndMap_.end()) {
      int ind = keyIndMap_.size();

      p = keyIndMap_.insert(p, typename KeyIndMap::value_type(key, ind));

      indKeyMap_[ind] = key;
    }

    return find(key);
  }

  const_iterator find(const KEY &key) const {
    auto p = keyIndMap_.find(key);
    if (p == keyIndMap_.end()) return end();

    return const_iterator(this, indKeyMap_.find((*p).second));
  }

  iterator find(const KEY &key) {
    auto p = keyIndMap_.find(key);
    if (p == keyIndMap_.end()) return end();

    return iterator(this, indKeyMap_.find((*p).second));
  }

  iterator begin() { return iterator(this, indKeyMap_.begin()); }
  iterator end  () { return iterator(this, indKeyMap_.end  ()); }

  const_iterator begin() const { return const_iterator(this, indKeyMap_.begin()); }
  const_iterator end  () const { return const_iterator(this, indKeyMap_.end  ()); }

 private:
  const KEY &indKey(int ind) const {
    auto p = indKeyMap_.find(ind);
    assert(p != indKeyMap_.end());

    return (*p).second;
  }

  const VALUE &indValue(int ind) const {
    auto p = indValueMap_.find(ind);
    assert(p != indValueMap_.end());

    return (*p).second;
  }

  void setIndValue(int ind, const VALUE &value) {
    indValueMap_[ind] = value;
  }

 private:
  friend class iterator;

  KeyIndMap   keyIndMap_;
  IndKeyMap   indKeyMap_;
  IndValueMap indValueMap_;
};

#endif
