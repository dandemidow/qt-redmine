// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef PROJECTSSENDER_H
#define PROJECTSSENDER_H

#include <QObject>
#include "sender.h"
#include "project.h"

class ProjectsSender: public Sender {
  Q_OBJECT
public:
  ProjectsSender(const QUrl &url, Network &net);
  void process(const QDomDocument &doc);

signals:
  void ready(Answer<Project>);
};

#endif // PROJECTSSENDER_H
