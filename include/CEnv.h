#ifndef CEnv_H
#define CEnv_H

#include <CRefPtr.h>

#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

#define CEnvInst CEnv::instance()

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

  class NameValueCmp {
   public:
    int operator()(const NameValue &a, const NameValue &b) {
      return (a.first < b.first);
    }
  };

 public:
  static CEnv &instance() {
    static CEnv instance;

    return instance;
  }

  bool exists(const std::string &name) const {
    char *env = getenv((char *) name.c_str());

    return (env != 0);
  }

  std::string get(const std::string &name) const {
    char *env = getenv((char *) name.c_str());
    if (! env) {
      std::cerr << "env: '" << name + "' does not exist" << std::endl;
      return "";
    }

    return env;
  }

  bool get(const std::string &name, std::string &value) {
    char *env = getenv((char *) name.c_str());
    if (! env) return false;

    value = env;

    return true;
  }

  bool set(const std::string &name, const std::string &value) {
#ifdef USE_SETENV
    int error = ::setenv(name.c_str(), value.c_str(), 1);
#else
    std::string env = name + "=" + value;

    char *envp = strdup((char *) env.c_str());

    allocated_.push_back(envp);

    int error = ::putenv(envp);
#endif

    if (error != 0)
      return false;

    return true;
  }

  bool unset(const std::string &name) {
    extern char **environ;

    int name_len = name.size();

    int i = 0;

    while (environ[i] != 0) {
      int environ_len = strlen(environ[i]);

      if (environ_len > name_len &&
          strncmp(environ[i], name.c_str(), name_len) == 0 &&
          environ[i][name_len] == '=')
        break;

      i++;
    }

    if (environ[i] == 0) {
      std::cerr << "env: '" << name + "' does not exist" << std::endl;
      return false;
    }

    int i1 = i;

    while (environ[i1] != 0)
      i1++;

    for (int j = i; j < i1; j++)
      environ[j] = environ[j + 1];

    return true;
  }

  void getNameValues(NameList &names, ValueList &values) const {
    loadNameValues(names, values);
  }

  void getNameValues(NameValues &nv) const {
    loadNameValues(nv);
  }

  void getSortedNameValues(NameList &names, ValueList &values) const {
    extern char **environ;

    std::vector<NameValue> name_values;

    for (int i = 0; environ[i] != 0; i++) {
      std::string env_name = std::string(environ[i]);

      std::string::size_type pos = env_name.find('=');

      std::string env_value;

      if (pos != std::string::npos) {
        env_value = env_name.substr(pos + 1);
        env_name  = env_name.substr(0, pos);
      }

      name_values.push_back(NameValue(env_name,env_value));
    }

    std::sort(name_values.begin(), name_values.end(), NameValueCmp());

    names .clear();
    values.clear();

    for (unsigned int i = 0; i < name_values.size(); i++) {
      names .push_back(name_values[i].first );
      values.push_back(name_values[i].second);
    }
  }

 private:
  CEnv() { }
 ~CEnv() { }

  // not implemented
  CEnv(const CEnv &env);
  CEnv &operator=(const CEnv &env);

 private:
  void loadNameValues(NameValues &nv) const {
    loadNameValues(nv.names, nv.values);
  }

  void loadNameValues(NameList &names, ValueList &values) const {
    extern char **environ;

    names .clear();
    values.clear();

    for (int i = 0; environ[i] != 0; i++) {
      std::string env_name = std::string(environ[i]);

      std::string::size_type pos = env_name.find('=');

      std::string env_value;

      if (pos != std::string::npos) {
        env_value = env_name.substr(pos + 1);
        env_name  = env_name.substr(0, pos);
      }

      names .push_back(env_name );
      values.push_back(env_value);
    }
  }

 private:
  CRefPtr<NameValues> nameValues_;

  std::vector<char *> allocated_;
};

#endif
