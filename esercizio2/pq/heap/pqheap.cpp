
namespace lasd {

/* ************************************************************************** */

// Constructors
template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& container) : HeapVec<Data>(container) {};

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data>&& container) : HeapVec<Data>(std::move(container)) {};

template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& other) : HeapVec<Data>(other) {};

template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data>&& other) : HeapVec<Data>(std::move(other)) {};

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) {
  HeapVec<Data>::operator=(other);
  return *this;
}
template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) {
  if (this != &other) {
    HeapVec<Data>::operator=(std::move(other));
  }
  return *this;
}

template <typename Data>
Data PQHeap<Data>::Tip() const {
  if (this->size == 0) {
    throw std::length_error("Heap is empty");
  }
  return (*this)[0];
}

template <typename Data>
void PQHeap<Data>::RemoveTip() {
  if (this->size == 0) {
    throw std::length_error("Heap is empty");
  }
  (*this)[0] = std::move((*this)[this->size - 1]); // sposta l'ultimo in cima
  this->Resize(this->size - 1); // rimuovi l'ultimo logicamente
  this->Heapify(0); // ripristina heap
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
  if (this->size == 0) {
    throw std::length_error("Heap is empty");
  }
  Data tip = std::move((*this)[0]); // move per efficienza
  RemoveTip();
  return tip;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data& value) {
  this->Resize(this->size + 1);
  (*this)[this->size - 1] = value;
  UpHeap(this->size - 1);
}

template <typename Data>
void PQHeap<Data>::Insert(Data&& value) {
  this->Resize(this->size + 1);
  (*this)[this->size - 1] = std::move(value);
  UpHeap(this->size - 1);
}




template <typename Data>
void PQHeap<Data>::Change(ulong index, const Data& value) {
  if (index >= this->size) {
    throw std::out_of_range("Index out of range");
  }
  // Se il nuovo valore è maggiore, lo sposto in cima
  if (value > (*this)[index]) {
    (*this)[index] = value;
    UpHeap(index);  
  } else {
    // Altrimenti lo sposto in fondo
    (*this)[index] = value;
    this->Heapify(index);  
  }
};

template <typename Data>
void PQHeap<Data>::Change(ulong index, Data&& value) {
  if (index >= this->size) {
    throw std::out_of_range("Index out of range");
  }
  // Se il nuovo valore è maggiore, lo sposto in cima
  if (value > (*this)[index]) {
    (*this)[index] = std::move(value);
    UpHeap(index);
  } else {
    // Altrimenti lo sposto in fondo
    (*this)[index] = std::move(value);
    this->Heapify(index);
  }
};

template <typename Data>
void PQHeap<Data>::Clear() noexcept {
    HeapVec<Data>::Clear();
};

template <typename Data>
void PQHeap<Data>::UpHeap(ulong index) {
  while (index > 0 && (*this)[index] > (*this)[this->Parent(index)]) {
    std::swap((*this)[index], (*this)[this->Parent(index)]);
    index = this->Parent(index);
  }
}


}


