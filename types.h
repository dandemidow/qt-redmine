// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef TYPES
#define TYPES

#include <QString>

struct IdType {
  unsigned int id;
  QString name;
};

struct ListType {
  unsigned int total_count;
  unsigned int offset;
  unsigned int limit;
  QString type;
};

template<typename T>
class opt {
  bool exist;
  T d;
public:
  explicit opt():exist(false) {}
  explicit opt(const T &v) : d(v) {}
  T &operator = (const T &v) { d = v; exist = true; return d; }
  operator bool() const { return exist; }
  operator T() const { return d; }
  T *operator -> () { exist = true; return &d; }

  template <typename S>
  friend S &operator << (S &s, const opt<T> &o) {
    s<<o.value;
    return s;
  }
};

template <typename T>
struct Answer {
  typedef T type;
  opt<ListType> info;
  QList<T> items;
};

#endif // TYPES

