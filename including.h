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

template <class Self>
class Includeble {
  bool _included;
  QString _include;
public:
  explicit Includeble() : _included(false) {}

  Self &operator <<(const Include &i) {
    this->_include = i.getInclude();
    this->_included = true;
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

