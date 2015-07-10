// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef TYPING
#define TYPING

#include <QString>
#include <QByteArray>
#include <QtXml/QDomDocument>

#include "network.h"
#include "including.h"
#include "pathing.h"

class Content {
  QDomDocument _content;
public:
  QByteArray getContent() const {
    return _content.toByteArray();
  }
  void setContent(const QDomDocument &doc) {
    _content = doc;
  }
};

class NoContent {
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
    public Path,
    public NoContent,
    public Includeble<Self> {
public:
  static const Network::RequestType type = Network::GET;
  explicit Typing(const QString &path): Path(path) {}
  explicit Typing(const QString &path, unsigned int id): Path(path, id) {}
  void setPath(QUrl &url) const {
    Path::setPath(url);
    Includeble<Self>::setQuery(url);
  }
};

template<class Self>
class Typing<Network::POST, Self> :
    public Path,
    public Content {
public:
  static const Network::RequestType type = Network::POST;
  explicit Typing(const QString &path): Path(path) {}
};

template <class Self>
class Typing<Network::PUT, Self> :
    public Path,
    public Content {
public:
  static const Network::RequestType type = Network::PUT;
  explicit Typing(const QString &path, unsigned int id): Path(path, id) {}
};

template <class Self>
class Typing<Network::DELETE, Self> :
    public Path,
    public NoContent {
public:
  static const Network::RequestType type = Network::DELETE;
  explicit Typing(const QString &path, unsigned int id): Path(path, id) {}
};

#define SIMPLE_GET_REQUEST(cl, path) \
  class cl: public Typing<Network::GET, cl> { \
    public: \
    cl(): Typing(QString::fromLatin1(path)){} \
  };

#define STANDARD_TYPES_REQUESTS(cl, path) \
  template <Network::RequestType type> \
  class cl : public Typing<type, cl<type> > { \
  public: \
    explicit cl(): Typing<type, cl<type> >(QString::fromLatin1(path)) {} \
    template <typename Arg> \
    explicit cl(Arg arg): Typing<type, cl<type> >(QString::fromLatin1(path), arg) {} \
  };

#endif // TYPING

