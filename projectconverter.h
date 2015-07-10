// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef PROJECTCONVERTER
#define PROJECTCONVERTER

#include "project.h"
#include "converter.h"

template <>
struct Convert<Project> {
  static Answer<Project> exec(const QDomDocument &doc) {
    Answer<Project> _ans;
    cnv::getInfo(doc, QString::fromLatin1("projects"), _ans);
    START_PARSE_DOC(doc, project, _ans)
        GET_ELEMENT(id);
        GET_ELEMENT(name);
        GET_ELEMENT(identifier);
        GET_ELEMENT(description);
        GET_ELEMENT(created_on);
        GET_ELEMENT(updated_on);
    STOP_PARSE_DOC
    return _ans;
  }
};

#endif // PROJECTCONVERTER

