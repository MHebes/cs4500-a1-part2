// lang::CwC
#pragma once

#include <assert.h>
#include <stdint.h>

#include "object.h"

// from https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
unsigned long upper_power_of_2(unsigned long x) {
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x + 1;
}

// A list of strings
class List : public Object {
   public:
    Object** vector;  // Vector of Object pointers. owned<owned>
    size_t size_;     // Size of vector
    size_t length_;   // Num elements (returned by size())

    // Initializes vector with size 1 initially to avoid first allocation
    List() : vector(new Object*[1]), size_(1), length_(0) {}

    // Frees vector and Objects within it
    ~List() {
        for (size_t i = 0; i < length_; i++) {
            delete vector[i];
        }

        delete[] vector;
    }

    // Override. Outputs elements of the list with ", " inserted between them
    void print() {
        for (size_t i = 0; i < length_; i++) {
            vector[i]->print();
            if (i < length_ - 1) printf(", ");
        }
    }

    // Override. Checks if all elements of this list match all elements of a
    // given List
    bool equals(Object* o) {
        if (!o) return false;
        if (this == o) return true;

        List* o_strlist = dynamic_cast<List*>(o);
        if (!o_strlist) return false;

        if (o_strlist->size() != length_) return false;

        for (size_t i = 0; i < length_; i++) {
            if (!o_strlist->get(i)->equals(vector[i])) return false;
        }

        return true;
    }

    // Override. Returns length of list
    size_t hash() { return length_; /* TODO lazy */ }

    // Returns length of list
    size_t size() { return length_; }

    // Return a copy of the Object at index i
    Object* get(size_t index) {
        assert(index < length_);
        return vector[index]->clone();
    }

    // Return index of given Object, or size() + 1 if it doesn't exist
    size_t index_of(Object* o) {
        for (size_t i = 0; i < length_; i++) {
            if (vector[i]->equals(o)) return i;
        }

        return size() + 1;
    }

    // Reallocates vector if necessary based on length - never decreases size
    void resize_(size_t length) {
        if (length > size_) {
            size_ = upper_power_of_2(length);

            Object** new_vector = new Object*[size_];

            for (size_t i = 0; i < length_; i++) {
                new_vector[i] = vector[i];
            }

            delete[] vector;  // delete Object**, not every Object*

            vector = new_vector;
        }

        length_ = length;
    }

    // Reallocates but allows a size to be specified instead of basing off of
    // length
    void realloc_(size_t new_size) {
        if (new_size <= size_) return;

        new_size = upper_power_of_2(size_);

        size_ = new_size;

        Object** new_vector = new Object*[size_];
        for (size_t i = 0; i < length_; i++) {
            new_vector[i] = vector[i];
        }
        delete[] vector;  // delete Object**, not Object* s
        vector = new_vector;
    }

    // Adds an element to the end of the list
    virtual void push_back(Object* str) {
        assert(str);

        resize_(length_ + 1);

        vector[length_ - 1] = str->clone();
    }

    // Removes the element at index i and returns it. Shifts other elements
    // after i
    Object* remove(size_t i) {
        assert(i < length_);

        Object* e = vector[i];

        // shift elements one to the left
        for (size_t j = i; j < length_ - 1; j++) {
            vector[j] = vector[j + 1];
        }

        resize_(length_ - 1);

        return e;  // no clone necessary bc we are transferring ownership
    }

    // Replaces the element at index i with e
    Object* set(size_t i, Object* e) {
        assert(e);

        Object* old = vector[i];
        vector[i] = e->clone();
        return old;  // move ptr to caller
    }

    // Insert e at index i
    void add(size_t i, Object* e) {
        assert(i <= length_);
        assert(e);

        resize_(length_ + 1);

        // shift everything after i to the right
        for (size_t j = length_ - 1; j > i; j--) {
            vector[j] = vector[j - 1];
        }

        // replace i
        vector[i] = e->clone();
    }

    // Add all elements from c into the list starting at index i. Existing
    // elements after i are shifted
    virtual void add_all(size_t i, List* c) {
        assert(i <= length_);
        assert(c);

        resize_(length_ + c->size());

        // shift everything to the right by c->size() elements
        for (size_t j = length_ - 1; j > i + c->size(); j--) {
            vector[j] = vector[j - c->size()];
        }

        // copy c into the new space
        for (size_t j = 0; j < c->size(); j++) {
            vector[i + j] = c->get(j)->clone();
        }
    }

    // Empty the list
    void clear() {
        for (size_t i = 0; i < length_; i++) {
            delete vector[i];
        }

        delete[] vector;
    }
};

// A sorted list of Objects
class SortedList : public List {
   public:
    // default constructor only

    // Inserts e before the first element which it comes before alphabetically
    void sorted_add(Object* e) {
        assert(e);

        for (size_t i = 0; i < size(); i++) {
            if (e->compare(get(i)) < 0) {
                add(i, e);
                return;
            }
        }

        List::push_back(e);  // add at end, it's the biggest
    }

    // Override. Overriding this because the spec doesn't offer any polymorphism
    // otherwise :)
    virtual void push_back(Object* e) { sorted_add(e); }

    // Ignores the index because the spec requires it :(
    virtual void add_all(size_t i, List* c) {
        assert(c);

        for (size_t j = 0; j < c->size(); j++) {
            sorted_add(c->get(j));
        }
    }
};
