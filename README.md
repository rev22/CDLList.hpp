CDLList.hpp
===========

Circular doubly-linked list, implemented as a header-only C++ library.

All operations are O(1) and composed of few instructions.

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

### access [next] or [prev]ious element

````C++
CDLList &a = b.next();
CDLList &c = b.prev();
````
Returns a reference to the next or previous element in the list.

### [cull] element from list

````C++
node.cull();
````
Removes [node] from any circular list it belongs to.

After this the node itself is in a 1-size list, the next and prev pointers both refer to itself.

### [pass] node to another list

````C++
node.pass(list);
````
Removes [node] from any circular list it belongs to, then add it to [list].


### [join] two lists

````C++
a.join(b);
````
Creates a single list by joining the lists a and b belong to.

### [swap] nodes belonging to different lists

````C++
a.swap(b);
````
Move a to the list b belongs to, and vice-versa.

### automatic removal

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
