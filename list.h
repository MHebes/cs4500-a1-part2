// lang::CwC
#pragma once

#include <assert.h>
#include <stdint.h>

#include "object.h"

// A list of strings
class List : public Object {
public:
    // Initializes vector with size 1 initially to avoid first allocation
    List() {}

    // Frees vector and Objects within it
    ~List() {}

    // Override. Outputs elements of the list with ", " inserted between them
    void print() {}

    // Override. Checks if all elements of this list match all elements of a
    // given List
    bool equals(Object* o) { return false; }

    // Override.
    size_t hash() { return 0; }

    // Returns length of list
    size_t size() { return 0; }

    // Return a copy of the Object at index i
    Object* get(size_t index) { return nullptr; }

    // Return index of given Object, or size() + 1 if it doesn't exist
    size_t index_of(Object* o) { return 0; }

    // Adds an element to the end of the list
    virtual void push_back(Object* str) {}

    // Removes the element at index i and returns it. Shifts other elements
    // after i
    Object* remove(size_t i) { return nullptr; }

    // Replaces the element at index i with e
    Object* set(size_t i, Object* e) { return nullptr; }

    // Insert e at index i
    void add(size_t i, Object* e) {}

    // Add all elements from c into the list starting at index i. Existing
    // elements after i are shifted
    virtual void add_all(size_t i, List* c) {}

    // Empty the list
    void clear() {}
};

