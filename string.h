// lang::CwC
#pragma once

#include <string.h>

#include "object.h"

// Represents a string of characters. Essentially a char vector
class String : public Object {
public:
    // Make a new string based on str
    String(const char* str) {}

    // Make an empty string
    String() : Object() {}

    // Free char array
    ~String() {}

    void print() {}

    String* clone() { return nullptr; }

    bool equals(Object* other) { return false; }

    size_t hash() { return 0; }

    int compare(String* other) { return 0; }

    size_t length() { return 0; }

    String* concat(String* other) { return nullptr; }
};
