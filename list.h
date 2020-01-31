// lang::CwC
#pragma once

#include "object.h"

/**
 * A list of strings. This is a basic container object for the purposes of
 * testing. NOTE: Ideally this would be made obselete by a more fully-featured
 * Array class. However, due to the nature of Assignment 2, I cannot do that
 * well. - Mike
 */
class List : public Object {
 public:
  // Initializes list
  List();

  // Frees list and objects within it
  ~List();

  // Returns length of list
  size_t size();

  // Return a copy of the Object at index i
  Object* get(size_t index);

  // Return index of given Object, or size() + 1 if it doesn't exist
  size_t index_of(Object* o);

  /* Additional interface: anything inherited from Object */
};
