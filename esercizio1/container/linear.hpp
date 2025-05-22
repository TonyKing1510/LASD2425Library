
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer :
                         virtual public PreOrderTraversableContainer<Data>,
                         virtual public PostOrderTraversableContainer<Data> {
  // Must extend PreOrderTraversableContainer<Data>,
  //             PostOrderTraversableContainer<Data>

private:

  // ...

protected:

  using Container::size; // Number of elements in the container
  // (inherited from Container)


public:

  // Destructor
  virtual ~LinearContainer() = default; // Destructor of abstract types must be virtual

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator=(const LinearContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  LinearContainer& operator=(LinearContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer<Data>&) const noexcept; // Comparison of abstract types is possible.
  bool operator!=(const LinearContainer<Data>&) const noexcept; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& operator[](const ulong) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)

  inline virtual const Data& Front() const ; // (non-mutable version; concrete function must throw std::length_error when empty)

  inline virtual const Data& Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer : virtual public LinearContainer<Data>,
                               virtual public PreOrderMappableContainer<Data>,
                               virtual public PostOrderMappableContainer<Data> {
  // Must extend LinearContainer<Data>,
  //             PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>

private:

  // ...

protected:

  using Container::size; // Number of elements in the container

  using LinearContainer<Data>::operator[];
  using LinearContainer<Data>::Front;
  using LinearContainer<Data>::Back;

public:

  // Destructor
  virtual ~MutableLinearContainer() = default; // Destructor of abstract types must be virtual

  /* ************************************************************************ */

  // Copy assignment
  MutableLinearContainer& operator=(const MutableLinearContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableLinearContainer& operator=(MutableLinearContainer&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */
  // Specific member functions

  virtual Data& operator[](ulong) = 0 ;  // (mutable version; concrete function must throw std::out_of_range when out of range)

  inline virtual Data& Front() ; // (mutable version; concrete function must throw std::length_error when empty)

  inline virtual Data& Back() ; // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

};

template <typename Data>
class SortableLinearContainer : virtual public MutableLinearContainer<Data> {
  // Must extend MutableLinearContainer<Data>

private:

  // ...

protected:

  using Container::size; // Number of elements in the container
  using MutableLinearContainer<Data>::operator[]; // (inherited from MutableLinearContainer)

public:

  // Destructor
  virtual ~SortableLinearContainer() = default; // Destructor of abstract types must be virtual

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer& operator=(const SortableLinearContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  SortableLinearContainer& operator=(SortableLinearContainer&) = delete; // Move assignment of abstract types is not be possible.

  /* ************************************************************************ */

  // Specific member function

  void Sort() noexcept;
 
protected:
  void InsertionSort() noexcept;
  

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
