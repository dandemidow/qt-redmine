// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef USERSSENDER_H
#define USERSSENDER_H

#include "typing.h"

class UserWhoIAm :
    public Typing<Network::GET, UserWhoIAm> {
public:
  explicit UserWhoIAm() : Typing("users/current") {}
};

STANDARD_TYPES_REQUESTS(UserCmd, "users")

#endif // USERSSENDER_H
