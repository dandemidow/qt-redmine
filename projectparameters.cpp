// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#include "projectparameters.h"

namespace prj {

Only::Only(unsigned int id) : _id(id) {
}

void Only::setPath(QUrl &url) const {
  url.setPath("/projects/"+QString::number(_id)+".xml");
}


void All::setPath(QUrl &url) const {
  url.setPath("/projects.xml");
}

}  // namespace prj
