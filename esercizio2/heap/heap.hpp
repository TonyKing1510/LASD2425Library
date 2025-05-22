
#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap : virtual public SortableLinearContainer<Data>,
             virtual public ClearableContainer {
  // Must extend SortableLinearContainer<Data>,
  //             ClearableContainer

private:

protected:

public:

  // Destructor
  ~Heap() =  default;

  /* ************************************************************************ */

  // Copy assignment
  Heap<Data> operator=(const Heap<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Heap<Data> operator=(Heap<Data>&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual bool IsHeap() const noexcept = 0; // type IsHeap(argument) specifiers;

  virtual void Heapify() = 0; 

};

/* ************************************************************************** */

}

#endif
