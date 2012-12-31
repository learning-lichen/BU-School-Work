// FIX THIS MACRO, IT IS BUGGY.
#define offsetof(struct_type, field_name)			\
  (((struct_type *) 0) - &((struct_type *) 0)->field_name)

#include <cstring>

struct A {
  char c;
  struct A *next;
  struct A *prev;
};

struct B {
  int a[40];
  struct B *next;
  struct B *prev;
  double x;
};

struct C {
  struct C *next;
  struct C *prev;
  char c[21];
};

// This function must insert the given node before the node
// given by the 'at' position.
void insert_node(void *node, void *at, size_t offset_of_link_ptrs) {
  void* next_node = (void *) *(char**) ((char*) node + offset_of_link_ptrs);
  void* prev_node = (void *) *(char**) ((char*) node + offset_of_link_ptrs + sizeof(void*));

  void* at_prev = (void*) *(char**) ((char*) at + offset_of_link_ptrs + sizeof(void*));
  void* prev_next = (void*) *(char**) ((char*) at_prev + offset_of_link_ptrs);

  next_node = at;
  prev_node = at_prev;

  at_prev = next_node;
  prev_next = next_node;
}

int main() {
  // The code below must work as is.
  A *ap = new A;
  A *a_pos = new A;
  insert_node(ap, a_pos, offsetof(A, next));
  delete ap;
  delete a_pos;
}

