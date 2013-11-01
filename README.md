CDLList.hpp
===========

Circular doubly-linked list, implemented as a header-only C++11 library.

All operations provided are constant-time and composed of few instructions.

Copyright © 2013 Michele Bini (see the file COPYING for licensing details)

Sample usage
------------

Create a single-node list:

````C++
CDLList a;
````

Create a two-nodes list:

````C++
CDLList a;
CDLList b(a);
````

Create a three-nodes circular list:

````C++
CDLList a;
CDLList b(a);
CDLList c(b);
````

Create a function returning the size of a list:

````C++
int length(CDLList &l) {
    CDLList *x = &l;
    int count = 0;
    do { count++; x = &(x->next()); } while (x != &l);
    return count;
}
````

Operations
----------

### Create a single-element node

````C++
CDLList a;
````

This constructor creates a single-element list.

Cost: ~2 instructions

### Create a node in a list

````C++
CDLList a(l);
````

This constructor creates node A and add it to list L

Cost: ~4 instructions

### [next] or [prev]ious element

````C++
CDLList &a = b.next();
CDLList &c = b.prev();
````
Returns a reference to the next or previous element in the list.

Cost: ~1 instruction

### [cull] element from list

````C++
node.cull();
````
Removes [node] from any circular list it belongs to.

After this the node itself is in a 1-size list, the next and prev pointers both refer to itself.

Cost: ~4 intructions

### [pass] node to another list

````C++
node.pass(list);
````
Removes [node] from any circular list it belongs to, then add it to [list].

Cost: ~7 instructions

### [join] two lists

````C++
a.join(b);
````
Creates a single list by joining the lists A and B belong to.

Cost: ~7 instructions

### [swap] nodes belonging to different lists

````C++
a.swap(b);
````
Move A to the list B belongs to, and vice-versa.

Cost: ~10 instructions

### Predicates

````C++

    (a == b)  // A and B are the same element. Cost: ~1 instruction.

    a.lone()  // A is a 1-element list.     Cost: ~1 instruction.
    a.bevy()  // A has 3 or more elements.  Cost: ~1 instruction.
    a.pair()  // A has 2 elements.          Cost: ~2 instructions.

````

### Automatic removal on object destruction

The destructor of a node detaches it from any list it belongs to:

````C++
CDLList foo;

//  foo is on a list by itself
{
  CDLList bar(foo);

  // Now both foo and bar are in the same list
  assert(length(foo) == 2);
  assert(length(bar) == 2);
}

// bar's destructor was called and foo now is alone again
assert(length(foo) == 1);
````

The cost of the destructor is approximately 2 instructions.
