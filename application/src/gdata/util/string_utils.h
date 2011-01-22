// Copyright 2008 Google Inc. All Rights Reserved.
// Author: e.bidelman@google.com (Eric Bidelman)

// Handy string utilities.

#ifndef GDATA_UTIL_STRING_UTIL_H_
#define GDATA_UTIL_STRING_UTIL_H_

#include <string>

namespace gdata {
namespace util {

using std::string;

class StringUtils {
 public:
  StringUtils();
  ~StringUtils() {}

 static string to_lowercase(const string& str);
 static string find_and_replace(string source,
                                const string& find,
                                const string& replace);
};

}}  // namespace gdata::util

#endif  // GDATA_UTIL_STRING_UTIL_H_
