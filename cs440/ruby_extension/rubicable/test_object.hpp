#ifndef __TEST_OBJECT_H
#define __TEST_OBJECT_H

#include "rubicable_base.hpp"

class TestObject : public RubicableBase {
public:
  VALUE call(VALUE method_name);
  ~TestObject();
};

#endif
