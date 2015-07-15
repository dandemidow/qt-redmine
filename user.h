// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef USER
#define USER

#include <QString>
#include <QDebug>
#include "types.h"

#include <QDomDocument>

struct User {
  unsigned int id;
  QString login;
  QString firstname;
  QString lastname;
  QString mail;
  opt<QString> groups;
};

ADOPT_STRUCT(User)
  PARSE_ELEMENT_SAME(id)
  PARSE_ELEMENT_SAME(login)
  PARSE_ELEMENT_SAME(firstname)
  PARSE_ELEMENT_SAME(lastname)
  PARSE_ELEMENT_SAME(mail)
ADOPT_END

ADOPT_ANSWER(User, users, user)

#endif // USER
