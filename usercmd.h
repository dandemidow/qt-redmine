// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef USERSSENDER_H
#define USERSSENDER_H

#include <QObject>
#include "parameter.h"
#include "pathing.h"
#include "including.h"

class UserCmd :
    public Path<UserCmd>,
    public Includeble<UserCmd> {
public:
  explicit UserCmd() : Path("users") {}
  void setPath(QUrl &url) const {
    url.setPath(path());
    url.setQuery(query());
  }
};

#endif // USERSSENDER_H
