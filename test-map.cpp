#include <assert.h>

#include "list.h"
#include "map.h"
#include "object.h"
#include "string.h"

// empty constructor
void test_empty_cons() {
  Map* map = new Map();
  assert(map);
  assert(map->size() == 0);
  delete map;
}

// clone
void test_clone() {
  Object* a1 = new String("a");
  Object* a2 = new String("a");
  Object* b1 = new String("b");
  Object* b2 = new String("b");
  Object* c1 = new String("c");
  Object* c2 = new String("c");
  Object* d1 = new String("d");
  Object* d2 = new String("d");

  Map map1;
  map1.put(a1, b1);
  map1.put(c1, d1);

  Map* map2 = map1.clone();
  List* keys1 = map1.keys();
  List* keys2 = map2->keys();
  List* vals1 = map1.values();
  List* vals2 = map2->values();

  assert(keys1->size() == keys2->size());
  assert(keys1->size() == vals1->size());
  assert(vals1->size() == vals2->size());

  for (size_t i = 0; i < keys1->size(); i++) {
    assert(keys1->get(i) == keys2->get(i));
    assert(vals1->get(i) == vals2->get(i));
  }

  assert(map1.equals(map2));

  map2->put(c2, a2);  // replace c1
  assert(!map1.equals(map2));

  delete a1;
  delete a2;
  delete b1;
  delete b2;
  delete c1;
  delete c2;
  delete d1;
  delete d2;
  delete map2;
  delete keys1;
  delete keys2;
  delete vals1;
  delete vals2;
}

// equals
void test_equals() {
  Object* a1 = new String("a");
  Object* a2 = new String("a");
  Object* b1 = new String("b");
  Object* b2 = new String("b");
  Object* c1 = new String("c");
  Object* c2 = new String("c");
  Object* d1 = new String("d");
  Object* d2 = new String("d");

  Map map1;
  Map map2;

  map1.put(a1, b1);
  assert(!map1.equals(&map2));

  map2.put(a1, b1);
  assert(map1.equals(&map2));

  map2.put(a2, b2);
  assert(map1.equals(&map2));

  map1.put(c1, d1);
  map2.put(c2, d2);
  assert(map2.equals(&map1));

  delete a1;
  delete a2;
  delete b1;
  delete b2;
  delete c1;
  delete c2;
  delete d1;
  delete d2;
}

// hash
void test_hash() {
  Object* a1 = new String("a");
  Object* a2 = new String("a");
  Object* b1 = new String("b");
  Object* b2 = new String("b");
  Object* c1 = new String("c");
  Object* c2 = new String("c");
  Object* d1 = new String("d");
  Object* d2 = new String("d");

  Map map1;
  Map map2;

  map1.put(a1, b1);
  assert(!map1.equals(&map2));

  map2.put(a1, b1);
  assert(map1.equals(&map2));
  assert(map1.hash() == map2.hash());

  map2.put(a2, b2);
  assert(map1.equals(&map2));
  assert(map1.hash() == map2.hash());

  map1.put(c1, d1);
  map2.put(c2, d2);
  assert(map2.equals(&map1));
  assert(map1.hash() == map2.hash());

  delete a1;
  delete a2;
  delete b1;
  delete b2;
  delete c1;
  delete c2;
  delete d1;
  delete d2;
}

// containsKey
void test_containsKey() {
  Object* a1 = new String("a");
  Object* a2 = new String("a");
  Object* b = new String("b");

  Map map;
  assert(!map.containsKey(nullptr));
  assert(!map.containsKey(a1));

  map.put(a1, b);
  assert(map.containsKey(a1));
  assert(map.containsKey(a2));

  delete a1;
  delete a2;
}

// containsValue
void test_containsValue() {
  Object* a1 = new String("a");
  Object* a2 = new String("a");
  Object* b = new String("b");

  Map map;
  assert(!map.containsValue(nullptr));
  assert(!map.containsValue(a1));

  map.put(b, a1);
  assert(map.containsValue(a1));
  assert(map.containsValue(a2));

  delete a1;
  delete a2;
}

// put and get
void test_put_get() {
  Object* s1 = new String("a");
  Object* s2 = new String("b");
  Object* s3 = new String("c");
  Object* s4 = new String("d");

  Map map;
  assert(map.put(s1, s2) == nullptr);
  assert(map.size() == 1);
  assert(map.put(s2, s3) == nullptr);
  assert(map.size() == 2);
  assert(map.put(s4, s3) == nullptr);
  assert(map.size() == 3);
  assert(map.get(s4)->equals(s3));

  Object* s5 = new String("d");  // == s4
  assert(map.put(s5, s1)->equals(s3));
  assert(map.size() == 3);

  assert(map.get(s1) == s2);
  assert(map.get(s1)->equals(s2));

  assert(map.get(s2) == s3);
  assert(map.get(s2)->equals(s3));

  assert(map.get(s4) == s1);
  assert(map.get(s4)->equals(s1));

  delete s1;
  delete s2;
  delete s3;
  delete s4;
  delete s5;
}

// isEmpty
void test_isEmpty() {
  Object* a = new String("a");
  Object* b = new String("b");

  Map map;

  assert(map.isEmpty());

  map.put(a, b);

  assert(!map.isEmpty());

  map.remove(a);

  assert(map.isEmpty());
}

// putAll
void test_putAll() {
  Object* a1 = new String("a");
  Object* a2 = new String("a");
  Object* b1 = new String("b");
  Object* b2 = new String("b");
  Object* c1 = new String("c");
  Object* e2 = new String("e");
  Object* d1 = new String("d");
  Object* f2 = new String("f");

  Map map1;
  Map map2;

  map1.put(a1, b1);
  map1.put(c1, d1);
  map2.put(a1, b2);
  map2.put(e2, f2);

  map1.putAll(&map2);

  assert(map2.size() == 2);
  assert(map1.size() == 3);  // one overlap, one new

  assert(map1.get(a1)->equals(b2));
  assert(map1.get(c1)->equals(d1));
  assert(map1.get(e2)->equals(f2));

  delete a1;
  delete a2;
  delete b1;
  delete b2;
  delete c1;
  delete e2;
  delete d1;
  delete f2;
}

// remove
void test_remove() {
  Object* s1 = new String("a");
  Object* s2 = new String("b");
  Object* s3 = new String("c");
  Object* s4 = new String("d");
  Object* s5 = new String("d");  // == s4

  Map map;
  assert(map.put(s1, s2) == nullptr);
  assert(map.put(s2, s3) == nullptr);
  assert(map.put(s4, s3) == nullptr);
  assert(map.size() == 3);

  assert(map.remove(s1) == s2);
  assert(map.size() == 2);
  assert(map.remove(s2) == s3);
  assert(map.size() == 1);
  assert(map.remove(s5) == s3);
  assert(map.isEmpty());
  assert(!map.containsKey(s4));

  delete s1;
  delete s2;
  delete s3;
  delete s4;
  delete s5;
}

// size
void test_size() {
  Object* a1 = new String("a");
  Object* b1 = new String("b");
  Object* c1 = new String("c");
  Object* d1 = new String("d");

  Map map1;

  assert(map1.size() == 0);
  map1.put(a1, b1);
  assert(map1.size() == 1);
  map1.put(c1, d1);
  assert(map1.size() == 2);
  map1.put(c1, a1);
  assert(map1.size() == 2);

  map1.remove(a1);
  assert(map1.size() == 1);
  map1.remove(c1);
  assert(map1.size() == 0);

  delete a1;
  delete b1;
  delete c1;
  delete d1;
}

// clear
void test_clear() {
  Object* a1 = new String("a");
  Object* b1 = new String("b");
  Object* c1 = new String("c");
  Object* d1 = new String("d");

  Map map1;

  map1.put(a1, b1);
  map1.put(c1, d1);
  map1.put(d1, a1);

  assert(map1.size() == 3);
  assert(!map1.isEmpty());

  map1.clear();

  assert(map1.size() == 0);
  assert(map1.isEmpty());

  delete a1;
  delete b1;
  delete c1;
  delete d1;
}

// keys and values
void test_keys_and_values() {
  Object* a1 = new String("a");
  Object* b1 = new String("b");
  Object* c1 = new String("c");
  Object* d1 = new String("d");

  Map map1;

  map1.put(a1, b1);
  map1.put(c1, d1);
  map1.put(d1, a1);

  assert(map1.size() == 3);

  List* keys = map1.keys();
  List* values = map1.values();

  assert(keys->size() == 3);
  assert(values->size() == 3);

  assert((keys->index_of(a1) < keys->size()));
  assert(!(keys->index_of(b1) < keys->size()));
  assert((keys->index_of(c1) < keys->size()));
  assert((keys->index_of(d1) < keys->size()));

  assert((values->index_of(a1) < values->size()));
  assert((values->index_of(b1) < values->size()));
  assert(!(values->index_of(c1) < values->size()));
  assert((values->index_of(d1) < values->size()));

  delete a1;
  delete b1;
  delete c1;
  delete d1;
  delete keys;
  delete values;
}

int main() {
  test_empty_cons();
  test_clone();
  test_equals();
  test_hash();
  test_containsKey();
  test_containsValue();
  test_put_get();
  test_isEmpty();
  test_putAll();
  test_remove();
  test_size();
  test_clear();
  test_keys_and_values();

  return 0;
}
