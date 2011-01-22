#include "string_utils.h"

namespace gdata {
namespace util {

string StringUtils::to_lowercase(const string& str) {
  string lower_cased;
  for (string::const_iterator i = str.begin(); i != str.end(); ++i) {
    lower_cased += tolower(*i);
  }
  return lower_cased;
}

string StringUtils::find_and_replace(string source,
                                     const string& find,
                                     const string& replace) {
  size_t i;
  for ( ; (i = source.find(find)) != string::npos;) {
    source.replace(i, find.length(), replace);
  }
  return source;
}

}}  // namespace gdata::util
