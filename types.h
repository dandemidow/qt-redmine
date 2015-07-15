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
  hand(QDomDocument &_doc, const QDomElement &el) :
    doc(_doc),
    elem(el) {}
  void set(T &i) {
    QString name;
    QDomElement el = doc.createElement(name);
    el.appendChild(doc.createTextNode(conv<QString>::get(i)));
    elem.appendChild(el);
  }
  void get(T &i) {
    i = conv<T>::get(elem.text());
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
    void set(st_type &s) { \
      (void)(s);\
    } \
    void get(st_type &s) { \
      foreach (__base *f, __handlers) { \
        f->get(s); \
      } \
    } \
  };

#define PARSE_ATTRIBUTE(name, element) \
  struct _##name : __base { \
    void get(st_type &s){ \
      s.name = conv<Q_TYPEOF(s.name)>::get(_element.attribute(QString::fromLatin1(#element))); \
    } \
    void set(st_type &s) { \
      (void)(s); \
    } \
    _##name(QDomDocument &_d, const QDomElement &_e) : __base(_d, _e) {} \
  }; \
  __handlers.append(new _##name(_doc, _el)); \

#define PARSE_ATTRIBUTE_SAME(name) \
  PARSE_ATTRIBUTE(name, name)




#define ADOPT_STRUCT(st) \
  template <> \
  struct hand<st> { \
    typedef st st_type; \
    struct __base { \
      QDomDocument &_document; \
      QDomElement _element; \
      virtual void get(st_type &s) = 0; \
      virtual void set(st_type &s) = 0; \
      __base(QDomDocument &_d, const QDomElement &_e) : _document(_d), _element(_e) {} \
    }; \
    QList<__base *> __handlers; \
    hand(QDomDocument &_doc, const QDomElement &_el) {

#define ADOPT_END \
  } \
  void set(st_type &s) { \
    (void)(s);\
  } \
  void get(st_type &s) { \
    foreach (__base *f, __handlers) { \
      f->get(s); \
    } \
  } \
};

#define PARSE_ELEMENT(name, element) \
  struct _##name : __base { \
    void get(st_type &s){ \
      QDomElement element = _element.tagName()!=QString::fromLatin1(#element)?_element.firstChildElement(QString::fromLatin1(#element)):_element; \
      hand<Q_TYPEOF(s.name)>(_document, element).get(s.name); \
    } \
    void set(st_type &s) { \
      hand<Q_TYPEOF(s.name)>(_document, _element).set(s.name); \
    } \
    _##name(QDomDocument &_d, const QDomElement &_e) : __base(_d, _e) {} \
  }; \
  __handlers.append(new _##name(_doc, _el)); \

#define PARSE_ELEMENT_SAME(name) \
  PARSE_ELEMENT(name, name)

#define PARSE_LIST(nodes, node) \
  struct _##nodes : __base { \
    void get(st_type &s){ \
      QDomElement element = _element.firstChildElement(QString::fromLatin1(#nodes)); \
      hand<Q_TYPEOF(s.nodes)>(_document, element, QString::fromLatin1(#node)).get(s.nodes); \
    } \
    void set(st_type &s) { \
      hand<Q_TYPEOF(s.nodes)>(_document, _element, QString::fromLatin1(#node)).set(s.nodes); \
    } \
    _##nodes(QDomDocument &_d, const QDomElement &_e) : __base(_d, _e) {} \
  }; \
  __handlers.append(new _##nodes(_doc, _el)); \

template<>
template<typename T>
struct hand<QList<T> > {
  QDomDocument &doc;
  QDomElement elem;
  QString item_name;
  hand(QDomDocument &_doc, const QDomElement &el, const QString &name) :
    doc(_doc),
    elem(el),
    item_name(name) { }
  void set(QList<T> &i) {
    (void)(i);
  }
  void get(QList<T> &l) {
    QDomNodeList list = elem.elementsByTagName(item_name);
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

template <class T>
struct AnswerTraits;

#define ADOPT_ANSWER(st, nodes, name) \
  template <> \
  struct AnswerTraits <Answer<st> > { \
    static QString nodes_name() { return QString::fromLatin1(#nodes); } \
    static QString node_name() { return QString::fromLatin1(#name); } \
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
  void set(Answer<T> &ans) {
    (void)(ans);
  }
  void get(Answer<T> &l) {
    QString name = AnswerTraits<Q_TYPEOF(l)>::node_name();
    QString names = AnswerTraits<Q_TYPEOF(l)>::nodes_name();
    if ( elem.tagName() == name ) {
      T t;
      hand<T>(doc, elem).get(t);
      l.items.append(t);
    } else {
      QDomElement list = elem.tagName()==names?elem:elem.firstChildElement(names);
      cnv::getInfo(list, l);
      hand<Q_TYPEOF(l.items)>(doc, list, name).get(l.items);
    }
  }
};


#endif // TYPES

