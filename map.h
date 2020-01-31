// lang::CwC
#pragma once

#include "list.h"
#include "object.h"

// Represents a mapping from Objects to Objects based on their hashcodes. Much
// of the interface comes from Java's HashMap.
class Map : public Object {
 public:
  // Construct an empty map
  Map();

  // Free memory for map
  ~Map();

  // Override. Make a shallow copy of the map (does not clone keys and values)
  virtual Map* clone();

  // Override. Compare to other object
  virtual bool equals(Object* other);

  // Override. Computer hash code for map
  virtual size_t hash();

  // Returns true if this map contains the given key
  bool containsKey(Object* key);

  // Returns true if this map contains the given value
  bool containsValue(Object* value);

  // Return the object to which the given key is mapped, or nullptr is one
  // does not exist
  Object* get(Object* key);

  // Return true if there are no keys in this map
  bool isEmpty();

  // Map the given key to the given value in this map. Returns the previous
  // value associated with that key, or nullptr if none.
  Object* put(Object* key, Object* value);

  // Copy all the mappings from the given map to this map
  void putAll(Map* map);

  // Removes the given key's mapping from this map. Returns the value
  // associated with the key, or nullptr if none
  Object* remove(Object* key);

  // Returns the number of key-value mappings in this map
  size_t size();

  // Clears all mappings
  void clear();

  // Returns a copy of the list of keys in this map
  List* keys();

  // Returns a copy of the list of values in this map
  List* values();
};
