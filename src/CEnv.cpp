#include <CEnv.h>
#include <CStrUtil.h>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using std::string;

extern char **environ;

class CEnvNameValueCmp {
 public:
  int operator()(const CEnv::NameValue &a, const CEnv::NameValue &b) {
    return (a.first < b.first);
  }
};

CEnv &
CEnv::
getInstance()
{
  static CEnv *instance = nullptr;

  if (! instance)
    instance = new CEnv();

  return *instance;
}

CEnv::
~CEnv()
{
  for (uint i = 0; i < allocated_.size(); i++)
    free(allocated_[i]);
}

bool
CEnv::
exists(const string &name) const
{
  char *env = getenv(const_cast<char *>(name.c_str()));

  return (env != nullptr);
}

string
CEnv::
get(const string &name) const
{
  char *env = getenv(const_cast<char *>(name.c_str()));

  if (! env) {
    std::cerr << "env: '" << name + "' does not exist" << std::endl;
    return "";
  }

  return env;
}

bool
CEnv::
get(const string &name, string &value) const
{
  char *env = getenv(const_cast<char *>(name.c_str()));
  if (! env) return false;

  value = env;

  return true;
}

bool
CEnv::
get(const string &name, int &value) const
{
  value = 0;

  string str;

  if (! get(name, str))
    return false;

  value = int(CStrUtil::toInteger(str));

  return true;
}

bool
CEnv::
get(const string &name, bool &value) const
{
  value = 0;

  string str;

  if (! get(name, str))
    return false;

  value = CStrUtil::toBool(str);

  return true;
}

bool
CEnv::
set(const string &name, const string &value)
{
#ifdef USE_SETENV
  int error = ::setenv(name.c_str(), value.c_str(), 1);
#else
  string env = name + "=" + value;

  char *envp = strdup(const_cast<char *>(env.c_str()));

  allocated_.push_back(envp);

  int error = ::putenv(envp);
#endif

  if (error != 0)
    return false;

  return true;
}

bool
CEnv::
set(const string &name, int value)
{
  return set(name, CStrUtil::toString(value));
}

bool
CEnv::
unset(const string &name)
{
  auto name_len = name.size();

  uint i = 0;

  while (environ[i] != nullptr) {
    auto environ_len = strlen(environ[i]);

    if (environ_len > name_len &&
        strncmp(environ[i], name.c_str(), name_len) == 0 &&
        environ[i][name_len] == '=')
      break;

    i++;
  }

  if (environ[i] == nullptr) {
    std::cerr << "env: '" << name + "' does not exist" << std::endl;
    return false;
  }

  uint i1 = i;

  while (environ[i1] != nullptr)
    i1++;

  for (uint j = i; j < i1; j++)
    environ[j] = environ[j + 1];

  return true;
}

bool
CEnv::
unsetAll()
{
  environ[0] = nullptr;

  return true;
}

CEnv::NameList
CEnv::
getNames() const
{
  NameValues nv;

  loadNameValues(nv);

  return nv.names;
}

CEnv::ValueList
CEnv::
getValues() const
{
  NameValues nv;

  loadNameValues(nv);

  return nv.values;
}

CEnv::ValueList
CEnv::
getValues(const string &name) const
{
  string path = get(name);

  CStrWords words = CStrUtil::toFields(path, ":");

  ValueList values;

  auto num_words = words.size();

  for (uint i = 0; i < num_words; i++)
    values.push_back(words[int(i)].getWord());

  return values;
}

void
CEnv::
getNameValues(NameList &names, ValueList &values) const
{
  loadNameValues(names, values);
}

void
CEnv::
getNameValues(NameValues &nv) const
{
  loadNameValues(nv);
}

void
CEnv::
getSortedNameValues(NameList &names, ValueList &values) const
{
  std::vector<NameValue> name_values;

  for (int i = 0; environ[i] != nullptr; i++) {
    string env_name = string(environ[i]);

    string::size_type pos = env_name.find('=');

    string env_value;

    if (pos != string::npos) {
      env_value = env_name.substr(pos + 1);
      env_name  = env_name.substr(0, pos);
    }

    name_values.push_back(NameValue(env_name,env_value));
  }

  sort(name_values.begin(), name_values.end(), CEnvNameValueCmp());

  names .clear();
  values.clear();

  for (unsigned int i = 0; i < name_values.size(); i++) {
    names .push_back(name_values[i].first );
    values.push_back(name_values[i].second);
  }
}

void
CEnv::
loadNameValues(NameValues &nv) const
{
  loadNameValues(nv.names, nv.values);
}

void
CEnv::
loadNameValues(NameList &names, ValueList &values) const
{
  names .clear();
  values.clear();

  for (int i = 0; environ[i] != nullptr; i++) {
    string env_name = string(environ[i]);

    string::size_type pos = env_name.find('=');

    string env_value;

    if (pos != string::npos) {
      env_value = env_name.substr(pos + 1);
      env_name  = env_name.substr(0, pos);
    }

    names .push_back(env_name );
    values.push_back(env_value);
  }
}

void
CEnv::
getPathList(const string &name, ValueList &paths)
{
  string value = CEnv::get(name);

  CStrUtil::addFields(value, paths, ":");
}
