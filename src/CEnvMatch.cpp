#include <CEnvMatch.h>

std::string
CEnv::
mostMatchPrefix(const std::string &prefix)
{
  std::vector<std::string> names;

  if (! matchPrefix(prefix, names)) {
    return prefix;
  }

  return CStrUtil::mostMatch(names);
}

std::string
CEnv::
mostMatchPattern(const std::string &pattern)
{
  std::vector<std::string> names;

  if (! matchPattern(pattern, names)) {
    return pattern;
  }

  return CStrUtil::mostMatch(names);
}

bool
CEnv::
matchPrefix(const std::string &prefix, std::vector<std::string> &names)
{
  std::string pattern = prefix + "*";

  if (! matchPattern(pattern, names))
    return false;

  return true;
}

bool
CEnv::
matchPattern(const std::string &pattern, std::vector<std::string> &names)
{
  CGlob glob(pattern);

  glob.setAllowOr(false);
  glob.setAllowNonPrintable(true);

  std::vector<std::string> env_names;
  std::vector<std::string> env_values;

  CEnvInst.getNameValues(env_names, env_values);

  int num_env_names = env_names.size();

  for (int i = 0; i < num_env_names; i++) {
    if (glob.compare(env_names[i]))
      names.push_back(env_names[i]);
  }

  return true;
}
