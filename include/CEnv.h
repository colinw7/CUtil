#ifndef CEnv_H
#define CEnv_H

#include <CRefPtr.h>

#include <vector>
#include <climits>
#include <sys/types.h>

#define CEnvInst CEnv::getInstance()

class CEnv {
 public:
  typedef std::vector<std::string> NameList;
  typedef std::vector<std::string> ValueList;

  typedef std::pair<std::string,std::string> NameValue;

 private:
  struct NameValues {
    NameList  names;
    ValueList values;

    NameValues() :
     names(), values() {
    }
  };

 public:
  class const_iterator {
   public:
    typedef NameValue value_type;

   private:
    CRefPtr<NameValues> nameValues_;
    uint                pos_;

   public:
    const_iterator() :
     nameValues_(), pos_(UINT_MAX) {
      nameValues_ = CEnvInst.getSnapShot();

      pos_ = nameValues_->names.size();
    }

    explicit const_iterator(int) :
     nameValues_(), pos_(0) {
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
  };

 public:
  static CEnv &getInstance();

 ~CEnv();

  bool exists(const std::string &name) const;

  std::string get(const std::string &name) const;
  bool        get(const std::string &name, std::string &value) const;
  bool        get(const std::string &name, int &value) const;

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

  CRefPtr<NameValues> getSnapShot() {
    if (nameValues_.getRef() < 2) {
      NameValues *nameValues = new NameValues;

      getNameValues(*nameValues);

      nameValues_ = nameValues;
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
  CRefPtr<NameValues> nameValues_;
  std::vector<char *> allocated_;
};

#endif
