// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

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

#endif // PROJECT

