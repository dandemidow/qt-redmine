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
    START_PARSE_DOC(doc, issue, _ans)
      GET_ELEMENT(id)
      GET_IDTYPE_ELEMENT(project)
      GET_IDTYPE_ELEMENT(tracker)
      GET_IDTYPE_ELEMENT(status)
      GET_IDTYPE_ELEMENT(priority)
      GET_IDTYPE_ELEMENT(author)
      GET_ELEMENT(subject)
      GET_ELEMENT(description)
      GET_ELEMENT(start_date)
      GET_ELEMENT(due_date)
      GET_ELEMENT(done_ratio)
      GET_ELEMENT(estimated_hours)
      GET_ELEMENT(created_on)
      GET_ELEMENT(updated_on)
      GET_ELEMENT(closed_on)
    STOP_PARSE_DOC
    return _ans;
  }
};


#endif // ISSUECONVERTER

