// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef REDMINE_GLOBAL_H_
#define REDMINE_GLOBAL_H_

#include <QtCore/qglobal.h>

#if defined(REDMINEQT_LIBRARY)
#  define REDMINEQTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define REDMINEQTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif  // REDMINE_GLOBAL_H_
