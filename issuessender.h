// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef ISSUESSENDER_H
#define ISSUESSENDER_H

#include <QObject>
#include "issue.h"
#include "sender.h"
#include "issueparameters.h"

class IssuesSender : public Sender
{
  Q_OBJECT
public:
  explicit IssuesSender(const QUrl &url, Network &net);
  void process(const QDomDocument &doc);

signals:
  void ready(Answer<Issue>);
};

#endif // USSUESSENDER_H
