namespace lasd {

/* ************************************************************************** */

// Constructors
template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& container) : HeapVec<Data>(container) {
  capacity = this->size;  // Set initial capacity equal to size
}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data>&& container) : HeapVec<Data>(std::move(container)) {
  capacity = this->size;  // Set initial capacity equal to size
}

template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& other) : HeapVec<Data>(other) {
  capacity = this->size;
}

template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data>&& other)  : HeapVec<Data>(std::move(other)) {
  capacity = this->size;
}

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) {
   HeapVec<Data>::operator=(other);
   capacity = this->size;
  return *this;
}

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) {
   if (this != &other) {
    HeapVec<Data>::operator=(std::move(other));
    capacity = this->size;  // Set capacity to the new size
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
  (*this)[0] = std::move((*this)[this->size - 1]);
  this->size--;

  if (this->size > 0) {
    this->Heapify(0);
  }
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
  if (this->size == 0) {
    throw std::length_error("Heap is empty");
  }
  Data tip = std::move((*this)[0]);
  RemoveTip();
  return tip;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data& value) {
  if (this->capacity == this->size) {
    this->Resize(this->size + 10);
    std::swap(this->size, this->capacity); 
  }

  // Aumentiamo la size
  this->size++;

  // Aggiungiamo in posizione size (che è valido ora)
  (*this)[this->size-1] = value;

  // UpHeap sul nuovo elemento
  UpHeap(this->size-1);
}



template <typename Data>
void PQHeap<Data>::Insert(Data&& value) {
  if (this->capacity == this->size) {
    this->Resize(this->size + 10);
    std::swap(this->size, this->capacity); // Ensure capacity is at least size
  }

  // Aumentiamo la size
  this->size++;

  // Aggiungiamo in posizione size (che è valido ora)
  (*this)[this->size-1] = std::move(value);

  // UpHeap sul nuovo elemento
  UpHeap(this->size-1);
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, const Data& value) {
  if (index >= this->size) {
    throw std::out_of_range("Index out of range");
  }
  if (value > (*this)[index]) {
    (*this)[index] = value;
    UpHeap(index);  
  } else {
    (*this)[index] = value;
    this->DownHeap(index); 
  }
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, Data&& value) {
  if (index >= this->size) {
    throw std::out_of_range("Index out of range");
  }
  if (value > (*this)[index]) {
    (*this)[index] = std::move(value);
    UpHeap(index);
  } else {
    (*this)[index] = std::move(value);
    this->DownHeap(index);
  }
}

template <typename Data>
void PQHeap<Data>::Clear() noexcept {
  HeapVec<Data>::Clear();
  capacity = 0; // Reset capacity
}

template <typename Data>
void PQHeap<Data>::UpHeap(ulong index) {
  while (index > 0 && (*this)[index] > (*this)[this->Parent(index)]) {
    std::swap((*this)[index], (*this)[this->Parent(index)]);
    index = this->Parent(index);
  }
}

  template <typename Data>
  void PQHeap<Data>::Resize(ulong newSize) {
    if(newSize < this->size) {
      throw std::length_error("New size must be greater than or equal to current size");
    }
    if(newSize == 0) {
      this->Clear(); // Clear the heap if new size is zero
    }
    HeapVec<Data>::Resize(newSize);
  }

} // namespace lasd
