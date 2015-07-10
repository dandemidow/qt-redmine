// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef ISSUE
#define ISSUE

#include <QString>
#include "types.h"

struct IssuePriority {
  unsigned int id;
  QString name;
  bool is_default;
};

struct IssueStatus {
  unsigned int id;
  QString name;
  bool is_default;
  bool is_closed;
};

struct Tracker {
  unsigned int id;
  QString name;
};

struct Journal {
  unsigned int id;
  IdType user;
  QString notes;
  QString created_on;
};

struct Issue {
  unsigned int id;
  IdType project;
  IdType tracker;
  IdType status;
  IdType priority;
  IdType author;
  QString subject;
  QString description;
  QString start_date;
  QString due_date;
  unsigned int done_ratio;
  QString estimated_hours;
  QString created_on;
  QString updated_on;
  QString closed_on;
  QList<Journal> journals;
};

#endif // ISSUE

