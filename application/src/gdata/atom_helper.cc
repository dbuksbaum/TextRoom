#include "atom_helper.h"

namespace gdata {

using xmlpp::TextNode;
using xmlpp::Attribute;

AtomHelper::AtomHelper() {
  map<string, string> namespaces;
  namespaces_["atom"] = "http://www.w3.org/2005/Atom";
  namespaces_["openSearch"] = "http://a9.com/-/spec/opensearch/1.1/";
  RegisterNamespaces(namespaces);
}

void AtomHelper::RegisterNamespaces(const map<string, string>& namespaces) {
  map<string, string>::const_iterator iter;
  for (iter = namespaces.begin(); iter != namespaces.end(); ++iter) {
    namespaces_[iter->first] = iter->second;
  }
}

const Node* AtomHelper::Entry() const {
  const Node *node = NULL;

  if (parser_) {
    node = parser_.get_document()->get_root_node();
  }
  return node;
}

NodeSet AtomHelper::Entries() const {
  NodeSet entries;
  if (parser_) {
    entries = Find(parser_.get_document()->get_root_node(), "./atom:entry");
  }
  return entries;
}

string AtomHelper::AlternateLinkHref(const Node *entry) const {
  if (!parser_) return "";
  return Attribute(Link(entry, "alternate"), "href");
}

string AtomHelper::CategoryLabel(const Node *entry) const {
  if (!parser_) return "";

  string label;

  NodeSet categories = Find(entry, "./atom:category");
  for (unsigned int i = 0; i < categories.size(); ++i) {
    const Element *nodeElement = dynamic_cast<const Element*>(categories[i]);
    const Element::AttributeList& attributes =
        nodeElement->get_attributes();

    Element::AttributeList::const_iterator iter;
    for (iter = attributes.begin(); iter != attributes.end(); ++iter) {
      const xmlpp::Attribute *attribute = *iter;
      if (attribute->get_name() == "scheme" &&
          attribute->get_value() == "http://schemas.google.com/g/2005#kind") {
        label = Attribute(nodeElement, "label");
        break;
      }
    }
  }

  return label;
}

string AtomHelper::AclRole(const Node *entry) const {
  if (!parser_) return "";
  NodeSet roles = Find(entry, "./gAcl:role");
  if (roles.size()) {
    return Attribute(dynamic_cast<const Element*>(roles[0]), "value");
  } else {
    return "";
  }
}

string AtomHelper::AclScope(const Node *entry) const {
  if (!parser_) return "";
  NodeSet scopes = Find(entry, "./gAcl:scope");
  if (scopes.size()) {
    return Attribute(dynamic_cast<const Element*>(scopes[0]), "value");
  } else {
    return "";
  }
}

string AtomHelper::ContentSrc(const Node *entry) const {
  if (!parser_) return "";
  NodeSet contents = Find(entry, "./atom:content");
  if (contents.size()) {
    return Attribute(dynamic_cast<const Element*>(contents[0]), "src");
  } else {
    return "";
  }
}

string AtomHelper::EditLinkHref(const Node *entry) const {
  if (!parser_) return "";
  return Attribute(Link(entry, "edit"), "href");
}

string AtomHelper::EditMediaLinkHref(const Node *entry) const {
  if (!parser_) return "";
  return Attribute(Link(entry, "edit-media"), "href");
}

string AtomHelper::ETag(const Node *entry) const {
   if (!parser_) return "";
  return Attribute(dynamic_cast<const Element*>(entry), "etag");
}

string AtomHelper::FeedLinkHref(const Node *entry) const {
  if (!parser_) return "";
  NodeSet feedLinks = Find(entry, "./gd:feedLink");
  if (feedLinks.size()) {
    return Attribute(dynamic_cast<const Element*>(feedLinks[0]), "href");
  } else {
    return "";
  }
}

string AtomHelper::Id(const Node *entry) const {
  if (!parser_) return "";
  NodeSet ids = Find(entry, "./atom:id");
  if (ids.size()) {
    const TextNode *id =
        dynamic_cast<const TextNode*>(*ids[0]->get_children().begin());
    return id->get_content();
  } else {
    return "";
  }
}

string AtomHelper::Title(const Node *entry) const {
  if (!parser_) return "";
  NodeSet titles = Find(entry, "./atom:title");
  if (titles.size()) {
    const TextNode *title =
      dynamic_cast<const TextNode*>(*titles[0]->get_children().begin());
    return title->get_content();
  } else {
    return "";
  }
}

////////////////////////////////////////////////////////////////////////////////
// Private members
////////////////////////////////////////////////////////////////////////////////

string AtomHelper::Attribute(const Element *from_element,
                             string attr_name) const {
  if (!parser_) return "";

  const Element::AttributeList& attributes = from_element->get_attributes();

  Element::AttributeList::const_iterator iter;
  for (iter = attributes.begin(); iter != attributes.end(); ++iter) {
    const xmlpp::Attribute *attribute = *iter;
    if (attribute->get_name() == attr_name) {
      return attribute->get_value();
    }
  }
  return "";
}

const Element* AtomHelper::Link(const Node *entry, string rel) const {
  if (!parser_) return NULL;

  NodeSet links = Find(entry, "./atom:link");
  for (unsigned int i = 0; i < links.size(); ++i) {
    const Element *nodeElement = dynamic_cast<const Element*>(links[i]);
    const Element::AttributeList& attributes =
        nodeElement->get_attributes();

    Element::AttributeList::const_iterator iter;
    for (iter = attributes.begin(); iter != attributes.end(); ++iter) {
      const xmlpp::Attribute *attribute = *iter;
      if (attribute->get_name() == "rel" && attribute->get_value() == rel) {
        return nodeElement;
      }
    }
  }
  return NULL;
}

} // namespace gdata
