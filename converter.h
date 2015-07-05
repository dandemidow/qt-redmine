// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef REDMINE_CONVERTER_
#define REDMINE_CONVERTER_

#include <QtXml/QDomDocument>

template<typename R>
struct conv {
  static R get(const QDomElement& );
};

template<>
struct conv <unsigned int> {
  static unsigned int get(const QDomElement& el) {
    return el.text().toUInt();
  }

  static unsigned int get(const QString &attr) {
    return attr.toUInt();
  }
};

template<>
struct conv <QString> {
  static QString get(const QDomElement& el) {
    return el.text();
  }
  static QString get(const QString &attr) {
    return attr;
  }
};

#define START_PARSE_DOC(doc, name, ans) \
  QDomNodeList node_list = doc.elementsByTagName(#name); \
  for (int i = 0; i<node_list.size(); ++i) { \
  typedef Q_TYPEOF(ans) answer_type; \
  typename answer_type::type st; \
  Q_TYPEOF(ans) &__ans = ans; \
  QDomNode node = node_list.item(i);

#define STOP_PARSE_DOC \
  __ans.items.append(st); \
  }

#define START_PARSE_ELEMENT(f) \
  { \
  QDomElement last = node.firstChildElement(#f); \
  Q_TYPEOF(st.f) &element = st.f;

#define STOP_PARSE_ELEMENT \
  }

#define GET_ATTRIBUTE(part) \
  element.part = conv<Q_TYPEOF(element.part)>::get(last.attribute(#part));

#define GET_ELEMENT(part) \
  st.part = conv<Q_TYPEOF(st.part)>::get(node.firstChildElement(#part));

template <typename T>
struct Convert {};

namespace cnv {
  template <class Ans>
  void getInfo(const QDomDocument &doc, const QString &type, Ans &ans) {
    QDomElement _types = doc.firstChildElement(type);
    if ( !_types.isNull() ) {
      ans.info->total_count = _types.attribute("total_count").toUInt(); \
      ans.info->offset = _types.attribute("offset").toUInt(); \
      ans.info->limit = _types.attribute("limit").toUInt(); \
      ans.info->type = _types.attribute("type");
    }
  }
}  // namespace cnv

#endif  // REDMINE_CONVERTER_
