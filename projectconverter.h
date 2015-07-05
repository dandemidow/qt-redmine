// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef PROJECTCONVERTER
#define PROJECTCONVERTER

#include "project.h"
#include "converter.h"

template <>
struct Convert<Project> {
  static Answer<Project> exec(const QDomDocument &doc) {
    Answer<Project> _ans;
    cnv::getInfo(doc, "projects", _ans);
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

