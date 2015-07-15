// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef PROJECTSSENDER_H
#define PROJECTSSENDER_H

#include "typing.h"

STANDARD_TYPES_REQUESTS(ProjectCmd, "projects")

class ProjectMembers :
  public Typing<Network::GET, ProjectMembers> {
  public:
    ProjectMembers(unsigned int id) : Typing(QString::fromLatin1("projects/")+QString::number(id)+QString::fromLatin1("/memberships")) {}
    ProjectMembers(const char* name) : Typing(QString::fromLatin1("projects/")+QString::fromLatin1(name)+QString::fromLatin1("/memberships")) {}
};

#endif // PROJECTSSENDER_H
