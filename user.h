// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef USER
#define USER

#include <QString>
#include "types.h"


struct User {
  unsigned int id;
  QString login;
  QString firstname;
  QString lastname;
  QString mail;
  opt<QString> groups;
};

#endif // USER

