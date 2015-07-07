// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef TYPING
#define TYPING

#include <QString>
#include <QByteArray>
#include <QtXml/QDomDocument>

#include "network.h"
#include "including.h"

class Post {
  QDomDocument _content;
public:
  QByteArray getContent() const {
    return _content.toByteArray();
  }
  void setContent(const QDomDocument &doc) {
    _content = doc;
  }
};

class Get {
public:
  QByteArray getContent() const {
    return QByteArray();
  }
};

template <Network::RequestType t, class Self>
class Typing {
};
template<class Self>
class Typing<Network::GET, Self> :
    public Get,
    public Includeble<Self>{
public:
  static const Network::RequestType type = Network::GET;
};
template<class Self>
class Typing<Network::POST, Self> : public Post {
public:
  static const Network::RequestType type = Network::POST;
};

template <class Self>
class Typing<Network::PUT, Self> : public Post {
public:
  static const Network::RequestType type = Network::PUT;
};

template <class Self>
class Typing<Network::DELETE, Self> : public Get {
public:
  static const Network::RequestType type = Network::DELETE;
};

#endif // TYPING

