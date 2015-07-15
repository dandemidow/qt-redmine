// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef REDMINE_CONVERTER_
#define REDMINE_CONVERTER_

#include <QVariant>
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
  static unsigned int get(const QVariant &i) {
    return i.toUInt();
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
  static QString get(const unsigned int &i) {
    return QString::number(i);
  }
  static QString get(const QVariant &i) {
    return i.toString();
  }
};

template<>
struct conv <bool> {
  static bool get(const QDomElement& el) {
    return QVariant(el.text()).toBool();
  }
  static bool get(const QString &attr) {
    return QVariant(attr).toBool();
  }
};

template<>
struct conv <QVariant> {
  static QVariant get(const QDomElement& el) {
    return QVariant(el.text());
  }
  static QVariant get(const QString &attr) {
    return attr;
  }
  static QVariant get(const unsigned int &i) {
    return QVariant(i);
  }
  static QVariant get(QVariant &i) {
    return i;
  }
};

#define START_PARSE_DOC(doc, name, ans) \
  typedef Q_TYPEOF(ans) answer_type; \
  typename answer_type::type st; \
  Q_TYPEOF(ans) &__ans = ans; \
  QDomNodeList node_list = doc.elementsByTagName(QString::fromLatin1(#name)); \
  for (int i = 0; i<node_list.size(); ++i) { \
  QDomNode node = node_list.item(i);

#define STOP_PARSE_DOC \
  __ans.items.append(st); \
  }

#define START_PARSE_ELEMENT(f) \
  { \
  QDomElement last = node.firstChildElement(QString::fromLatin1(#f)); \
  Q_TYPEOF(st.f) &element = st.f;

#define STOP_PARSE_ELEMENT \
  }

#define GET_ATTRIBUTE(part) \
  element.part = conv<Q_TYPEOF(element.part)>::get(last.attribute(QString::fromLatin1(#part)));

#define GET_ELEMENT(part) \
  st.part = conv<Q_TYPEOF(st.part)>::get(node.firstChildElement(QString::fromLatin1(#part)));

#define GET_IDTYPE_ELEMENT(idel) \
  START_PARSE_ELEMENT(idel) \
    GET_ATTRIBUTE(id) \
    GET_ATTRIBUTE(name) \
  STOP_PARSE_ELEMENT

#define START_PARSE_LIST(listname) \
  { \
  Q_TYPEOF(st.listname) & __list = st.listname; \
  typedef Q_TYPEOF(__list.front()) sublist_type; \
  QString listname_s = QString::fromLatin1(#listname)+"s"; \
  QDomElement el = node.firstChildElement(listname_s); \
  QDomNodeList nodes; \
  if (el.isNull()) nodes = doc.elementsByTagName(QString::fromLatin1(#listname)); \
  else nodes = el.elementsByTagName(QString::fromLatin1(#listname)); \
  for ( int j = 0; j<nodes.size(); ++j ) { \
    sublist_type st; \
    QDomNode node = nodes.item(j);

#define STOP_PARSE_LIST \
    __list.append(st); \
    } \
  }

template <typename T>
struct Convert {};

namespace cnv {
  template <class Ans>
  void getInfo(const QDomElement &_types, Ans &ans) {
    if ( !_types.isNull() ) {
      ans.info->total_count = _types.attribute(QString::fromLatin1("total_count")).toUInt(); \
      ans.info->offset = _types.attribute(QString::fromLatin1("offset")).toUInt(); \
      ans.info->limit = _types.attribute(QString::fromLatin1("limit")).toUInt(); \
      ans.info->type = _types.attribute(QString::fromLatin1("type"));
    }
  }
}  // namespace cnv

#endif  // REDMINE_CONVERTER_

