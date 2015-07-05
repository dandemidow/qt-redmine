// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#include "issuessender.h"
#include <QFile>
#include "issueconverter.h"

IssuesSender::IssuesSender(const QUrl &url, Network &net) :
  Sender(QUrl(url.toString()+"/issues.xml"), net) {}

void IssuesSender::process(const QDomDocument &doc)
{
  Answer<Issue> issues = Convert<Issue>::exec(doc);
//  qDebug()<<"ans - "<<ans.ize();
//  QFile iss("issues.xml");
//  iss.open(QFile::WriteOnly);
//  iss.write(ans);
//  iss.close();
//  QList<Issue> issues = ans2Issue(ans);
  emit ready(issues);
}


