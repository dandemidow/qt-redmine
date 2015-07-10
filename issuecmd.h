// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef ISSUESSENDER_H
#define ISSUESSENDER_H

#include "typing.h"

STANDARD_TYPES_REQUESTS(IssueCmd, "issues")

SIMPLE_GET_REQUEST(Trackers, "trackers")
SIMPLE_GET_REQUEST(IssueStatuses, "issue_statuses")
SIMPLE_GET_REQUEST(IssuePriorities, "enumerations/issue_priorities")

#endif // USSUESSENDER_H
