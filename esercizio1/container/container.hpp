
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */
using uint = unsigned int;
using ulong = unsigned long;

namespace lasd {

/* ************************************************************************** */

class Container {

private:

  // ...

protected:

 ulong size = 0;// Number of elements in the container

  /* ************************************************************************ */

  // Default constructor
  Container() = default;

public:

  // Destructor
  virtual ~Container() = default; // Destructor of abstract types must be virtual

  /* ************************************************************************ */

  // Copy assignment
  Container& operator=(const Container&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Container& operator=(Container&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const Container&) const noexcept = delete; // Comparison of abstract types is not possible.


  /* ************************************************************************ */

  // Specific member functions

  virtual inline bool Empty() const {
    return (size == 0);
  }; // (concrete function should not throw exceptions)

  virtual inline ulong Size() const {
    return size;
  }; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

class ClearableContainer : virtual public Container {
  // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ClearableContainer() = default; // Destructor of abstract types must be virtual

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer& operator=(const ClearableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ClearableContainer& operator=(ClearableContainer&&) noexcept = default; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer&) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const ClearableContainer&) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Clear() = 0; 

};

/* ************************************************************************** */

class ResizableContainer : virtual public ClearableContainer {
  // Must extend ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ResizableContainer() = default; // Destructor of abstract types must be virtual

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer& operator=(const ResizableContainer&) = delete ; // Copy assignment of abstract types is not possible.

  // Move assignment
  ResizableContainer& operator=(ResizableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResizableContainer&) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const ResizableContainer&) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Resize(ulong new_size) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override {
    this->Resize(0); // Resize to 0
  }; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#endif
