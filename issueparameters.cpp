// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#include "issueparameters.h"

namespace iss {

  Only::Only(unsigned int id) : _id(id) {
  }

  void Only::setPath(QUrl &url) const {
    url.setPath("/issues/"+QString::number(_id)+".xml");
  }


  void All::setPath(QUrl &url) const {
    url.setPath("/issues.xml");
  }

}  // namespace iss
