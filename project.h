// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef PROJECT
#define PROJECT

#include <QString>
#include "types.h"

struct Project {
  unsigned int id;
  QString name;
  QString identifier;
  QString description;
  QString created_on;
  QString updated_on;
};

struct ProjectMember {
  unsigned int id;
  IdType project;
  IdType user;
  // roles
};

#endif // PROJECT

