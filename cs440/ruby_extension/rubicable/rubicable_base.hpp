#ifndef __RUBICABLE_BASE_H
#define __RUBICABLE_BASE_H

#include <ruby.h>

class RubicableBase {
public:
  virtual VALUE call(VALUE method_name);
  virtual ~RubicableBase();
};

#endif
