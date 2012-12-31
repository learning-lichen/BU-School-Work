#include <iostream>

#include "test_object.hpp"

using namespace std;

VALUE TestObject::call(VALUE method_name) {
  char* method_name_cstr = StringValuePtr(method_name);

  cout << method_name_cstr << " was called on a TestObject." << endl;
}

TestObject::~TestObject() {
}
