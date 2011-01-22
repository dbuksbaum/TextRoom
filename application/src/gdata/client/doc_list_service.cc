#include "doc_list_service.h"

namespace gdata {
namespace client {

const string DocListService::kServiceName = "writely";
const string DocListService::kDocListScope = "http://docs.google.com/feeds";
const string DocListService::kDocListFeed = "/documents/private/full";
const string DocListService::kDocListFolderFeed = "/folders/private/full/";
const string DocListService::kDocListAclFeed = "/acl/private/full/";
const string DocListService::kDocumentCategory = "/-/document";
const string DocListService::kSpreadsheetCategory = "/-/spreadsheet";
const string DocListService::kPresentationCategory = "/-/presentation";
const string DocListService::kFolderCategory = "/-/folder";
const string DocListService::kStarredCategory = "/-/starred";
const string DocListService::kTrashedCategory = "/-/trashed";

DocListService::DocListService(
    string email, string password, string application_name) :
    Service(kServiceName, application_name) {
  ClientLogin(email, password);

  // register namespaces used by the DocList APIs
  map<string, string> doclist_namespaces;
  doclist_namespaces["gAcl"] = "http://schemas.google.com/acl/2007";
  doclist_namespaces["gd"] = "http://schemas.google.com/g/2005";
  atom_helper_.RegisterNamespaces(doclist_namespaces);
}

vector< map<string, string> > DocListService::ListDocuments(
    string url, bool output/*=true*/) {
  vector< map<string, string> > docs;

  atom_helper_.Parse(HttpRequest("GET", url));
  xmlpp::NodeSet entries = atom_helper_.Entries();

  if (entries.size() && output) {
    cout << "doc: documents, spre: spreadsheets, pres: presentations, "
         << "fol: folders, pdf: pdfs, U: unknown\n";
  }

  for (unsigned int i = 0; i < entries.size(); ++i) {
    map<string, string> data;

    data["category"] = atom_helper_.CategoryLabel(entries[i]);
    data["content_src"] = atom_helper_.ContentSrc(entries[i]);
    data["edit_link"] = atom_helper_.EditLinkHref(entries[i]);
    data["etag"] = atom_helper_.ETag(entries[i]);
    data["id"] = atom_helper_.Id(entries[i]);
    data["title"] = atom_helper_.Title(entries[i]);
    data["acl_feedLink"] = atom_helper_.FeedLinkHref(entries[i]);
    
    string doc_type = "U";
    if (data["category"] == "document") {
      doc_type = "doc";
    } else if (data["category"] == "spreadsheet") {
      doc_type = "spre";
    } else if (data["category"] == "presentation") {
      doc_type = "pres";
    } else if (data["category"] == "folder") {
      doc_type = "fol";
    } else if (data["category"] == "pdf") {
      doc_type = "pdf";
    }

    if (output) {
      cout << "[" << doc_type << "] \t" << data["title"] << endl;
    }

    data["doc_type"] = doc_type;
    docs.push_back(data);
  }

  return docs;
}

void DocListService::ListAcls(string url) {
  vector< map<string, string> > acls;

  atom_helper_.Parse(HttpRequest("GET", url));

  xmlpp::NodeSet entries = atom_helper_.Entries();
  cout << "Document's permissions\n";
  for (unsigned int i = 0; i < entries.size(); ++i) {
    string title = atom_helper_.Title(entries[i]);
    string role = atom_helper_.AclRole(entries[i]);
    string scope = atom_helper_.AclScope(entries[i]);
    cout << role << " : " << scope << endl;
  }
}

void DocListService::UploadDoc(string filename, string title) {
  PostData post_data;
  post_data.data = NULL;
  post_data.filename = filename;

  // Setup headers for this request
  vector<string> custom_headers;
  custom_headers.push_back("Slug: " + title);

  string file_extension =
      gdata::util::StringUtils::to_lowercase(filename.substr(filename.rfind('.') + 1));
  if (file_extension == "csv") {
    cout << "\nUploading spreadsheet\n";
    custom_headers.push_back("Content-Type: text/csv");

  } else if (file_extension == "doc") {
    cout << "\nUploading MS word document\n";
    custom_headers.push_back("Content-Type: application/msword");

  } else if (file_extension == "htm" || file_extension == "html") {
    cout << "\nUploading html document\n";
    custom_headers.push_back("Content-Type: text/html");

  } else if (file_extension == "ods") {
    cout << "\nUploading OpenOffice spreadsheet\n";
    custom_headers.push_back("Content-Type: application/x-vnd.oasis.opendocument.spreadsheet");

  } else if (file_extension == "odt") {
    cout << "\nUploading OpenOffice word document\n";
    custom_headers.push_back("Content-Type: application/vnd.oasis.opendocument.text");

  } else if (file_extension == "pps" || file_extension == "ppt") {
    cout << "\nUploading MS Power Point presentation\n";
    custom_headers.push_back("Content-Type: application/vnd.ms-powerpoint");

  } else if (file_extension == "rtf") {
    cout << "\nUploading rich text document\n";
    custom_headers.push_back("Content-Type: application/rtf");

  } else if (file_extension == "tab" || file_extension == "tsv") {
    cout << "\nUploading spreadsheet\n";
    custom_headers.push_back("Content-Type: text/tab-separated-values");

  } else if (file_extension == "xls") {
    cout << "\nUploading spreadsheet\n";
    custom_headers.push_back("Content-Type: application/vnd.ms-excel");

  } else {
    cout << "\nUploading plain ol' text document\n";
    custom_headers.push_back("Content-Type: text/plain");
  }

  string response = HttpRequest("POST", kDocListScope + kDocListFeed,
                                custom_headers, post_data);

  if (response != "") {
    atom_helper_.Parse(response);
    string alternate_link =
        atom_helper_.AlternateLinkHref(atom_helper_.Entry());
    cout << "\nDocument created: " << alternate_link << endl;
  }
}

void DocListService::DeleteDoc(string url, string etag) const {
  vector<string> custom_headers;
  custom_headers.push_back("If-Match: " + etag);

  string response = HttpRequest("DELETE", url, custom_headers);
  cout << "\nDeleted!\n";
}

}}  // namespace gdata::client
