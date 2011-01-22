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

#ifndef GDATA_CLIENT_SERVICE_H_
#define GDATA_CLIENT_SERVICE_H_

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "../util/string_utils.h"
#include "../atom_helper.h"

namespace gdata {
namespace client {

using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;

struct PostData {
  char *data;
  string filename;
};

const string kVersion = "1.0";
const string kClientLoginUrl =
    "https://www.google.com/accounts/ClientLogin";
const string kClientLoginAuthHeaderPrefix =
    "Authorization: GoogleLogin auth=";

class Service {
 public:
  Service() {}
  Service(const string& service_name, const string& application_name);
  ~Service() {}

  const string& auth_token() const { return auth_token_; }
  void set_auth_token(const string& token) { auth_token_ = token; }

  const string& service_name() const { return service_name_; }
  void set_service_name(const string &name) { service_name_ = name; }

  const string& application_name() const { return application_name_; }
  void set_application_name(const string& name) { application_name_ = name; }

  const vector<string>& request_headers() const { return request_headers_; }
  void set_request_headers(const vector<string>& headers) {
    request_headers_ = headers;
  }

  void ClientLogin(string email,
                   string password,
                   string account_type="HOSTED_OR_GOOGLE");

  string HttpRequest(const string& http_method, const string& url) const;
  string HttpRequest(const string& http_method,
                     const string& url,
                     const vector<string>& custom_headers,
                     const PostData& post_data) const;
  string HttpRequest(const string& http_method,
                     const string& url,
                     const vector<string>& custom_headers) const;
  string HttpRequest(const string& http_method,
                     const string& url,
                     const PostData& post_data) const;

 protected:
  string auth_token_;
  string service_name_;
  string application_name_;
  vector<string> request_headers_;
  gdata::AtomHelper atom_helper_;

 private:
  static size_t WriteCallback(char* data,
                              size_t size,
                              size_t nmemb,
                              string* buffer);
};

}}  // namespace gdata::client

#endif  // GDATA_CLIENT_SERVICE_H_
