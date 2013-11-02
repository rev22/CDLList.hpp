#include "../CDLList.hpp"
#include <assert.h>

// Count how many elements a circular list has:
int length(CDLList &l) {
    CDLList *x = &l;
    int c = 0;
    do { c++; x = &(x->next()); } while (x != &l);
    return c;
}

int main() {
  {
    // Create a single-node list:
    CDLList a;
    assert(length(a) == 1);
  }

  {
    // Create a two-nodes list:
    CDLList a;
    CDLList b(a);
    assert(length(a) == 2);
    assert(length(b) == 2);
  }

  {
    // Create a three-nodes circular list:
    CDLList a;
    CDLList b(a);
    CDLList c(b);
    assert(length(a) == 3);
    assert(length(b) == 3);
    assert(length(c) == 3);
  }

  {
    // The destructor of a node detaches it from any list it belongs to:

    CDLList foo;
    
    //  foo is on a list by itself
    assert(foo.lone());
    {
      CDLList bar(foo);
      // Now both foo and bar are in the same list
      assert(length(foo) == 2);
      assert(length(bar) == 2);
      assert(foo.pair());
      assert(bar.pair());
    }

    // bar's destructor was called and foo now is alone again
    assert(foo.lone());
    assert(length(foo) == 1);
  }
  
}
