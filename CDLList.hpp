// Copyright (c) 2013 Michele Bini

// This program is free software: you can redistribute it and/or modify
// it under the terms of the version 3 of the GNU General Public License
// as published by the Free Software Foundation.

// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

class CDLList {
private:
  template <typename X> static void swap_pointers(X*&a, X*&b) { X*c = a; a = b; b = c; }
  template <typename X> inline static X* unconst(const X *x) { return const_cast<X*>(x); };
protected:
  CDLList* _prev;
  CDLList* _next;
public:
  inline CDLList() :_prev(unconst(this)), _next(unconst(this)) {};

  inline CDLList(CDLList &u) :_prev(&u), _next(u._next) {
    u._next = this;
    _next->_prev = this;
  };

  inline ~CDLList() {
      _prev->_next = _next;
      _next->_prev = _prev;
  };

  inline CDLList& next() { return *_next; };
  inline CDLList& prev() { return *_prev; };
  
  // Remove element from currently existing list
  inline void cull() {
  	_prev->_next = _next;
	  _next->_prev = _prev;
	  _next = _prev = this;
  }

  // Switch element over to a new list
  inline void pass(CDLList& u) {
      _prev->_next = _next;
      _next->_prev = _prev;
      CDLList& v = *(u._next);
      _next = &v;
      _prev = &u;
      v._prev = this;
      u._next = this;
  };

  // Join element with a new list, possibly joining two lists
  inline void join(CDLList& p) {
    if (this == &p) return;
    CDLList& q = *(p._next);
    CDLList& u = *(_next);
    if ((&q == this) || (&u == &p)) return;
    swap_pointers(p._next, _next);
    swap_pointers(q._prev, u._prev);
  };

  inline void swap(CDLList& p) {
    if (this == &p) return;
    CDLList& q = *(p._next);
    CDLList& u = *(_next);
    CDLList& o = *(p._prev);
    CDLList& s = *(_prev);
    if ((&q == this) || (&u == &p)) return;
    swap_pointers(p._next, _next);
    swap_pointers(q._prev, u._prev);
    swap_pointers(p._prev, _prev);
    swap_pointers(o._next, s._next);
  };
};


