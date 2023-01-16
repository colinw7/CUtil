#ifndef CEnv_H
#define CEnv_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <climits>
#include <sys/types.h>

#define CEnvInst CEnv::getInstance()

class CEnv {
 public:
  using NameList  = std::vector<std::string>;
  using ValueList = std::vector<std::string>;

  using NameValue = std::pair<std::string, std::string>;

 private:
  struct NameValues {
    NameList  names;
    ValueList values;
  };

  using NameValuesP = std::shared_ptr<NameValues>;

 public:
  class const_iterator {
   public:
    using value_type = NameValue;

   public:
    // end iterator
    const_iterator() {
      nameValues_ = CEnvInst.getSnapShot();

      pos_ = static_cast<uint>(nameValues_->names.size());
    }

    // begin iterator
    explicit const_iterator(int) {
      nameValues_ = CEnvInst.getSnapShot();
    }

   ~const_iterator() {
      CEnvInst.releaseSnapShot();
    }

    const_iterator &operator++() {
      ++pos_;

      return *this;
    }

    bool operator==(const const_iterator &i) {
      return (pos_ == i.pos_);
    }

    bool operator!=(const const_iterator &i) {
      return ! (*this == i);
    }

    value_type operator*() const {
      return value_type(nameValues_->names[pos_], nameValues_->values[pos_]);
    }

   private:
    NameValuesP nameValues_;
    uint        pos_ { 0 };
  };

 public:
  static CEnv &getInstance();

 ~CEnv();

  bool exists(const std::string &name) const;

  std::string get(const std::string &name) const;
  bool        get(const std::string &name, std::string &value) const;
  bool        get(const std::string &name, int &value) const;
  bool        get(const std::string &name, bool &value) const;

  bool set(const std::string &name, const std::string &value);
  bool set(const std::string &name, int value);

  bool unset(const std::string &name);

  bool unsetAll();

  const_iterator begin() { return const_iterator(0); }
  const_iterator end  () { return const_iterator(); }

  NameList  getNames () const;
  ValueList getValues() const;

  ValueList getValues(const std::string &name) const;

  void getNameValues(NameValues &nv) const;
  void getNameValues(NameList &names, ValueList &values) const;

  void getSortedNameValues(NameList &names, ValueList &values) const;

  std::string mostMatchPrefix (const std::string &prefix );
  std::string mostMatchPattern(const std::string &pattern);

  bool matchPrefix (const std::string &prefix , NameList &names);
  bool matchPattern(const std::string &pattern, NameList &names);

  void getPathList(const std::string &name, ValueList &paths);

  NameValuesP getSnapShot() {
    if (nameValues_.use_count() < 2) {
      NameValues *nameValues = new NameValues;

      getNameValues(*nameValues);

      nameValues_ = NameValuesP(nameValues);
    }

    return nameValues_;
  }

  void releaseSnapShot() {
  }

 private:
  CEnv() { }

  // not implemented
  CEnv(const CEnv &env);
  CEnv &operator=(const CEnv &env);

 private:
  void loadNameValues(NameValues &nv) const;
  void loadNameValues(NameList &names, ValueList &values) const;

 private:
  using Allocated = std::vector<char *>;

  NameValuesP nameValues_;
  Allocated   allocated_;
};

#endif
