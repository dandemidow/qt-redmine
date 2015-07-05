// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

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

