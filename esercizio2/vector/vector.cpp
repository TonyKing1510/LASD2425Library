#include<iostream>
#include<algorithm>
using namespace std;
#include <stdexcept>

namespace lasd {

/* ************************************************************************** */
/*Function of class vector*/



template<typename Data>
    lasd::Vector<Data>::Vector(const ulong initialSize)
    {
        this->size=initialSize;
        this->elem=new Data[initialSize] {};
    }

// Costruttore della classe lasd::Vector che prende un container attraversabile come parametro
template<typename Data>
lasd::Vector<Data>::Vector(const TraversableContainer<Data>& container)
{
    // Imposta la dimensione del vettore uguale alla dimensione del container passato
    this->size = container.Size();

    // Alloca dinamicamente un array di elementi di tipo Data e lo inizializza a valori di default
    this->elem = new Data[this->size] {};

    // Inizializza l'indice a 0 per tracciare la posizione nell'array
    ulong i = 0;

    // Attraversa (traverse) tutti gli elementi del container
    container.Traverse([this, &i](const Data& dat) {
        // Copia l'elemento corrente del container nell'array alla posizione i
        this->elem[i] = dat;

        // Incrementa l'indice per la prossima posizione
        i++;
    });
}


// Costruttore della classe lasd::Vector che prende un MappableContainer tramite move (rvalue reference)
template<typename Data>
lasd::Vector<Data>::Vector(MappableContainer<Data>&& container)
{
    // Imposta la dimensione del vettore uguale alla dimensione del container passato
    this->size = container.Size();

    // Alloca dinamicamente un array di elementi di tipo Data e lo inizializza a valori di default
    this->elem = new Data[this->size] {};

    // Inizializza l'indice a 0 per tracciare la posizione nell'array
    ulong i = 0;

    // Applica una funzione (map) a tutti gli elementi del container (in questo caso li sposta nel nuovo array)
    container.Map(
        [this, &i](Data &dat)  
        {
            // Sposta (move semantic) l'elemento corrente dal container all'array interno nella posizione i
            this->elem[i] = std::move(dat);

            // Incrementa l'indice per la prossima posizione
            i++;
        });
}


    template <typename Data>
    const Data& lasd::Vector<Data>::operator[](const ulong i) const
    {
        if (i < this->size)
        {
            return this->elem[i];
        }
        else
        {
            throw std::out_of_range("Index out of range");
        }
    }

    template <typename Data>
    Data& lasd::Vector<Data>::operator[](ulong i) 
    {
        if (i < this->size)
        {
            return this->elem[i];
        }
        else
        {
            throw std::out_of_range("Index out of range");
        }
    }
    

    template<typename Data>
    lasd::Vector<Data>::Vector(const Vector<Data> &v)
    {
        this->elem = new Data[v.size];
        std::copy(v.elem, v.elem + v.size, this->elem);
        this->size = v.size;
    }

    template<typename Data>
    lasd::Vector<Data>::Vector(Vector<Data> &&v) noexcept {
        this->elem = v.elem;
        this->size = v.size;
        v.elem = nullptr;
        v.size = 0;
    }


    template<typename Data>
    lasd::Vector<Data>::~Vector() noexcept
    {
        delete[] this->elem;
        this->elem = nullptr;
    }

    template<typename Data>
    Vector<Data>& lasd::Vector<Data>::operator=(const Vector<Data> &v)
    {
        Vector<Data> *tmpVec = new Vector<Data>(v);
        std::swap(*tmpVec,*this);
        delete tmpVec;
        return *this;
    }

    template<typename Data>
    Vector<Data>& lasd::Vector<Data>::operator=(Vector<Data> &&v) noexcept
    {
        std::swap(this->elem, v.elem);
        std::swap(size,v.size);
        return *this;
    }

    template<typename Data>
    bool lasd::Vector<Data>::operator==(const Vector<Data>& v) const noexcept
    {
        if (this == &v)
        {
            return true;
        }
        if (this->size != v.size)
        {
            return false;
        }
        for (ulong i = 0; i < this->size; i++)
        {
            if (this->elem[i] != v.elem[i])
            {
                return false;
            }
        }
        return true;
    }

    template<typename Data>
    bool lasd::Vector<Data>::operator!=(const Vector<Data>& v) const noexcept
    {
       return !(*this == v);
    }

    // Funzione membro per ridimensionare il vettore a una nuova dimensione
    template<typename Data>
    void lasd::Vector<Data>::Resize(const ulong newSize)
    {
        // Se la nuova dimensione è zero, dealloca l'array e azzera i dati
        if (newSize == 0)
        {
            Clear();
        }
        else // Caso in cui la nuova dimensione è maggiore di zero
        {
            // Alloca un nuovo array di dimensione newSize, inizializzato a valori di default
            Data* newElem = new Data[newSize] {};

            // Calcola il numero minimo di elementi da copiare (tra vecchia e nuova dimensione)
            ulong minSize = std::min(this->size, newSize);

            // Copia i primi minSize elementi dal vecchio array al nuovo array
            std::copy(this->elem, this->elem + minSize, newElem);

            // Libera la memoria del vecchio array
            delete[] this->elem;

            // Aggiorna il puntatore al nuovo array
            this->elem = newElem;

            // Aggiorna la dimensione del vettore
            this->size = newSize;
        }
    }

    template<typename Data>
    void lasd::Vector<Data>::Clear() noexcept
    {
        if(this->elem != nullptr)
        {
            delete[] this->elem;
            this->elem = nullptr;
            this->size = 0;
        }
    }

    template <typename Data>
    const Data& lasd::Vector<Data>::Front() const
    {
        if(this->size != 0){
            return this->elem[0];
        }else{
            throw std::length_error("La dimensione è errata");
        }
    }

    template <typename Data>
    Data &lasd::Vector<Data>::Front()
    {
        if (this->size != 0)
        {
            return this->elem[0];
        }
        else
        {
            throw std::length_error("La dimensione è errata");
        }
    }

    template <typename Data>
    const Data &lasd::Vector<Data>::Back() const
    {
        if (size != 0)
        {
            return this->elem[this->size-1];
        }
        else
        {
            throw std::length_error("La dimensione è erraata");
        }
    }

    template <typename Data>
    Data &lasd::Vector<Data>::Back()
    {
        if (size != 0)
        {
            return this->elem[this->size-1];
        }
        else
        {
            throw std::length_error("La dimensione è errata");
        }
    }

    /*Member for SortableVector.hpp*/
    // qui in sortable usare i metodi di Vector
    template<typename Data>
    SortableVector<Data>::SortableVector(const ulong initialSize) : Vector<Data>(initialSize){};

    template<typename Data>
    SortableVector<Data>::SortableVector(const TraversableContainer<Data>& container) : Vector<Data>(container){};

    template <typename Data>
    lasd::SortableVector<Data>::SortableVector(MappableContainer<Data> &&other) noexcept : Vector<Data>(std::move(other)){};

    template <typename Data>
    lasd::SortableVector<Data>::SortableVector(const SortableVector<Data>& other) noexcept : Vector<Data>(other){};

    template <typename Data>
    lasd::SortableVector<Data>::SortableVector(SortableVector<Data>&& other) noexcept : Vector<Data>(std::move(other)){};

    template <typename Data>
    lasd::SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& other) noexcept
    {
        Vector<Data>::operator=(other);
        return *this;
    };

    template <typename Data>
    lasd::SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& other) noexcept
    {
        Vector<Data>::operator=(std::move(other));
        return *this;
    };

/* ************************************************************************** */

}
