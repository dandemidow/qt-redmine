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

ADOPT_STRUCT(Project)
  PARSE_ELEMENT_SAME(id)
  PARSE_ELEMENT_SAME(name)
  PARSE_ELEMENT_SAME(identifier)
  PARSE_ELEMENT_SAME(description)
  PARSE_ELEMENT_SAME(created_on)
  PARSE_ELEMENT_SAME(updated_on)
ADOPT_END

ADOPT_ANSWER(Project, projects, project)

struct ProjectMember {
  unsigned int id;
  IdType project;
  IdType user;
  // roles
};

ADOPT_STRUCT(ProjectMember)
  PARSE_ELEMENT_SAME(id)
  PARSE_ELEMENT_SAME(project)
  PARSE_ELEMENT_SAME(user)
ADOPT_END

ADOPT_ANSWER(ProjectMember, memberships, membership)

#endif // PROJECT

