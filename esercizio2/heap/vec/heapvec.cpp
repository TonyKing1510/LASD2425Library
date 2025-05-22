
namespace lasd {

/* ************************************************************************** */

// Constructors
template <typename Data>
lasd::HeapVec<Data>::HeapVec(const TraversableContainer<Data>& container) : Vector<Data>(container) {
  Heapify();  // Trasforma il vettore in un MaxHeap
}


template <typename Data>
lasd::HeapVec<Data>::HeapVec(MappableContainer<Data>&& container) : Vector<Data>(std::move(container)) {
  Heapify();  // Trasforma il vettore in un MaxHeap
}



template <typename Data>
lasd::HeapVec<Data>::HeapVec(const HeapVec<Data>& other) : Vector<Data>(other) {
}

/* ************************************************************************** */

template <typename Data>
lasd::HeapVec<Data>::HeapVec(HeapVec<Data>&& other)
  : Vector<Data>(std::move(other))  // Muovi il Vector base
{
}




template <typename Data>
lasd::HeapVec<Data>& lasd::HeapVec<Data>::operator=(const HeapVec<Data>& other) {
  Vector<Data>::operator=(other); // copia base
  return *this;
}

template <typename Data>
lasd::HeapVec<Data>& lasd::HeapVec<Data>::operator=(HeapVec<Data>&& other) {
  if (this != &other) {
    Vector<Data>::operator=(std::move(other)); // move base
  }
  return *this;
}


template <typename Data>
bool lasd::HeapVec<Data>::operator==(const HeapVec<Data>& other) const noexcept {
  if (this->size != other.size)
    return false;
  for (ulong i = 0; i < size; ++i) {
    if (this->elem[i] != other.elem[i])
      return false;
  }
  return true;
}

template <typename Data>
bool lasd::HeapVec<Data>::operator!=(const HeapVec<Data>& other) const noexcept {
  return !(*this == other);
}


template <typename Data>
bool lasd::HeapVec<Data>::IsHeap() const noexcept {
  for (ulong i = 0; i < this->size; ++i) {
    ulong left = LeftChild(i);
    ulong right = RightChild(i);

    if (left < this->size && elem[i] < elem[left])
      return false;
    if (right < this->size && elem[i] < elem[right])
      return false;
  }
  return true;
}

template <typename Data>
void lasd::HeapVec<Data>::Heapify() {
  if (size == 0) return;
  for (long i = (long)(this->size / 2) - 1; i >= 0; --i) {
    Heapify(i);
  }
}

//usata per la discesa del maxHeap
template <typename Data>
void lasd::HeapVec<Data>::Heapify(ulong i) noexcept {
  ulong largest = i;
  ulong left = LeftChild(i);
  ulong right = RightChild(i);

  if (left < this->size && elem[left] > elem[largest]) {
    largest = left;
  }
  if (right < this->size && elem[right] > elem[largest]) {
    largest = right;
  }

  if (largest != i) {
    std::swap(elem[i], elem[largest]);
    Heapify(largest);  // ricorsione sul figlio modificato
  }
}


template <typename Data>
ulong lasd::HeapVec<Data>::LeftChild(ulong i) const noexcept {
  return 2 * i + 1;
}
template <typename Data>
ulong lasd::HeapVec<Data>::RightChild(ulong i) const noexcept {
  return 2 * i + 2;
}
template <typename Data>
ulong lasd::HeapVec<Data>::Parent(ulong i) const noexcept {
  return (i - 1) / 2;
}
template <typename Data>
void lasd::HeapVec<Data>::Sort() {
  Heapify(); // Costruisce il maxHeap iniziale

  for (long i = size - 1; i > 0; --i) {
    std::swap(this->elem[0], this->elem[i]); // porta il max in fondo

    // Ricostruisce il maxHeap su [0, i-1]
    ulong index = 0;
    bool heapOk = false;

    while (!heapOk) {
      ulong largest = index;
      ulong left = LeftChild(index);
      ulong right = RightChild(index);

      if (left < static_cast<ulong>(i) && this->elem[left] > this->elem[largest])
        largest = left;
      if (right < static_cast<ulong>(i) && this->elem[right] > this->elem[largest])
        largest = right;

      if (largest != index) {
        std::swap(this->elem[index], this->elem[largest]);
        index = largest;
      } else {
        heapOk = true;
      }
    }
  }
}


template <typename Data>
const Data& lasd::HeapVec<Data>::operator[](ulong index) const {
  if (index >= this->size) {
    throw std::out_of_range("Index out of range");
  }
  return this->elem[index];
}

template <typename Data>
Data& lasd::HeapVec<Data>::operator[](ulong index) {
  if (index >= this->size) {
    throw std::out_of_range("Index out of range");
  }
  return this->elem[index];
}


template <typename Data>
void lasd::HeapVec<Data>::Clear() noexcept {
  Vector<Data>::Clear(); // libera memoria e resetta size
}





/* ************************************************************************** */

}
