
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public MutableLinearContainer<Data>,
               virtual public ResizableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  using Container::size;
  Data *elem = nullptr;
  using MutableLinearContainer<Data>::operator[];

  // ...

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
   Vector(const ulong initSize); // A vector with a given initial dimension
   Vector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
   Vector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector<Data> &);

  // Move constructor
  Vector(Vector<Data> && ) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector() noexcept;

  /* ************************************************************************ */

  // Copy assignment
  Vector<Data>& operator=(const Vector<Data> &);

  // Move assignment
  Vector<Data>& operator=(Vector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector<Data>&) const noexcept;
  bool operator!=(const Vector<Data>&) const noexcept; 

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  Data& operator[](ulong) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

  Data& Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  Data& Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  const Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

  const Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(const ulong) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : virtual public Vector<Data>,
                     virtual public SortableLinearContainer<Data> {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  using Container::size;
  using Vector<Data>::operator[];
  

  // ...

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  SortableVector(const ulong initSize); // A vector with a given initial dimension
  SortableVector(const TraversableContainer<Data>&);// A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data>&&) noexcept; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector<Data>&) noexcept;

  // Move constructor
  SortableVector(SortableVector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~SortableVector()=default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector<Data>& operator=(const SortableVector<Data> &) noexcept;

  // Move assignment
  SortableVector<Data>& operator=(SortableVector<Data> &&) noexcept;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
