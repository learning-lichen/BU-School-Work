#include <ruby.h>
#include <dlfcn.h>

#include "rubicable_base.hpp"

VALUE rubicable_class;

typedef struct _rubicable_container {
  RubicableBase* data;
} RubicableContainer;

void free_rubicable(void* p) {
  RubicableContainer* rc = (RubicableContainer*) p;
  delete rc->data;
  free(p);
}

VALUE new_rubicable(VALUE self, VALUE external_lib_name, VALUE external_init_name) {
  char* lib_name = StringValuePtr(external_lib_name);
  char* init_name = StringValuePtr(external_init_name);
  void* sdl_lib;
  RubicableBase* (*init_func)(void);
  RubicableContainer* container = ALLOC(RubicableContainer);
  VALUE struct_data;
  
  sdl_lib = dlopen(lib_name, RTLD_LOCAL | RTLD_LAZY);
  if (sdl_lib == 0) {
    return Qnil;
  }

  init_func = (RubicableBase* (*)(void)) dlsym(sdl_lib, init_name);

  if (init_func == 0) {
    return Qnil;
  }

  container->data = init_func();
  struct_data = Data_Wrap_Struct(rubicable_class, 0, free_rubicable, container);
  rb_obj_call_init(struct_data, 0, 0);

  free(lib_name);
  free(init_name);

  return struct_data;
}

VALUE invoke(int argc, VALUE* argv, VALUE optional) {
  printf("%d\n", argc);
}

extern "C" void Init_rubicable() {
  rubicable_class = rb_define_class("Rubicable", rb_cObject);
  rb_define_singleton_method(rubicable_class, "load", RUBY_METHOD_FUNC(new_rubicable), 1);
  rb_define_method(rubicable_class, "method_missing", RUBY_METHOD_FUNC(invoke), -1);
}
