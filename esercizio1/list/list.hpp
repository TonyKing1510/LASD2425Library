
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public MutableLinearContainer<Data>,
             virtual public ClearableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:

  using Container::size;

  struct Node {

    // Data
    Data Element;
    struct Node *ptrnext=nullptr;

    /* ********************************************************************** */

    // Specific constructors
     Node(const Data& dat) : Element(dat){};
     Node(Data&& dat) : Element(std::move(dat)){};

    /* ********************************************************************** */

    // Copy constructor
      Node(const Node& nod) : Element(nod.Element), ptrnext(nod.ptrnext){};

    // Move constructor
      Node( Node&&nod) : Element(std::move(nod.Element)), ptrnext(nod.ptrnext){};

    /* ********************************************************************** */

    // Destructor
   virtual ~Node()=default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const noexcept;
    inline bool operator!=(const Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    static Node *Clone(Node*);


  };

  Node *head=nullptr;
  Node *tail=nullptr;

public:

List()=default;

/* ************************************************************************ */

// Specific constructor
List(const TraversableContainer<Data>&); // A list obtained from a TraversableContainer
List(MappableContainer<Data>&&); // A list obtained from a MappableContainer

/* ************************************************************************ */

// Copy constructor
List(const List<Data>&);

// Move constructor
List(List<Data>&&) noexcept;

/* ************************************************************************ */

// Destructor
virtual ~List();

/* ************************************************************************ */

// Copy assignment
List<Data>& operator=(const List<Data>&) noexcept;

// Move assignment
List<Data>& operator=(List<Data>&&) noexcept;

/* ************************************************************************ */

// Comparison operators
bool operator==(const List<Data>&) const noexcept;
bool operator!=(const List<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&); // Copy of the value
  void InsertAtFront(Data&&); // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data&); // Copy of the value
  void InsertAtBack(Data&&); // Move of the value
  void RemoveFromBack(); // (must throw std::length_error when empty)
  Data BackNRemove(); // (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  Data& operator[](ulong) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

  Data& Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  Data& Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const ulong) const override;  // Override LinearContainer member (must throw std::out_of_range when out of range)

  const Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

  const Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

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

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!
  void PreOrderTraverse(TraverseFun, const Node *curr) const;
  void PostOrderTraverse(TraverseFun, const Node*curr) const;
  void PreOrderMap(MapFun, Node *curr) ;
  void PostOrderMap(MapFun,  Node *curr) ;

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
