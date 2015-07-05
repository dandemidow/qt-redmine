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
};

#endif // USERCONVERTER

