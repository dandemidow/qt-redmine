// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef ISSUECONVERTER
#define ISSUECONVERTER

#include "converter.h"
#include "issue.h"

template <>
struct Convert<Issue> {
  static Answer<Issue> exec(const QDomDocument &doc) {
    Answer<Issue> _ans;
    cnv::getInfo(doc, "issues", _ans);
    START_PARSE_DOC(doc, "issue", _ans)
      START_PARSE_ELEMENT(project)
        GET_ATTRIBUTE(id)
        GET_ATTRIBUTE(name)
      STOP_PARSE_ELEMENT
    STOP_PARSE_DOC
    return _ans;
  }
};


#endif // ISSUECONVERTER

