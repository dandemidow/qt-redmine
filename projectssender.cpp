// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#include "projectssender.h"

#include <QtXml>
#include <QDomDocument>

#include "projectconverter.h"
#include "projectparameters.h"

ProjectsSender::ProjectsSender(const QUrl &url, Network &net) :
  Sender(url, net) { (*this)<<prj::All(); }

void ProjectsSender::process(const QDomDocument &doc)
{
  Answer<Project> projects = Convert<Project>::exec(doc);
//  QFile iss("projects.xml");
//  iss.open(QFile::WriteOnly);
//  iss.write(arr);
//  iss.close();
//  QList<Project> projects = ans2Project(arr);
  emit ready(projects);
}
