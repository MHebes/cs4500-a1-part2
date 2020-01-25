// lang::CwC
#pragma once

#include <string.h>

#include "object.h"

// Represents a string of characters. Essentially a char vector
class String : public Object {
   public:
    char* str_;      // internal string; owned
    size_t length_;  // length of string

    // Make a new string based on str
    String(const char* str) {
        length_ = strlen(str);
        str_ = new char[length_ + 1];
        strcpy(str_, str);
    }

    // Make an empty string
    String() : Object() {
        str_ = new char[1];
        str_[0] = '\0';
    }

    // Free char array
    ~String() { delete[] str_; }

    void print() { printf("%s", str_); }

    String* clone() { return new String(str_); }

    bool equals(Object* other) {
        String* other_str = dynamic_cast<String*>(other);

        if (!other_str) {
            return false;  // not a string
        }

        return strcmp(other_str->str_, str_) == 0;
    }

    size_t hash() {
        return strlen(str_);  // lazy
    }

    int compare(String* other) {
        assert(other);
        return strcmp(str_, other->str_);
    }

    size_t length() { return length_; }

    String* concat(String* other) {
        char* buf = new char[length() + other->length() + 1];
        strcpy(buf, str_);
        strcat(buf, other->str_);
        String* newStr = new String(buf);
        delete[] buf;
        return newStr;
    }
};
