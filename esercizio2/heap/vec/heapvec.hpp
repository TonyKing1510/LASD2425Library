
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : virtual public Heap<Data>,
                public Vector<Data> {
  // Must extend Heap<Data>,
  // Could extend SortableVector<Data>

private:

  // ...

protected:

  using Container::size;
  using Vector<Data>::elem;
  
  
  // ...

public:

  // Default constructor
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  HeapVec(const TraversableContainer<Data> &); // A heap obtained from a TraversableContainer
  HeapVec(MappableContainer<Data>&&); // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
   HeapVec(const HeapVec<Data>&);

  // Move constructor
  HeapVec(HeapVec<Data>&&);

  /* ************************************************************************ */

  // Destructor
  ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  HeapVec<Data>& operator=(const HeapVec<Data>&);

  // Move assignment
  HeapVec<Data>& operator=(HeapVec<Data>&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HeapVec<Data>&) const noexcept;
  bool operator!=(const HeapVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  bool IsHeap() const noexcept override;

  void Heapify() override;

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort(); 

  const Data& operator[](ulong i) const override; // Access to the vector elements (non-mutable version)
  void Clear() noexcept override; // Clear the vector (inherited from ClearableContainer)

protected:
  ulong LeftChild(ulong) const noexcept; // returns the index of the left child (2i+1)
  ulong RightChild(ulong) const noexcept; // returns the index of the right child (2i+2)
  ulong Parent(ulong) const noexcept; // returns the index of the parent (i-1)/2
  void Heapify(ulong) noexcept; // heapify the vector starting from the given index
  Data& operator[](ulong i) override; // Access to the vector elements (mutable version)

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
