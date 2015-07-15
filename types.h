// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef TYPES
#define TYPES

#include <QDebug>
#include <QString>
#include "converter.h"

template <typename T>
struct hand {
  QDomDocument &doc;
  QDomElement elem;
  hand(QDomDocument &_doc, QDomElement &el) :
    doc(_doc),
    elem(el) {}
  void set(T &i, const QString &name) {
    QDomElement el = doc.createElement(name);
    el.appendChild(doc.createTextNode(conv<QString>::get(i)));
    elem.appendChild(el);
  }
  void get(T &i, const QString &name) {
    QDomElement l = elem.firstChildElement(name);
    i = conv<T>::get(elem.firstChildElement(name).text());
  }
};

#define ADOPT_STRUCT_ATTRIBUTE(name) \
  template <> \
  struct hand<name> { \
    typedef name st_type; \
    QDomDocument &_doc; \
    QDomElement _el; \
    struct __base { \
      QDomDocument &_document; \
      QDomElement _element; \
      virtual void get(st_type &s) = 0; \
      virtual void set(st_type &s) = 0; \
      __base(QDomDocument &_d, const QDomElement &_e) : _document(_d), _element(_e) {} \
    }; \
    QList<__base *> __handlers; \
    hand(QDomDocument &doc, const QDomElement &el) : \
      _doc(doc), \
      _el(el) {

#define ADOPT_STRUCT_ATTRIBUTE_END \
    } \
    void set(st_type &s, const QString &name) { \
      (void)(s);\
      (void)(name);\
    } \
    void get(st_type &s, const QString &name) { \
      QDomElement l = _el; \
      if ( _el.tagName() != name ) \
        l = _el.firstChildElement(name); \
      foreach (__base *f, __handlers) { \
        f->_element = l; \
        f->get(s); \
      } \
    } \
  };

#define PARSE_ATTRIBUTE(name, element) \
  struct _##name : __base { \
    void get(st_type &s){ \
      s.name = conv<Q_TYPEOF(s.name)>::get(_element.attribute(#element)); \
    } \
    void set(st_type &s) { \
      (void)(s); \
    } \
    _##name(QDomDocument &_d, QDomElement &_e) : __base(_d, _e) {} \
  }; \
  __handlers.append(new _##name(_doc, _el)); \

#define PARSE_ATTRIBUTE_SAME(name) \
  PARSE_ATTRIBUTE(name, name)




#define PARSE_ELEMENT(name, element) \
  struct _##name : __base { \
    void get(st_type &s){ \
      hand<Q_TYPEOF(s.name)>(_document, _element).get(s.name, #element); \
    } \
    void set(st_type &s) { \
      hand<Q_TYPEOF(s.name)>(_document, _element).set(s.name, #element); \
    } \
    _##name(QDomDocument &_d, QDomElement &_e) : __base(_d, _e) {} \
  }; \
  __handlers.append(new _##name(_doc, _el)); \

#define PARSE_ELEMENT_SAME(name) \
  PARSE_ELEMENT(name, name)

#define ADOPT_STRUCT(st) \
  template <> \
  struct hand<st> { \
    typedef st st_type; \
    struct __base { \
      QDomDocument &_document; \
      QDomElement &_element; \
      virtual void get(st_type &s) = 0; \
      virtual void set(st_type &s) = 0; \
      __base(QDomDocument &_d, QDomElement &_e) : _document(_d), _element(_e) {} \
    }; \
    QList<__base *> __handlers; \
    hand(QDomDocument &_doc, QDomElement &_el) {

#define ADOPT_END \
  } \
  void get(st_type &s) { \
    foreach (__base *f, __handlers) { \
      f->get(s); \
    } \
  } \
};

template<>
template<typename T>
struct hand<QList<T> > {
  QDomDocument &doc;
  QDomElement elem;
  hand(QDomDocument &_doc, const QDomElement &el) :
    doc(_doc),
    elem(el) {}
  void set(QList<T> &i, const QString &name) {
    (void)(i);
    (void)(name);
  }
  void get(QList<T> &l, const QString &name) {
    QDomNodeList list = elem.elementsByTagName(name);
    for (int i=0; i<list.size(); ++i) {
      QDomNode node = list.item(i);
      T t;
      QDomElement one = node.toElement();
      hand<T>(doc, one).get(t);
      l.append(t);
    }
  }
};


struct IdType {
  unsigned int id;
  QString name;
};

ADOPT_STRUCT_ATTRIBUTE(IdType)
  PARSE_ATTRIBUTE_SAME(id)
  PARSE_ATTRIBUTE_SAME(name)
ADOPT_STRUCT_ATTRIBUTE_END

struct ListType {
  unsigned int total_count;
  unsigned int offset;
  unsigned int limit;
  QString type;
};

template<typename T>
class opt {
  bool exist;
  T d;
public:
  explicit opt():exist(false) {}
  explicit opt(const T &v) : d(v) {}
  T &operator = (const T &v) { d = v; exist = true; return d; }
  operator bool() const { return exist; }
  operator T() const { return d; }
  T *operator -> () { exist = true; return &d; }

  template <typename S>
  friend S &operator << (S &s, const opt<T> &o) {
    s<<o.value;
    return s;
  }
};



template <typename T>
struct Answer {
  typedef T type;
  opt<ListType> info;
  QList<T> items;
};

template<>
template<typename T>
struct hand<Answer<T> > {
  QDomDocument &doc;
  QDomElement elem;
  hand(QDomDocument &_doc, const QDomElement &el) :
    doc(_doc),
    elem(el) {}
  hand(QDomDocument &_doc) :
    doc(_doc),
    elem(doc.lastChild().toElement()) {}
  void set(Answer<T> &ans, const QString &name) {
    (void)(ans);
    (void)(name);
  }
  void get(Answer<T> &l, const QString &names) {
    QString name = names.left(names.size()-1);
    if ( elem.tagName() == name ) {
      T t;
      hand<T>(doc, elem).get(t);
      l.items.append(t);
    } else {
      QDomElement list = elem.tagName()==names?elem:elem.firstChildElement(names);
      cnv::getInfo(list, l);
      hand<Q_TYPEOF(l.items)>(doc, list).get(l.items, name);
    }
  }
};


#endif // TYPES

