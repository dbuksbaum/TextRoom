#include "service.h"

namespace gdata {
namespace client {

using std::ifstream;
using std::ios;

Service::Service(const string &service_name, const string &application_name)
    : service_name_(service_name),
      application_name_(application_name) {

  // Standard headers for every request
  request_headers_.push_back("User-Agent: " + application_name +
                             " GData-C++/" + kVersion);
  request_headers_.push_back("GData-Version: 2.0");
}

void Service::ClientLogin(string email,
                          string password,
                          string account_type /*=HOSTED_OR_GOOGLE*/) {
  string body = "Email=" + email + "&Passwd=" + password +
                "&accountType=" + account_type +
                "&source=" + application_name_ + "&service=" + service_name_;

  PostData post_data;
  post_data.data = const_cast<char*>(body.c_str());
  string resp = HttpRequest("POST", kClientLoginUrl, post_data);

  string prefix = "Auth=";  // prefix of the ClientLogin token
  string token = resp.substr(resp.find(prefix) + prefix.size());

  auth_token_ = token.substr(0, token.size() - 1);  // remove trailing "\n"

  // Attach Authorization header to every subsequent request
  request_headers_.push_back(kClientLoginAuthHeaderPrefix + auth_token_);
}

string Service::HttpRequest(const string& http_method,
                            const string& url) const {
  vector<string> custom_headers = vector<string>();
  PostData post_data;
  return HttpRequest(http_method, url, custom_headers, post_data);
}

string Service::HttpRequest(const string& http_method,
                            const string& url,
                            const vector<string>& custom_headers) const {
  PostData post_data;
  return HttpRequest(http_method, url, custom_headers, post_data);
}

string Service::HttpRequest(const string& http_method,
                            const string& url,
                            const PostData& post_data) const {
  vector<string> custom_headers = vector<string>();
  return HttpRequest(http_method, url, custom_headers, post_data);
}

string Service::HttpRequest(const string& http_method,
                            const string& url,
                            const vector<string>& custom_headers,
                            const PostData& post_data) const {
  string resp_buffer;  // body of the response from the server
  char *memblock = NULL;  // file size of POST body
  CURL *curl = curl_easy_init();

  if (curl) {
    char errorBuffer[CURL_ERROR_SIZE];

    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp_buffer);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE , 1);

    struct curl_slist *headers = NULL;

    // Add standard headers
    for (unsigned int i = 0; i < request_headers_.size(); ++i) {
      headers = curl_slist_append(headers, request_headers_[i].c_str());
    }

    // Add any custom headers
    for (unsigned int i = 0; i < custom_headers.size(); ++i) {
      headers = curl_slist_append(headers, custom_headers[i].c_str());
    }

    if (http_method == "GET") {
      curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
      headers =
          curl_slist_append(headers, "Content-Type: application/atom+xml");

    } else if (http_method == "POST") {
      curl_easy_setopt(curl, CURLOPT_POST, 1);

      // Configure post for plain text or binary data
      if (post_data.data != NULL) {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(post_data.data));
      } else {
        ifstream file(post_data.filename.c_str(), ios::binary | ios::ate);

        if (!file) {
          cerr << "\nError: Cannot open file '" << post_data.filename << "'\n";
          return resp_buffer;
        } else {
          int file_size = static_cast<int>(file.tellg());
          memblock = new char[file_size];
          file.seekg(0, ios::beg);
          file.read(memblock, file_size);
          file.close();

          curl_easy_setopt(curl, CURLOPT_POSTFIELDS, memblock);
          curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, file_size);
        }
      }
    } else if (http_method == "PUT") {
      curl_easy_setopt(curl, CURLOPT_PUT, 1L);

    } else if (http_method == "DELETE") {
      curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    } else {
      cerr << "Error: Unknown http method - " << http_method << endl;
      exit(1);
    }

    // attach headers to this request
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode curl_code = curl_easy_perform(curl);

    int http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    // clean up
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    if (memblock != NULL) {
      delete[] memblock;
    }

    if (curl_code != CURLE_OK) {
      cout << "\nError: [" << curl_code << "] - " << errorBuffer;
      exit(1);
    } else if (400 <= http_code) {
      cout << "\nError: " << http_code << " response" << endl
           << resp_buffer << endl;
      exit(1);
    }
  }

  return resp_buffer;
}


////////////////////////////////////////////////////////////////////////////////
// Private members
////////////////////////////////////////////////////////////////////////////////

// This is the writer call back function used by curl
size_t Service::WriteCallback(char *data,
                              size_t size,
                              size_t nmemb,
                              string *buffer) {
  int result = 0;

  if (buffer != NULL) {
    buffer->append(data, size * nmemb);
    result = size * nmemb;  // How much did we write?
  }
  return result;
}

}}  // namespace gdata::client
