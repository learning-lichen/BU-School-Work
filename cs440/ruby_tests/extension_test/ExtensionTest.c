#include "ruby.h"

VALUE ExtensionTest = Qnil;

void Init_extension_test();

VALUE method_test(VALUE self);

void Init_extension_test() {
  ExtensionTest = rb_define_module()
}
