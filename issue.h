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

ADOPT_STRUCT(IssuePriority)
  PARSE_ELEMENT_SAME(id)
  PARSE_ELEMENT_SAME(name)
  PARSE_ELEMENT_SAME(is_default)
ADOPT_END

ADOPT_ANSWER(IssuePriority, issue_priorities, issue_priority)

struct IssueStatus {
  unsigned int id;
  QString name;
  bool is_default;
  bool is_closed;
};

ADOPT_STRUCT(IssueStatus)
  PARSE_ELEMENT_SAME(id)
  PARSE_ELEMENT_SAME(name)
  PARSE_ELEMENT_SAME(is_default)
  PARSE_ELEMENT_SAME(is_closed)
ADOPT_END

ADOPT_ANSWER(IssueStatus, issue_statuses, issue_status)

struct DetailType {
  QString property;
  QString name;
};

ADOPT_STRUCT_ATTRIBUTE(DetailType)
  PARSE_ATTRIBUTE_SAME(property)
  PARSE_ATTRIBUTE_SAME(name)
ADOPT_STRUCT_ATTRIBUTE_END

struct Detail {
  DetailType detail;
  QVariant old_value;
  QVariant new_value;
};

ADOPT_STRUCT(Detail)
  PARSE_ELEMENT_SAME(detail)
  PARSE_ELEMENT_SAME(old_value)
  PARSE_ELEMENT_SAME(new_value)
ADOPT_END

struct JournalType {
  unsigned int id;
};

ADOPT_STRUCT_ATTRIBUTE(JournalType)
  PARSE_ATTRIBUTE_SAME(id)
ADOPT_STRUCT_ATTRIBUTE_END

struct Journal {
  JournalType journal;
  IdType user;
  QString notes;
  QString created_on;
  QList<Detail> details;
};

ADOPT_STRUCT(Journal)
  PARSE_ELEMENT_SAME(journal)
  PARSE_ELEMENT_SAME(user)
  PARSE_ELEMENT_SAME(notes)
  PARSE_ELEMENT_SAME(created_on)
  PARSE_LIST(details, detail)
ADOPT_END

struct Issue {
  unsigned int id;
  IdType project;
  IdType tracker;
  IdType status;
  IdType priority;
  IdType author;
  IdType assigned_to;
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

ADOPT_STRUCT(Issue)
  PARSE_ELEMENT_SAME(id)
  PARSE_ELEMENT_SAME(project)
  PARSE_ELEMENT_SAME(tracker)
  PARSE_ELEMENT_SAME(status)
  PARSE_ELEMENT_SAME(priority)
  PARSE_ELEMENT_SAME(author)
  PARSE_ELEMENT_SAME(assigned_to)
  PARSE_ELEMENT_SAME(subject)
  PARSE_ELEMENT_SAME(description)
  PARSE_ELEMENT_SAME(start_date)
  PARSE_ELEMENT_SAME(due_date)
  PARSE_ELEMENT_SAME(done_ratio)
  PARSE_ELEMENT_SAME(estimated_hours)
  PARSE_ELEMENT_SAME(created_on)
  PARSE_ELEMENT_SAME(updated_on)
  PARSE_ELEMENT_SAME(closed_on)
  PARSE_LIST(journals, journal)
ADOPT_END

ADOPT_ANSWER(Issue, issues, issue)

struct IssuePost {
  opt<unsigned int> project_id;
  opt<unsigned int> tracker_id;
  opt<unsigned int> status_id;
  opt<unsigned int> priority_id;
  opt<QString> subject;
  opt<QString> description;
  opt<unsigned int> category_id;
  opt<unsigned int> fixed_version_id;
  opt<unsigned int> assigned_to_id;
  opt<unsigned int> parent_issue_id;
  //custom_fields;
  //watcher_user_ids;
  opt<bool> is_private;
  opt<unsigned int> estimated_hours;
  // for put
  opt<QString> notes;
  opt<bool> private_notes;
};

ADOPT_STRUCT(IssuePost)
  PARSE_ELEMENT_SAME(project_id);
  PARSE_ELEMENT_SAME(tracker_id)
  PARSE_ELEMENT_SAME(status_id)
  PARSE_ELEMENT_SAME(priority_id)
  PARSE_ELEMENT_SAME(subject)
  PARSE_ELEMENT_SAME(description)
  PARSE_ELEMENT_SAME(category_id)
  PARSE_ELEMENT_SAME(fixed_version_id)
  PARSE_ELEMENT_SAME(assigned_to_id)
  PARSE_ELEMENT_SAME(is_private)
  PARSE_ELEMENT_SAME(estimated_hours)
  PARSE_ELEMENT_SAME(notes)
  PARSE_ELEMENT_SAME(private_notes)
ADOPT_END
ADOPT_ANSWER(IssuePost, issues, issue)

#endif // ISSUE

