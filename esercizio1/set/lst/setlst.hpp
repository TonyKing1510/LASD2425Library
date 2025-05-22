
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst : virtual public Set<Data>, virtual public List<Data> {
  // Must extend Set<Data>,
  //             List<Data>

private:

  // ...

protected:

  using Container::size; // Number of elements in the container
  using List<Data>::head;
  using List<Data>::tail;
  using List<Data>::operator[];
  

  // ...

public:

  // Default constructor
    SetLst() = default;

  /* ************************************************************************ */

  // Specific constructors
   SetLst(const TraversableContainer<Data>&  q); // A set obtained from a TraversableContainer
   SetLst(MappableContainer<Data>&& q); // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
   SetLst(const SetLst<Data>&q);

  // Move constructor
   SetLst(SetLst<Data>&&q) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~SetLst() = default; // Destructor of abstract types must be virtual  

  /* ************************************************************************ */

  // Copy assignment
  SetLst<Data>& operator=(const SetLst<Data>&) noexcept; 
  // Move assignment
  SetLst<Data>& operator=(SetLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetLst<Data>&) const noexcept; 
  bool operator!=(const SetLst<Data>&) const noexcept; 

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  const Data& Min() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  const Data& Max() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member


  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member




protected:


 typename lasd::List<Data>::Node* BinarySearch(const Data&, typename lasd::List<Data>::Node*&) const noexcept;


};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif
