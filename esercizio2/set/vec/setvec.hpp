
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {
 
/* ************************************************************************** */

template <typename Data>
class SetVec : virtual public Set<Data>,
               virtual public ResizableContainer{
  // Must extend Set<Data>,
  //             ResizableContainer

private:

  // ...
/* ************************************************************************ */
protected:

  using Container::size; // elementi effettivi del vettore ( la usiamo per insert e altro)
  Vector<Data> elem; // Vector of elements
  ulong capacity = 4; // Capacity of the vector (la usiamo per resize e altro)
  ulong head = 0; // Head of the vector 
  ulong tail = 0; // Tail of the vector 

  // ...

public:

  // Default constructor
  SetVec() { 
    this->Resize(capacity); // Resize to initial capacity
  }

   

  // Specific constructors
   SetVec(const TraversableContainer<Data>&) noexcept; // A set obtained from a TraversableContainer
   SetVec(MappableContainer<Data>&&) noexcept; // A set obtained from a MappableContainer

  /*  ************************************************************************ */

  // Copy constructor
   SetVec(const SetVec<Data>&) noexcept;

  // Move constructor
   SetVec(SetVec<Data>&&) noexcept;

  /*  ************************************************************************ */

  // Destructor
  ~SetVec() = default;

  /*  ************************************************************************ */

  // Copy assignment
  SetVec<Data>& operator=(const SetVec<Data>&) noexcept;

  // Move assignment
  SetVec<Data>& operator=(SetVec<Data>&&) noexcept;

  /*  ************************************************************************ */

  // Comparison operators
  bool operator==(const SetVec<Data>&) const noexcept;
  bool operator!=(const SetVec<Data>&) const noexcept;

  /*  ************************************************************************ */

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

  /*  ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /*  ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /*  ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /*  ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /*  ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)
  void Resize(ulong) override; // Override ResizableContainer member (must throw std::length_error when new size is 0)


protected:

  ulong Index(ulong pos) const;  // converte posizione logica -> indice reale
  void Expand();                 // espande capacità se serve
  void ShiftRight(ulong pos);    // shifta a destra da pos in poi
  void ShiftLeft(ulong pos);     // shifta a sinistra da pos indietro
  long BinarySearch(const Data& val) const;
  



};
/* ************************************************************************** */

}

#include "setvec.cpp"

#endif
