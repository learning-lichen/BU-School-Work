#include <iostream>
#include <string>

#include "test_object.hpp"

using namespace std;

void TestObject::call(string method) {
  cout << "The method method " << method << " was called." << endl;

  if (method == "print_this")
    print_this();
  else
    cout << "No method by that name found." << endl;
}

void TestObject::print_this() {
  cout << "Hello from a C++ object." << endl;
}
