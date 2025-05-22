
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>,
                protected HeapVec<Data> {
  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

private:

  // ...

protected:

  using Container::size; // Number of elements in the container


  // ...

public:

  // Default constructor
  PQHeap() = default;

  /* ************************************************************************ */

  // Specific constructors
  PQHeap(const TraversableContainer<Data>& container); // A priority queue obtained from a TraversableContainer

  PQHeap(MappableContainer<Data>&& container); // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap<Data>&); // Copy constructor

  // Move constructor
  PQHeap(PQHeap<Data>&&); // Move constructor

  /* ************************************************************************ */

  // Destructor
  ~PQHeap() = default; // Destructor

  /* ************************************************************************ */

  // Copy assignment
  PQHeap<Data>& operator=(const PQHeap<Data>&); // Copy assignment

  // Move assignment
  PQHeap<Data>& operator=(PQHeap<Data>&&); // Move assignment is not possible

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  Data Tip() const override; // Override PQ member (must throw std::length_error when empty)
  void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)
  Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)

  void Insert(const Data&) override; // Override PQ member (Copy of the value)
  void Insert(Data&&) override; // Override PQ member (Move of the value)

  void Change(ulong, const Data&) override; // Override PQ member (Copy of the value)
  void Change(ulong, Data&&) override; // Override PQ member (Move of the value)

protected:

  // Auxiliary functions, if necessary!
  void Clear() noexcept override; // Override ClearableContainer member (clear the vector) 
  void UpHeap(ulong index); // Move the element at index up to restore the heap property

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
