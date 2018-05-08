////////////////////////////////////////////////////////////////////////////////
//
// Advantages of empty class
// In a nutshell, for template (meta-)programming
//
// from https://stackoverflow.com/questions/4035180/advantages-of-an-empty-class-in-c
//
////////////////////////////////////////////////////////////////////////////////

class forward_iterator_tag {};
class random_access_iterator_tag {};

class MySimpleForwardIterator {
public:
  typedef typename forward_iterator_tag tag;
};

class MySimpleRandomIterator {
public:
  typedef typename random_access_iterator_tag tag;
};

template <class iterator, class tag>
void myfunc_int(iterator it, tag t) {

}

template <class iterator>
void myfunc_int<iterator, forward_iterator_tag>(iterator it) {

}

template <class iterator>
void myfunc_int<iterator, random_access_iterator_tag>(iterator it) {

}

template <class iterator>
void myfunc_int(iterator it) {
  // call arbitary iterator, and let the compiler choose the correct
  // implementation depending on the iterator type.
  myfunc_int<iterator, typename iterator::tag>(it);
}
