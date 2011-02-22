/**
 * Copyright 2008 Google Inc. All Rights Reserved.
 * Author: e.bidelman@google.com (Eric Bidelman)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License
 *
 * Dependencies:
 * libcurl: C++ wrapper for curl (http://curl.haxx.se/libcurl/cplusplus/)
 */

#ifndef GDATA_CLIENT_DOC_LIST_SERVICE_H_
#define GDATA_CLIENT_DOC_LIST_SERVICE_H_

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <curl/curl.h>

#include "../client/service.h"
#include "../util/string_utils.h"

namespace gdata {
namespace client {

using std::string;
using std::map;
using std::vector;

class DocListService : public Service {
 public:
  static const string kServiceName;
  static const string kDocListScope;
  static const string kDocListFeed;
  static const string kDocListFolderFeed;
  static const string kDocListAclFeed;
  static const string kDocumentCategory;
  static const string kSpreadsheetCategory;
  static const string kPresentationCategory;
  static const string kFolderCategory;
  static const string kStarredCategory;
  static const string kTrashedCategory;

  DocListService() {}
  DocListService(string email, string password, string application_name);
  ~DocListService() {}

  vector< map<string, string> > ListDocuments(string url, bool output=true);
  void ListAcls(string url);
  void UploadDoc(string filename, string title);
  void DeleteDoc(string url, string etag) const;
};

}}  // namespace gdata::client

#endif  // GDATA_CLIENT_DOC_LIST_SERVICE_H_
