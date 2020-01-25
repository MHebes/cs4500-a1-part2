Assignment 1, Part 2.
Michael Hebert and Vincent Zhao
Description of classes

# Map

We have designed a generic Map object in map.h. It maps from Objects to
Objects, meaning it can be used with any of Object's child classes (e.g.
String).

Map itself inherits from Object, and implements all the usual suspects (print,
clone, equals, and hash).

Most of the other methods are similar to Java's HashMap class. The keys and
values can be obtained with keys() and values() as List objects.

# List

List is a generic list type which can contain arbitrary Objects. It is
functionally the same as the StrLists developed in the warmups, but more
generic.

Internally, it uses a dynamically-resizing vector of Object* pointers.

# Object

Object is the root node for objects in our CwC paradigm. It contains stub
methods for common object actions, such as comparison and printing.

# String

String is a basic implementation of Object which acts as a container for a
char array, with some useful helper methods.
