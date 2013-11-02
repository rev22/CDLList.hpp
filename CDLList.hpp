// CDLList.hpp - Circular Doubly-Linked Lists

// This is an header-only C++11 library

// Copyright (c) 2013 Michele Bini

// CDLList is free software: you can redistribute it and/or modify
// it under the terms of the version 3 of the GNU General Public License
// as published by the Free Software Foundation.

// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __CDLLIST_HPP__
#define __CDLLIST_HPP__

class CDLList {
protected:
  CDLList* _next;
  CDLList* _prev;

private:
  // Utility functions
  template <typename X> inline static void swap_pointers(X*&a, X*&b) { X*c = a; a = b; b = c; }
  template <typename X> inline static X* unconst(const X *x) { return const_cast<X*>(x); };

public:
  inline CDLList() :_next(unconst(this)), _prev(unconst(this)) {};

  inline CDLList(CDLList &u) :_next(u._next), _prev(&u) {
    u._next = this;
    _next->_prev = this;
  };

  // Disable default copy semantics
  inline CDLList(const CDLList &) = delete;
  inline CDLList& operator=(const CDLList &) = delete;
  
  inline ~CDLList() {
      _prev->_next = _next;
      _next->_prev = _prev;
  };

  // True iff this is a 1-element list
  inline bool lone() { return _prev == this; };

  // True iff this a list with three or more elements
  inline bool bevy() { return _prev != _next; };

  // True iff this list has two elements
  inline bool pair() { return (_prev != this) && (_prev == _next); };

  inline bool operator ==(CDLList &l) { return this == &l; }
  inline bool operator !=(CDLList &l) { return this != &l; }
  
  inline CDLList& next() { return *_next; };
  inline CDLList& prev() { return *_prev; };
  
  // Remove element from currently existing list
  inline void cull() {
    _prev->_next = _next;
    _next->_prev = _prev;
    _next = _prev = this;
  }

  // Crop a new circular list from 'this' to 'p' (not included)
  inline void join(CDLList& p) {
    swap_pointers(p._prev, _prev);
    p._prev->_next = &p;
    _prev->_next = this;    
  };

  // 'pass' element to another list
  inline void pass(CDLList& l) {
    CDLList& m = *(l._next);
    _prev->_next = _next;
    _next->_prev = _prev;
    _next = &m;
    _prev = &l;
    m._prev = this;
    l._next = this;
  };

  inline void swap(CDLList& p) {
    swap_pointers(p._next, _next);
    swap_pointers(p._prev, _prev);
    p._next->_prev = &p;
    p._prev->_next = &p;
    _next->_prev = this;
    _prev->_next = this;
  };
};

#endif
