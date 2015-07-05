// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef PROJECTPARAMETERS_H
#define PROJECTPARAMETERS_H

#include "parameter.h"

namespace prj {

class Only : public Parameter {
  unsigned int _id;
public:
  explicit Only(unsigned int id);
  void setPath(QUrl &url) const;
};

class All : public Parameter {
public:
  void setPath(QUrl &url) const;
};

}  // namespace prj

#endif // PROJECTPARAMETERS_H
