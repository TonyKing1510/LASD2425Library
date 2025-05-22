
using namespace std;
namespace lasd {


/* ************************************************************************** */
/*Specific member functions for Linear Container*/

// Definizione dell'operatore di uguaglianza (==)
template<typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data>& container) const noexcept {
    
    // Se i due contenitori sono lo stesso oggetto (stesso indirizzo di memoria), sono sicuramente uguali
    if (this == &container) {
        return true;
    }

    // Se le dimensioni sono diverse, i contenitori non possono essere uguali
    if (this->size != container.Size()) {
        return false;
    }

    // Confronto elemento per elemento usando l'indice
    for (ulong i = 0; i < this->size; i++) {
        // Se trovo un elemento diverso, i contenitori non sono uguali
        if ((*this)[i] != container[i]) {
            return false;
        }
    }

    // Se arrivo fin qui, tutti gli elementi sono uguali -> contenitori uguali
    return true;
}

// Definizione dell'operatore di disuguaglianza (!=)
template<typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& other) const noexcept {
    
    // Se i due contenitori sono lo stesso oggetto (stesso indirizzo), sono uguali -> quindi ! = false
    if (this == &other) {
        return false;
    }

    // Se le dimensioni sono diverse -> sicuramente diversi
    if (this->size != other.Size()) {
        return true;
    }

    // Confronto elemento per elemento usando Traverse
    bool isDiversi = false;
    int index = 0;

    Traverse([&other, &isDiversi, &index](const Data &dat) {
        // Se trovo un elemento diverso -> sono diversi
        if (dat != other[index]) {
            isDiversi = true;
            return true;  // Interrompi Traverse subito
        }
        index++;
        return false;
    });

    // Se ho trovato differenze -> true, altrimenti false
    return isDiversi;
}

template<typename Data>
inline const Data& LinearContainer<Data>::Front() const {
    if (this->size== 0) {
        throw length_error("Container is empty");
    }
    return (*this)[0];
}
template<typename Data>
inline const Data& LinearContainer<Data>::Back() const {
    if (this->size == 0) {
        throw length_error("Container is empty");
    }
    return (*this)[this->size - 1];
}

// Implementazione del metodo Traverse (richiesto dall'interfaccia TraversableContainer)
template<typename Data>
void LinearContainer<Data>::Traverse(TraverseFun fun) const {
    // Traverse di default per un LinearContainer: usa PreOrderTraverse (visita in ordine naturale)
    PreOrderTraverse(fun);
}

// Implementazione del PreOrderTraverse (visita in ordine naturale, da inizio a fine)
template<typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
    for (size_t i = 0; i < this->size; i++) {
        fun((*this)[i]);
    }
}

// Implementazione del PostOrderTraverse (visita in ordine inverso, da fine a inizio)
template<typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
    for (size_t i = this->size; i-- > 0;) {
        fun((*this)[i]);
    }
}



/* ************************************************************************** */
/*Specific member functions for MutableLinear Container*/

template<typename Data>
inline Data& MutableLinearContainer<Data>::Front() {
    if (this->size== 0) {
        throw length_error("Container is empty");
    }
    return (*this)[0];
}

template<typename Data>
inline Data& MutableLinearContainer<Data>::Back() {
    if (this->size == 0) {
        throw length_error("Container is empty");
    }
    return (*this)[this->size - 1];
}
template<typename Data>
void MutableLinearContainer<Data>::Map(MapFun fun) {
    // Applica la funzione "fun" a tutti gli elementi del contenitore
    for (ulong i = 0; i < this->size; i++) {
        fun((*this)[i]);  // Applica la funzione "fun" all'elemento corrente
    }
}
template<typename Data>
void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
   for (size_t i = 0; i < this->size; i++) {
        fun((*this)[i]);
    }
}
template<typename Data>
void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
    for (size_t i = this->size; i-- > 0;) {
        fun((*this)[i]);
    }
}


/* ************************************************************************** */
/*Specific member functions for SortableLinear Container*/

template<typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
    if(this->size > 1){
        InsertionSort();
    }
}

template<typename Data>
void SortableLinearContainer<Data>::InsertionSort() noexcept {
    for (ulong i = 1; i < this->size; i++) {
        Data key = (*this)[i];
        long j = i - 1; 

        while (j >= 0 && (*this)[j] > key) {
            (*this)[j + 1] = (*this)[j];
            j--;
        }
        (*this)[j + 1] = key;
    }
}





/* ************************************************************************** */

}
