// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef ISSUE
#define ISSUE

#include <QString>
#include "types.h"

struct Issue {
  unsigned int id;
  IdType project;
  IdType tracker;
  QString subject;
};

#endif // ISSUE

