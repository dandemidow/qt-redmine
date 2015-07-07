// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef USERCONVERTER
#define USERCONVERTER

#include "converter.h"
#include "user.h"

#define SET_ELEM(name, value) \
  { \
    QDomElement el = doc.createElement(#name); \
    el.appendChild(doc.createTextNode(value)); \
    user.appendChild(el); \
  }

template <>
struct Convert<User> {
  static Answer<User> exec(const QDomDocument &doc) {
    Answer<User> _ans;
    cnv::getInfo(doc, "users", _ans);
    START_PARSE_DOC(doc, user, _ans)
        GET_ELEMENT(id)
        GET_ELEMENT(login)
        GET_ELEMENT(firstname)
        GET_ELEMENT(lastname)
        GET_ELEMENT(mail)
    STOP_PARSE_DOC
    return _ans;
  }
  static QDomDocument encode(const User &u, const QString &pass) {
    QDomDocument doc;
    //  n.appendChild( n.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"") );
    QDomNode preNode = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.insertBefore(preNode, doc.firstChild());

    QDomElement user = doc.createElement("user");
    doc.appendChild(user);

    SET_ELEM(login, u.login)
    SET_ELEM(firstname, u.firstname)
    SET_ELEM(lastname, u.lastname)
    SET_ELEM(mail, u.mail)
    SET_ELEM(password, pass)
    return doc;
  }
};

#endif // USERCONVERTER

