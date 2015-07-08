// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef INCLUDING
#define INCLUDING

#include <QString>
#include <QUrl>
#include "parameter.h"

template <class Self>
class Includeble {
  QString _include;
public:
  explicit Includeble() {}

  Self &operator <<(const Include &i) {
    this->_include = i.getInclude();
    return *(static_cast<Self*>(this));
  }

  Self &operator <<(const Filter &f) {
    this->_include = f.getFilter();
    return *(static_cast<Self*>(this));
  }

  QString query() const {
    return _include;
  }
  void setQuery(QUrl &url) const {
    url.setQuery(_include);
  }
};

#endif // INCLUDING

