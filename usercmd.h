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

#include <QObject>
#include "parameter.h"
#include "pathing.h"
#include "including.h"
#include "typing.h"

class UserCmd :
    public Path,
    public Typing<Network::GET, UserCmd> {
public:
  explicit UserCmd() : Path("users") {}
  explicit UserCmd(unsigned int id) : Path("users", id) {}
  void setPath(QUrl &url) const {
    Path::setPath(url);
    Includeble::setQuery(url);
  }
};

class UserCmdPost :
    public Path,
    public Typing<Network::POST, UserCmdPost> {
public:
  explicit UserCmdPost() : Path("users") {}
};

class UserCmdPut :
    public Path,
    public Typing<Network::PUT, UserCmdPut> {
public:
  explicit UserCmdPut(unsigned int id) : Path("users", id) {}
};

class UserCmdDel :
    public Path,
    public Typing<Network::DELETE, UserCmdDel> {
public:
  explicit UserCmdDel(unsigned int id) : Path("users", id) {}
};

class UserWhoIAm :
    public Path,
    public Typing<Network::GET, UserWhoIAm> {
public:
  explicit UserWhoIAm() : Path("users/current") {}
  void setPath(QUrl &url) const {
    Path::setPath(url);
    Includeble::setQuery(url);
  }
};

#endif // USERSSENDER_H
