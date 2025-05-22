
namespace lasd {

/* ************************************************************************** */

// Specific member functions of PreOrderMappableContainer

template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun fun) {
    this->PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member functions of PostOrderMappableContainer

template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun fun) {
    this->PostOrderMap(fun);
}

/* ************************************************************************** */

}
