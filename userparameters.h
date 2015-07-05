// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef USERPARAMETERS
#define USERPARAMETERS

#include "parameter.h"

namespace usr {

class Membership : public Include {
public:
  explicit Membership();
};

class Groups : public Include {
public:
  explicit Groups();
};

}  // namespace usr

#endif // USERPARAMETERS

