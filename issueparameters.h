// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef ISSUEPARAMETERS_H
#define ISSUEPARAMETERS_H

#include "parameter.h"

#define SIMPLE_ID_FILTER(name) \
  class name : public Filter { \
  public: \
    name(unsigned int id) : Filter("project_id", QString::number(id)) {} \
  };

namespace iss {

  SIMPLE_ID_FILTER(ProjectID)
  SIMPLE_ID_FILTER(TrackerID)

  class SubprojectID : public Filter {
  public:
    SubprojectID() : Filter("subproject_id", "!*") {}
    SubprojectID(unsigned int id): Filter("subproject_id", QString::number(id)){}
  };

  class AssignedTo : public Filter {
  public:
    AssignedTo(): Filter("assigned_to_id", "me") {}
    AssignedTo(unsigned int id): Filter("assigned_to_id", QString::number(id)) {}
  };
  class Status : public Filter {
  public:
    enum Type {
      open,
      closed
    };
    Status() : Filter("status_id", "*") {}
    Status(Type t) : Filter("status_id", fromType(t)) {}
  private:
    const char *fromType(Type t) {
      switch(t) {
        case open: return "open";
        case closed: return "closed";
      }
      return 0;
    }
  };

  class Journals : public Include {
  public:
    explicit Journals(): Include("journals"){}
  };


}  // namespace iss

#endif // ISSUEPARAMETERS_H
