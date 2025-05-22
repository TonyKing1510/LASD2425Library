
namespace lasd{
    /* ************************************************************************** */
    template <typename Data>
    lasd::SetVec<Data>::SetVec(const TraversableContainer<Data>& other) noexcept {
        // Resize iniziale per accogliere gli elementi
        this->Resize(4); 
    
    
        other.Traverse([this](const Data& dat) {
            this->Insert(dat);  
        });
    }
    

        template <typename Data>
        lasd::SetVec<Data>::SetVec(MappableContainer<Data>&& other) noexcept {
            // Resize iniziale per accogliere gli elementi
            this->Resize(4);

            
            other.Map([this](Data& dat) {
                if (!this->Exists(dat)) {  
                    this->Insert(std::move(dat));
                }
            });
        }

        template <typename Data>
        lasd::SetVec<Data>::SetVec(const SetVec<Data>& other) noexcept {
            // Copia gli elementi da 'other' nel nuovo SetVec
            this->Resize(other.capacity);
            for (ulong i = 0; i < other.size; ++i) {
                this->Insert(other.elem[i]);  
            }
        }

        template <typename Data>
        lasd::SetVec<Data>::SetVec(SetVec<Data>&& other) noexcept {
        
            std::swap(this->elem, other.elem);
            std::swap(this->size, other.size);
            std::swap(this->capacity, other.capacity);
            std::swap(this->head, other.head);
            std::swap(this->tail, other.tail);
        }

        template <typename Data>
        lasd::SetVec<Data>& lasd::SetVec<Data>::operator=(const SetVec<Data>& other) noexcept {
            if (this != &other) {  // Evito l'auto-assegnazione
                // Rilascio le risorse precedenti
                this->Clear();

                // Ridimensiono il vettore per copiare gli elementi
                this->Resize(other.capacity);

                // Copio gli elementi uno ad uno nel nuovo SetVec
                for (ulong i = 0; i < other.size; ++i) {
                    this->Insert(other.elem[i]); 
                }
            }

            return *this; 
        }

        template <typename Data>
        lasd::SetVec<Data>& lasd::SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
            if (this != &other) {  // Evito l'auto-assegnazione
                // Rilascio le risorse precedenti
                this->Clear();
               
                std::swap(this->elem, other.elem);
                std::swap(this->size, other.size);
                std::swap(this->capacity, other.capacity);
                std::swap(this->head, other.head);
                std::swap(this->tail, other.tail);
            }

            return *this; 
        }

        template <typename Data>
        bool lasd::SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
            if (this == &other) {
                return true;  
            }

            if (this->size != other.size) {
                return false;  
            }

            for (ulong i = 0; i < this->size; ++i) {
                if (this->elem[Index(i)] != other.elem[other.Index(i)]) {
                    return false;
                }
            }

            return true; 
        }
        template <typename Data>
        bool lasd::SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
            return !(*this == other);  
        }

        template <typename Data>
        bool lasd::SetVec<Data>::Insert(const Data& data) {
            // Se esiste già, non inserisco
            if (this->Exists(data)) {
                return false;
            }

            // Espando se necessario
            if (this->size == this->capacity) {
                this->Expand();
            }

            // Trovo la posizione in cui inserire usando BinarySearch (modificata per ottenere posizione)
            ulong left = 0;
            ulong right = size;
            ulong insertPos = 0;

            while (left < right) {
                ulong mid = left + (right - left) / 2;
                if (this->elem[Index(mid)] < data) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }

            insertPos = left;

            // Sposto a destra da insertPos
            ShiftRight(Index(insertPos));

            // Inserisco l'elemento nella posizione corretta
            this->elem[Index(insertPos)] = data;

            // Aumento la dimensione
            this->size++;

            // Aggiorno la coda
            this->tail = (this->tail + 1) % this->capacity;

            return true;
        }


        template <typename Data>
        bool lasd::SetVec<Data>::Insert(Data&& data) {
            // Se esiste già, non inserisco
            if (this->Exists(data)) {
                return false;
            }

            // Espando se necessario
            if (this->size == this->capacity) {
                this->Expand();
            }

            // Trovo la posizione in cui inserire usando BinarySearch (modificata per ottenere posizione)
            ulong left = 0;
            ulong right = size;
            ulong insertPos = 0;

            while (left < right) {
                ulong mid = left + (right - left) / 2;
                if (this->elem[Index(mid)] < data) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }

            insertPos = left;

            // Sposto a destra da insertPos
            ShiftRight(Index(insertPos));

            // Inserisco l'elemento nella posizione corretta
            this->elem[Index(insertPos)] = std::move(data);

            // Aumento la dimensione
            this->size++;

            // Aggiorno la coda
            this->tail = (this->tail + 1) % this->capacity;

            return true;
        }



        template <typename Data>
        bool lasd::SetVec<Data>::Remove(const Data& data) {
            // Uso la BinarySearch per trovare la posizione logica dell'elemento
            long index = BinarySearch(data);

            if (index == -1) {
                return false; 
            }

            // Ottengo la posizione reale nel vettore circolare
            ulong realPos = Index(index);

            // Sposto a sinistra da quella posizione
            ShiftLeft(realPos);

            // Decremento il numero di elementi
            this->size--;

            // Aggiorno la posizione della coda
            if (this->tail == 0) {
                this->tail = this->capacity - 1;
            } else {
                this->tail--;
            }

            return true;
        }

        template <typename Data>
        void lasd::SetVec<Data>::ShiftRight(ulong n) {
            for (ulong i = this->size; i > n; --i) {
                this->elem[Index(i)] = std::move(this->elem[Index(i - 1)]);
            }
        }
        

        template <typename Data>
        void lasd::SetVec<Data>::ShiftLeft(ulong pos) {
            // Sposto gli elementi a sinistra a partire dalla posizione data
            for (ulong i = pos; i < this->size - 1; ++i) {
                this->elem[Index(i)] = std::move(this->elem[Index(i + 1)]);
            }
        }


        template <typename Data>
        ulong lasd::SetVec<Data>::Index(ulong pos) const {
            // Restituisco l'indice reale usando l'offset rispetto a 'head'
            return (this->head + pos) % this->capacity;
        }

        template <typename Data>
        void lasd::SetVec<Data>::Expand() {
            // Creo un nuovo vettore con capacità raddoppiata
            ulong new_capacity = this->capacity * 2;
            Vector<Data> new_elem(new_capacity);
        
            // Copio gli elementi nel nuovo vettore
            for (ulong i = 0; i < this->size; ++i) {
                new_elem[i] = std::move(this->elem[Index(i)]);
            }
        
            // Reset della testa e coda per il nuovo vettore circolare
            this->head = 0;
            this->tail = this->size;
        
            // Sostituisco il vecchio vettore con il nuovo
            this->elem = std::move(new_elem);
            this->capacity = new_capacity;
        }


        template <typename Data>
        void lasd::SetVec<Data>::Resize(ulong new_capacity) {
            if (new_capacity == 0) {
                this->Clear();
                return;
            }

            // Creo un nuovo vettore con la capacità richiesta
            Vector<Data> new_elem(new_capacity);

            elem.Resize(new_capacity);

            // Se la nuova capacità è inferiore alla dimensione attuale, riduco la dimensione
            if (this->size > new_capacity) {
                this->size = new_capacity;
            }

            // Reimposto la testa
            this->head = 0;
            this->tail = this->size;
        }


        template <typename Data>
        void lasd::SetVec<Data>::Clear() {
            // Reset della dimensione e degli indici
            this->size = 0;
            this->head = 0;
            this->tail = 0;
        }


        template <typename Data>
        const Data& lasd::SetVec<Data>::operator[](const ulong pos) const {
            if (pos >= this->size) {
                throw std::out_of_range("Index out of range.");
            }
            // Restituisco l'elemento all'indice logico 'pos'
            return this->elem[Index(pos)];
        }


        template <typename Data>
        bool lasd::SetVec<Data>::Exists(const Data& data) const noexcept {
            return (BinarySearch(data) != -1);
        }




            template <typename Data>
            const Data& lasd::SetVec<Data>::Min() {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }
                return this->elem[0];  
            }

            template <typename Data>
            Data lasd::SetVec<Data>::MinNRemove() {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }
                Data minElem = this->elem[0];  
                this->Remove(minElem);  
                return minElem;  
            }

            template <typename Data>
            void lasd::SetVec<Data>::RemoveMin() {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }
                this->Remove(this->elem[0]);  
            }

            template <typename Data>
            const Data& lasd::SetVec<Data>::Max() {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }
                return this->elem[this->size - 1];  
            }

            template <typename Data>
            Data lasd::SetVec<Data>::MaxNRemove() {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }
                Data maxElem = this->elem[this->size - 1]; 
                this->Remove(maxElem); 
                return maxElem; 
            }

            template <typename Data>
            void lasd::SetVec<Data>::RemoveMax() {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }
                this->Remove(this->elem[this->size - 1]); 
            }

            template <typename Data>
            const Data& lasd::SetVec<Data>::Predecessor(const Data& data) {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }

                const Data* result = nullptr;

                for (ulong i = 0; i < this->size; ++i) {
                    if (this->elem[i] < data) {
                        result = &(this->elem[i]);  // Aggiorno il candidato predecessore
                    } else {
                        break;  // esco : SetVec è ordinato, non troverò altri minori
                    }
                }

                if (result != nullptr) {
                    return *result;
                } else {
                    throw std::length_error("No predecessor found");
                }
            }

            template <typename Data>
            Data lasd::SetVec<Data>::PredecessorNRemove(const Data& data) {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }

                bool found = false;
                ulong predIndex = 0;

                for (ulong i = 0; i < this->size; ++i) {
                    ulong realIndex = Index(i);
                    if (this->elem[realIndex] < data) {
                        predIndex = realIndex;
                        found = true;
                    } else {
                        break;
                    }
                }

                if (!found) {
                    throw std::length_error("No predecessor found");
                }

                Data result = std::move(this->elem[predIndex]);

                ShiftLeft(predIndex);
                --size;

                // Aggiorno la coda (tail)
                if (this->tail == 0) {
                    this->tail = capacity - 1;
                } else {
                    this->tail -= 1;
                }

                return result;
            }
            

           template <typename Data>
            void lasd::SetVec<Data>::RemovePredecessor(const Data& data) {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }

                bool found = false;
                ulong predIndex = 0;

                for (ulong i = 0; i < this->size; ++i) {
                    ulong realIndex = this->Index(i);
                    if (this->elem[realIndex] < data) {
                        predIndex = realIndex;
                        found = true;
                    } else {
                        break;
                    }
                }

                if (!found) {
                    throw std::length_error("No predecessor found");
                }

                this->ShiftLeft(predIndex);
                --this->size;

                if (this->tail == 0) {
                    this->tail = this->capacity - 1;
                } else {
                    this->tail -= 1;
                }
            }



            template <typename Data>
            const Data& lasd::SetVec<Data>::Successor(const Data& data) {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }

                for (ulong i = 0; i < this->size; ++i) {
                    if (this->elem[i] > data) {  // Primo elemento strettamente maggiore di 'data'
                        return this->elem[i];
                    }
                }

                throw std::length_error("No successor found");  // Se nessun elemento maggiore esiste
        }


            

            template <typename Data>
            Data lasd::SetVec<Data>::SuccessorNRemove(const Data& data) {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }

                for (ulong i = 0; i < this->size; ++i) {
                    ulong realIndex = this->Index(i);
                    if (this->elem[realIndex] > data) {
                        Data succElem = this->elem[realIndex]; // Copio il successore
                        this->ShiftLeft(realIndex); // Rimuovo l'elemento spostando
                        --this->size;

                        if (this->tail == 0) {
                            this->tail = this->capacity - 1;
                        } else {
                            this->tail -= 1;
                        }

                        return succElem;
                    }
                }

                throw std::length_error("No successor found");
            }


            template <typename Data>
            void lasd::SetVec<Data>::RemoveSuccessor(const Data& data) {
                if (this->size == 0) {
                    throw std::length_error("SetVec is empty");
                }

                for (ulong i = 0; i < this->size; ++i) {
                    ulong realIndex = this->Index(i);
                    if (this->elem[realIndex] > data) {
                        this->ShiftLeft(realIndex);
                        --this->size;

                        if (this->tail == 0) {
                            this->tail = this->capacity - 1;
                        } else {
                            this->tail -= 1;
                        }

                        return;
                    }
                }

                throw std::length_error("No successor found");
            }


// Cerca un elemento e ritorna la sua posizione nel vettore se presente, altrimenti -1
template <typename Data>
long lasd::SetVec<Data>::BinarySearch(const Data& val) const {
    if (this->size == 0) return -1;

    long left = 0;
    long right = size - 1;

    while (left <= right) {
        long mid = left + (right - left) / 2;
        const ulong realIndex = Index(mid); 

        if (this->elem[realIndex] == val) {
            return realIndex;
        } else if (this->elem[realIndex] < val) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}





}