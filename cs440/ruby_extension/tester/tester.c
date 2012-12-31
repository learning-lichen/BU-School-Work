#include <ruby.h>
#include <string>

#include "test_object.hpp"

VALUE klass;

typedef struct _obj_container {
  TestObject* this_obj;
} MyObjectContainer;

void instance_free(void* p) {
  MyObjectContainer* obj = (MyObjectContainer*) p;
  delete obj->this_obj;
  free(p);
}

VALUE get_instance(VALUE self) {
  MyObjectContainer* new_obj = ALLOC(MyObjectContainer);
  new_obj->this_obj = new TestObject;

  VALUE tdata = Data_Wrap_Struct(klass, 0, instance_free, new_obj);
  rb_obj_call_init(tdata, 0, 0);
  return tdata;
}

VALUE invoke(VALUE self, VALUE method) {
  MyObjectContainer* obj;
  char* hi = StringValuePtr(method);

  Data_Get_Struct(self, MyObjectContainer, obj);

  obj->this_obj->call(hi);

  return Qnil;
}

extern "C" void Init_tester() {
  klass = rb_define_class("Tester", rb_cObject);
  rb_define_singleton_method(klass, "new", RUBY_METHOD_FUNC(get_instance), 0);
  rb_define_method(klass, "invoke", RUBY_METHOD_FUNC(invoke), 1);
}
