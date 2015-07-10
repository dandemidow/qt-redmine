// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef ISSUECONVERTER
#define ISSUECONVERTER

#include "converter.h"
#include "issue.h"

template <>
struct Convert<Issue> {
  static Answer<Issue> exec(const QDomDocument &doc) {
    Answer<Issue> _ans;
    cnv::getInfo(doc, QString::fromLatin1("issues"), _ans);
    START_PARSE_DOC(doc, issue, _ans)
      GET_ELEMENT(id)
      GET_IDTYPE_ELEMENT(project)
      GET_IDTYPE_ELEMENT(tracker)
      GET_IDTYPE_ELEMENT(status)
      GET_IDTYPE_ELEMENT(priority)
      GET_IDTYPE_ELEMENT(author)
      GET_ELEMENT(subject)
      GET_ELEMENT(description)
      GET_ELEMENT(start_date)
      GET_ELEMENT(due_date)
      GET_ELEMENT(done_ratio)
      GET_ELEMENT(estimated_hours)
      GET_ELEMENT(created_on)
      GET_ELEMENT(updated_on)
      GET_ELEMENT(closed_on)
        QDomNodeList journ_list = doc.elementsByTagName(QString::fromLatin1("journal"));
        for ( int j = 0; j<journ_list.size(); ++j ) {
          Journal jour;
          QDomNode jnode = journ_list.item(j);
          QDomElement jo = jnode.firstChildElement(QString::fromLatin1("notes"));
          jour.notes = jo.text();
          st.journals.append(jour);
        }

    STOP_PARSE_DOC
    return _ans;
  }
};

template <>
struct Convert<IssuePriority> {
  static Answer<IssuePriority> exec(const QDomDocument &doc) {
    Answer<IssuePriority> _ans;
    cnv::getInfo(doc, QString::fromLatin1("issue_priorities"), _ans);
    START_PARSE_DOC(doc, issue_priority, _ans)
      GET_ELEMENT(id)
      GET_ELEMENT(name)
      GET_ELEMENT(is_default)
    STOP_PARSE_DOC
    return _ans;
  }
};

template <>
struct Convert<IssueStatus> {
  static Answer<IssueStatus> exec(const QDomDocument &doc) {
    Answer<IssueStatus> _ans;
    cnv::getInfo(doc, QString::fromLatin1("issue_statuses"), _ans);
    START_PARSE_DOC(doc, issue_status, _ans)
        GET_ELEMENT(id)
        GET_ELEMENT(name)
        GET_ELEMENT(is_default)
        GET_ELEMENT(is_closed)
        STOP_PARSE_DOC
        return _ans;
  }
};


#endif // ISSUECONVERTER

