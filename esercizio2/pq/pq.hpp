
#ifndef PQ_HPP
#define PQ_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQ : virtual public LinearContainer<Data>,
           public ClearableContainer {
  // Must extend LinearContainer<Data>,
  //             ClearableContainer

private:

protected:

public:

  // Destructor
  ~PQ()= default;

  /* ************************************************************************ */

  // Copy assignment
  PQ<Data> operator=(const PQ<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PQ<Data> operator=(PQ<Data>&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data Tip() const = 0; // (concrete function must throw std::length_error when empty)
  virtual void RemoveTip() = 0; // (concrete function must throw std::length_error when empty)
  virtual Data TipNRemove() = 0; // (concrete function must throw std::length_error when empty)

  virtual void Insert(const Data&) = 0; // Copy of the value
  virtual void Insert(Data&&) = 0; // Move of the value

  virtual void Change(ulong, const Data&) = 0; // Copy of the value
  virtual void Change(ulong, Data&&) = 0; // Move of the value

};

/* ************************************************************************** */

}

#endif
