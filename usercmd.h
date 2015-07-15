// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef USERSSENDER_H
#define USERSSENDER_H

#include "typing.h"
#include "parameter.h"

class UserWhoIAm :
    public Typing<Network::GET, UserWhoIAm> {
public:
  explicit UserWhoIAm() : Typing("users/current") {}
};

STANDARD_TYPES_REQUESTS(UserCmd, "users")

namespace usr {

class Membership : public Include {
public:
  explicit Membership() : Include("memberships") {}
};

class Groups : public Include {
public:
  explicit Groups() : Include("groups") {}
};

}  // namespace usr

#endif // USERSSENDER_H
