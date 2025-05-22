
#ifndef SET_HPP
#define SET_HPP

/* ************************************************************************** */

#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Set : virtual public OrderedDictionaryContainer<Data>,
            virtual public LinearContainer<Data>,
            virtual public ClearableContainer {
  // Must extend OrderedDictionaryContainer<Data>,
  //             LinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  ~Set() = default;

  /* ************************************************************************ */

  // Copy assignment
  Set& operator=(const Set<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Set& operator=(Set<Data>&&) = delete; // Move assignment of abstract types is not possible.
  

};

/* ************************************************************************** */

}

#endif
