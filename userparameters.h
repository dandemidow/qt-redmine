// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

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

