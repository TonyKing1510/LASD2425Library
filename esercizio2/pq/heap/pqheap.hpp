
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
  ulong capacity = 0; // Capacity of the heap (not strictly necessary, but useful for efficiency)
  using HeapVec<Data>::operator[]; // Access to the elements of the heap
  using HeapVec<Data>::Front; 
  using HeapVec<Data>::Back; 

  // ...

public:

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

  void Clear() noexcept;

  inline const Data &operator[](ulong index) const override
    {
      return HeapVec<Data>::operator[](index);
    }
    using HeapVec<Data>::HeapVec; // Inherit constructors from HeapVec<Data>
  inline const Data &Front() const override
    {
      return HeapVec<Data>::Front(); // Access to the first element of the heap
    }
  inline const Data &Back() const override
    {
      return HeapVec<Data>::Back(); // Access to the last element of the heap
    }

  void Resize(ulong newSize) override; // Resize the heap (inherited from ResizableContainer)





protected:
  void UpHeap(ulong index); // Move the element at index up to restore the heap property
  inline void DownHeap(ulong index) noexcept {
    this->Heapify(index); // Use the inherited Heapify method to restore the heap property
  }

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
