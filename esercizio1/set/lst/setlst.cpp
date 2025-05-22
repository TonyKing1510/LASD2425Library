
namespace lasd {

/* ************************************************************************** */


template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data>& q) {
  q.Traverse([this](const Data& dat) {
    Insert(dat); 
  });
}


template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data>&& q) {
  q.Map([this](Data& dat) {
    Insert(std::move(dat)); 
  });
}

template <typename Data>
SetLst<Data>::SetLst(const SetLst<Data>& other) : List<Data>(other) {
  other.Traverse([this](const Data& dat) {
    Insert(dat); 
  });
}

template <typename Data>
SetLst<Data>::SetLst(SetLst<Data>&& other) noexcept
  : List<Data>(std::move(other)) {
  }




template <typename Data>
bool SetLst<Data>::Insert(const Data& d) {
  if (this->size == 0 || d < this->head->Element) {
    List<Data>::InsertAtFront(d);
    return true;
  }

 typename List<Data>::Node* pred = nullptr;
  typename List<Data>::Node* found = BinarySearch(d, pred);

  if (found != nullptr) return false; // già presente

  typename List<Data>::Node* newNode = new typename List<Data>::Node(d);

  if (pred == nullptr) {
    newNode->ptrnext = this->head;
    this->head = newNode;
  } else {
    newNode->ptrnext = pred->ptrnext;
    pred->ptrnext = newNode;
  }

  if (newNode->ptrnext == nullptr) {
    this->tail = newNode;
  }

  this->size++;
  return true;
}



template <typename Data>
bool SetLst<Data>::Insert(Data&& d) {
  if (this->size == 0 || d < this->head->Element) {
    List<Data>::InsertAtFront(d);
    return true;
  }
typename List<Data>::Node* pred = nullptr;
  typename List<Data>::Node* found = BinarySearch(d, pred);

  if (found != nullptr) return false; // già presente

  typename List<Data>::Node* newNode = new typename List<Data>::Node(std::move(d));

  if (pred == nullptr) {
    newNode->ptrnext = this->head;
    this->head = newNode;
  } else {
    newNode->ptrnext = pred->ptrnext;
    pred->ptrnext = newNode;
  }

  if (newNode->ptrnext == nullptr) {
    this->tail = newNode;
  }

  this->size++;
  return true;
}

template <typename Data>
bool SetLst<Data>::Remove(const Data& val) {
  typename List<Data>::Node* pred = nullptr;
  typename List<Data>::Node* curr = BinarySearch(val, pred);

  if (curr == nullptr) return false;

  if (pred == nullptr) {
    this->head = curr->ptrnext;
  } else {
    pred->ptrnext = curr->ptrnext;
  }

  if (curr == this->tail) {
    this->tail = pred;
  }

  delete curr;
  this->size--;
  return true;
}




template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& q) noexcept {
  if (this != &q) {
    List<Data>::operator=(q);
  }
  return *this;

}

template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& q) noexcept {
  if (this != &q) {
    List<Data>::operator=(std::move(q));
  }
  return *this;
}

template <typename Data>
bool SetLst<Data>::operator==(const SetLst<Data>& q) const noexcept {
  return List<Data>::operator==(q);
}
template <typename Data>
bool SetLst<Data>::operator!=(const SetLst<Data>& q) const noexcept {
  return List<Data>::operator!=(q);
}

template <typename Data>
const Data& SetLst<Data>::Min() {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }
  return List<Data>::Front();

}
template <typename Data>
Data SetLst<Data>::MinNRemove() {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }
  Data minElem = List<Data>::Front();
  this->lasd::List<Data>::RemoveFromFront();
  return minElem;

}

template <typename Data>
void SetLst<Data>::RemoveMin() {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }
  Min();
  this->lasd::List<Data>::RemoveFromFront();

}

template <typename Data>
const Data& SetLst<Data>::Max() {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }
  return List<Data>::Back();
}

template <typename Data>
Data SetLst<Data>::MaxNRemove() {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }
  Data maxElem = List<Data>::Back();
  this->lasd::List<Data>::RemoveFromBack();
  return maxElem;
}
template <typename Data>
void SetLst<Data>::RemoveMax() {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }
  Max();
  this->lasd::List<Data>::RemoveFromBack();
}

template <typename Data>
const Data& SetLst<Data>::Predecessor(const Data& d) {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }

  typename List<Data>::Node* pred = nullptr;
  this->BinarySearch(d, pred); // Anche se non trova il nodo, `pred` è aggiornato

  if (pred == nullptr) {
    throw std::length_error("No predecessor: no smaller element exists");
  }

  return pred->Element;
}



template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data& d) {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }

  typename List<Data>::Node* pred = nullptr;
  BinarySearch(d, pred); // Anche se d non esiste, pred sarà l’ultimo < d

  if (pred == nullptr) {
    throw std::length_error("No predecessor: no smaller element exists");
  }

  // Rimozione del nodo puntato da pred
  typename List<Data>::Node* toRemove = nullptr;

  // Serve per trovare il nodo *prima* del predecessore 
  if (pred == this->head) {
    this->head = pred->ptrnext;
  } else {
    // Scorro per trovare chi punta a pred
    toRemove = this->head;
    while (toRemove != nullptr && toRemove->ptrnext != pred) {
      toRemove = toRemove->ptrnext;
    }
    if (toRemove != nullptr) {
      toRemove->ptrnext = pred->ptrnext;
    }
  }

  if (pred == this->tail) {
    this->tail = toRemove; // tail ora punta al precedente
  }

  Data value = pred->Element;
  delete pred;
  --this->size;
  return value;
}

template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data& d) {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }

  typename List<Data>::Node* beforePred = nullptr;
  typename List<Data>::Node* pred = nullptr;
  typename List<Data>::Node* curr = this->head;

  // Scorro finché non trovo un nodo maggiore o uguale a d
  while (curr != nullptr && curr->Element < d) {
    beforePred = pred;
    pred = curr;
    curr = curr->ptrnext;
  }

  if (pred == nullptr) {
    throw std::length_error("No predecessor: no smaller element exists");
  }

  // Rimuovi pred
  if (beforePred == nullptr) {
    // pred è in testa
    this->head = pred->ptrnext;
  } else {
    beforePred->ptrnext = pred->ptrnext;
  }

  if (pred == this->tail) {
    this->tail = beforePred;
  }

  delete pred;
  --this->size;
}


template <typename Data>
const Data& SetLst<Data>::Successor(const Data& d) {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }

  typename List<Data>::Node* pred = nullptr;
  typename List<Data>::Node* found = BinarySearch(d, pred);

  typename List<Data>::Node* succ = nullptr;

  if (found != nullptr) {
    succ = found->ptrnext;
  } else {
    // Se d non esiste, succ è già curr in BinarySearch, che è il primo > d
    succ = (pred == nullptr) ? this->head : pred->ptrnext;
  }

  if (succ == nullptr) {
    throw std::length_error("No successor: element is the greatest or not found");
  }

  return succ->Element;
}

template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& d) {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }

  typename List<Data>::Node* pred = nullptr;
  typename List<Data>::Node* curr = this->head;

  while (curr != nullptr && curr->Element <= d) {
    pred = curr;
    curr = curr->ptrnext;
  }

  if (curr == nullptr) {
    throw std::length_error("No successor: element is the greatest or not found");
  }

  // Rimozione di curr (successore)
  if (pred == nullptr) {
    this->head = curr->ptrnext;
  } else {
    pred->ptrnext = curr->ptrnext;
  }

  if (curr == this->tail) {
    this->tail = pred;
  }

  Data value = curr->Element;
  delete curr;
  --this->size;
  return value;
}

template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data& d) {
  if (this->size == 0) {
    throw std::length_error("SetLst is empty");
  }

  typename List<Data>::Node* pred = nullptr;
  typename List<Data>::Node* curr = this->head;

  while (curr != nullptr && curr->Element <= d) {
    pred = curr;
    curr = curr->ptrnext;
  }

  if (curr == nullptr) {
    throw std::length_error("No successor: element is the greatest or not found");
  }

  // Rimuovi curr (successore)
  if (pred == nullptr) {
    this->head = curr->ptrnext;
  } else {
    pred->ptrnext = curr->ptrnext;
  }

  if (curr == this->tail) {
    this->tail = pred;
  }

  delete curr;
  --this->size;
}


template <typename Data>
bool SetLst<Data>::Exists(const Data& d) const noexcept {
  typename List<Data>::Node* pred = nullptr;
  typename List<Data>::Node* found = BinarySearch(d, pred);
  return (found != nullptr);
}

template <typename Data>
void SetLst<Data>::Clear() {
  List<Data>::Clear();
}

template <typename Data>
const Data& SetLst<Data>::operator[](const ulong pos) const {
  if (pos >= this->size) {
    throw std::out_of_range("Index out of range.");
  }
  return List<Data>::operator[](pos);
}




template <typename Data>
typename List<Data>::Node* SetLst<Data>::BinarySearch(const Data& val, typename List<Data>::Node*& pred) const noexcept {
  pred = nullptr;

  long left = 0;
  long right = this->size - 1;

  while (left <= right) {
    long mid = left + (right - left) / 2;

    // Scorri dalla head fino al nodo in posizione mid
    typename List<Data>::Node* midNode = this->head;
    typename List<Data>::Node* prev = nullptr;
    for (long i = 0; i < mid; ++i) {
      prev = midNode;
      midNode = midNode->ptrnext;
    }

    if (midNode->Element == val) {
      pred = prev;         
      return midNode;
    } else if (val < midNode->Element) {
      right = mid - 1;
    } else {
      pred = midNode;       // il migliore candidato < val
      left = mid + 1;
    }
  }

  // Non trovato
  return nullptr;
}

}