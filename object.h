// lang::CwC
#pragma once

#include <assert.h>
#include <stdio.h>

class Object {
   public:
    Object() {}

    virtual ~Object(){};

    virtual bool equals(Object* other) { return other == this; }

    virtual size_t hash() { return reinterpret_cast<size_t>(this); }

    virtual void print() { printf("Object %lx", hash()); }

    virtual void println() {
        print();
        printf("\n");
    }

    virtual Object* clone() {
        assert(false);  // not cloneable directly
    }

    virtual int compare(Object* other) {
        assert(false);  // not comparable directly
    }
};
