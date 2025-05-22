
namespace lasd {

/* ************************************************************************** */

/* specific member of List::Node */
//operator ==
template <typename Data>
bool List<Data>::Node::operator==(const Node& n)const noexcept{
     if(Element==n.Element){
        return true;
}
};

//operator !=
template <typename Data>
bool List<Data>::Node::operator!=(const Node& n)const noexcept{
    return !(*this==n);
};

//Clone
template <typename Data>
typename List<Data>::Node* List<Data>::Node::Clone(Node* head) {
    if (head == nullptr) {
        return nullptr; // Restituisci nullptr se la lista originale è vuota
    } else {
        // Clona il primo elemento della lista
        Node* Nhead = new Node(head->Element);
        Node* currentNnode = Nhead;

        // Clona il resto della lista
        Node* currentNode = head->ptrnext;
        while (currentNode != nullptr) {
            currentNnode->ptrnext = new Node(currentNode->Element);
            currentNnode = currentNnode->ptrnext;
            currentNode = currentNode->ptrnext;
        }

        
        return Nhead;
    }
}

/* ************************************************************************** */


//Lista
template <typename Data>
List<Data>::List(const TraversableContainer<Data>& c){
    c.Traverse([this](const Data& elem){
        InsertAtBack(elem);
    });

};

template <typename Data>
List<Data>::List(MappableContainer<Data>&& c){
    c.Map([this](Data& elem){
        InsertAtBack(std::move(elem));
    });
}

template <typename Data>
List<Data>::List(const List<Data> &L)
{
   L.Traverse([this](const Data& dat){
    InsertAtBack(dat);
   });
   this->size=L.size;
};

template <typename Data>
List<Data>::List(List<Data>&& L) noexcept{
   if(this!=&L){
    std::swap(this->head,L.head);
    std::swap(this->size,L.size);
    std::swap(this->tail,L.tail);

   };
};

template <typename Data>
List<Data>::~List(){
    Clear();
};

template <typename Data>
    List<Data> &lasd::List<Data>::operator=(const List<Data> &otherList) noexcept
    {
         if (this != &otherList) {
        this->Clear(); // Libera memoria esistente

        // Cloniamo i nodi a partire da otherList.head
        this->head = Node::Clone(otherList.head);

        // Aggiorna size e tail scorrendo la lista clonata
        this->size = 0;
        Node* current = this->head;
        this->tail = nullptr;

        while (current != nullptr) {
            this->tail = current;    // tail diventa l'ultimo nodo
            current = current->ptrnext;
            this->size++;
        }
    }

    return *this;
    };

template <typename Data>
    List<Data> &lasd::List<Data>::operator=(List<Data> &&otherList) noexcept
    {
        
            std::swap(this->head,otherList.head);
            std::swap(this->size,otherList.size);
            std::swap(this->tail,otherList.tail);
            return *this;
    };

    template <typename Data>
    bool lasd::List<Data>::operator==(const List<Data>& L) const noexcept {
        if (this->size != L.size) {
            return false;
        }
    
        // Definiamo due puntatori temporanei per scorrere le liste.
        Node* thisPtr = this->head;
        Node* LPtr = L.head;
    
        // Scorriamo entrambe le liste fino a quando non arriviamo alla fine di entrambe.
        while (thisPtr != nullptr && LPtr != nullptr) {
            // Controlla se gli elementi correnti delle due liste sono uguali.
            if (thisPtr->Element == LPtr->Element) {
                // Se sono uguali, passiamo agli elementi successivi nelle due liste.
                thisPtr = thisPtr->ptrnext;
                LPtr = LPtr->ptrnext;
            } else {
                // Se anche un solo elemento non è uguale, restituisci false.
                return false;
            }
        }
    
        // Se siamo arrivati alla fine di entrambe le liste senza trovare differenze,
        // allora le liste sono uguali.
        return true;
    };
    
    template <typename Data>
    bool lasd::List<Data>::operator!=(const List<Data>& L)const noexcept{
            return !(*this==L);
    };

    template <typename Data>
    void lasd::List<Data>::InsertAtFront(const Data& elem) {
        // Crea un nuovo nodo con l'elemento fornito.
        Node* newNode = new Node(elem);
        
        // Se la lista non è vuota, collega il nuovo nodo al nodo corrente in testa.
        if (head != nullptr) {
            newNode->ptrnext = head;
        }
    
        // Imposta il nuovo nodo come nuovo nodo in testa alla lista.
        head = newNode;
    
        // Se la lista è vuota, il nuovo nodo diventa anche il nodo finale.
        if (tail == nullptr) {
            tail = newNode;
        }
    
        // Incrementa la dimensione della lista.
        this->size++;
    
        // Dealloca la memoria per newNode se non serve più.
        // Nota: in questo caso non c'è bisogno di deallocazione esplicita
        // poiché il nodo appena creato non è stato restituito a un altro contesto.
        // Se la funzione fosse stata progettata diversamente, potrebbe essere necessario considerare
        // una diversa gestione della memoria.
        //delete newNode; // Non necessario in questa implementazione
    }

    template <typename Data>
    void lasd::List<Data>::InsertAtFront(Data&& elem) {
            // Crea un nuovo nodo con l'elemento fornito.
        Node* newNode = new Node(std::move(elem));
        
        // Se la lista non è vuota, collega il nuovo nodo al nodo corrente in testa.
        if (head != nullptr) {
            newNode->ptrnext = head;
        }

        // Imposta il nuovo nodo come nuovo nodo in testa alla lista.
        head = newNode;

        // Se la lista è vuota, il nuovo nodo diventa anche il nodo finale.
        if (tail == nullptr) {
            tail = newNode;
        }

        // Incrementa la dimensione della lista.
        this->size++;

        // Dealloca la memoria per newNode se non serve più.
        // Nota: in questo caso non c'è bisogno di deallocazione esplicita
        // poiché il nodo appena creato non è stato restituito a un altro contesto.
        // Se la funzione fosse stata progettata diversamente, potrebbe essere necessario considerare
        // una diversa gestione della memoria.
        //delete newNode; // Non necessario in questa implementazione
    };

    template <typename Data>
void lasd::List<Data>::RemoveFromFront() {
    // Controlla se la lista non è vuota
    if (head != nullptr) {

        // Salva il puntatore al nodo da eliminare (l'attuale head)
        Node* temp = this->head;

        // Se la lista contiene un solo elemento (head e tail coincidono)
        if (tail == head) {
            // La lista diventerà vuota, quindi azzera sia head che tail
            tail = head = nullptr;
        } else {
            // Altrimenti sposta head al nodo successivo
            head = head->ptrnext;
        }

        // Decrementa la dimensione della lista
        this->size--;

        // Disconnette il nodo da eliminare dal resto della lista (buona pratica)
        temp->ptrnext = nullptr;

        // Dealloca il nodo rimosso
        delete temp;
    } else {
        // Se la lista è vuota, lancia un'eccezione di lunghezza
        throw std::length_error("Lista vuota");
    }
}

    //stessa cosa di RemoveFromFront ma restituisce il valore
    template <typename Data>
    Data List<Data>::FrontNRemove(){
        if(head!=nullptr){
            Node *temp =head;
            Data NewEl;
            NewEl=head->Element;
            if(tail==head){
                tail=head=nullptr;
            }else{
                head=head->ptrnext;
            };
            size--;
            temp->ptrnext=nullptr;
            delete temp;
            return NewEl;
        }else{
            throw std::length_error("Lista vuota");
        };
    
    };

    template <typename Data>
    void lasd::List<Data>::InsertAtBack(const Data& elem) {
        // Crea un nuovo nodo con l'elemento fornito.
        Node* newNode = new Node(elem);
        
        // Se la lista è vuota, il nuovo nodo diventa sia head che tail.
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            // Altrimenti, collega il nuovo nodo alla fine della lista.
            tail->ptrnext = newNode;
            tail = newNode;
        }
    
        // Incrementa la dimensione della lista.
        this->size++;
    }
    template <typename Data>
    void lasd::List<Data>::InsertAtBack(Data&& elem) {
        // Crea un nuovo nodo con l'elemento fornito.
        Node* newNode = new Node(std::move(elem));
        
        // Se la lista è vuota, il nuovo nodo diventa sia head che tail.
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            // Altrimenti, collega il nuovo nodo alla fine della lista.
            tail->ptrnext = newNode;
            tail = newNode;
        }
    
        // Incrementa la dimensione della lista.
        this->size++;
    }
    template <typename Data>
void lasd::List<Data>::RemoveFromBack() {
    if (head != nullptr) {
        if (tail == head) {
            // La lista diventerà vuota
            delete head; 
            tail = head = nullptr;
        } else {
            Node* current = head;
            while (current->ptrnext != tail) {
                current = current->ptrnext;
            }
            // Dealloca il vecchio tail
            delete tail; 
            // Imposta il penultimo nodo come nuovo tail
            tail = current;
            tail->ptrnext = nullptr;
        }

        this->size--;
    } else {
        throw std::length_error("Lista vuota");
    }
}

template <typename Data>
Data List<Data>::BackNRemove() {
    if (tail != nullptr) {
        Node* temp = tail;
        Data NewEl = tail->Element;

        if (tail == head) {
            tail = head = nullptr;
        } else {
            Node* current = head;
            while (current->ptrnext != tail) {
                current = current->ptrnext;
            }
            tail = current;
            tail->ptrnext = nullptr;
        }

        size--;
        temp->ptrnext = nullptr;
        delete temp;
        return NewEl;
    } else {
        throw std::length_error("Lista vuota");
    }
}

template <typename Data>
const Data& lasd::List<Data>::operator[](ulong i)const {
    if(head!=nullptr){
        ulong j=0;
        Node *curr=head;
        while(j!=i && curr!=nullptr){
            curr=curr->ptrnext;
            j++;
        };
        if(j == i && curr != nullptr) {
            return curr->Element;
        }
    }
    // Se l'indice è fuori dai limiti o la lista è vuota, lancia un'eccezione o restituisci un valore di default.
    throw std::out_of_range("Index out of range");
};

template <typename Data>
Data& lasd::List<Data>::operator[](ulong i){
    if(head!=nullptr){
        ulong j=0;
        Node *curr=head;
        while(j!=i && curr!=nullptr){
            curr=curr->ptrnext;
            j++;
        };
         if(j == i && curr != nullptr) {
            return curr->Element;
        }
    }
    // Se l'indice è fuori dai limiti o la lista è vuota, lancia un'eccezione o restituisci un valore di default.
    throw std::out_of_range("Index out of range");
};

template <typename Data>
const Data& lasd::List<Data>::Front()const{
    if(this->head!=nullptr){
        return this->head->Element;
    }else{
       throw std::length_error("Lista vuota");
    };
};


template <typename Data>
 Data& lasd::List<Data>::Front(){
    if(this->head!=nullptr){
        return this->head->Element;
    }else{
        throw std::length_error("Lista vuota");
    };
};

template <typename Data>
const Data& lasd::List<Data>::Back()const{
    if(this->tail!=nullptr){
        return this->tail->Element;
    }else{
        throw std::length_error("Lista vuota");
    };
};

template <typename Data>
 Data& lasd::List<Data>::Back(){
    if(this->tail!=nullptr){
        return this->tail->Element;
    }else{
       throw std::length_error("Lista vuota");
    };
};


template <typename Data>
void lasd::List<Data>::Map(MapFun fun){
    PreOrderMap(fun,head);
};

template <typename Data>
void lasd::List<Data>::PreOrderMap(MapFun fun){
    PreOrderMap(fun,head);
};

template <typename Data>
void lasd::List<Data>::PostOrderMap(MapFun fun){
    PostOrderMap(fun,head);
};

template <typename Data>
void lasd::List<Data>::Traverse(TraverseFun fun) const{
     PreOrderTraverse(fun,head);
};

template <typename Data>
void lasd::List<Data>::PreOrderTraverse(TraverseFun fun)const{
    PreOrderTraverse(fun,head);
};


template <typename Data>
void lasd::List<Data>::PostOrderTraverse(TraverseFun fun)const{
    PostOrderTraverse(fun,head);
};




template <typename Data>

void List<Data>::PreOrderTraverse(TraverseFun fun, const Node* curr) const{
    while(curr!=nullptr){
        fun(curr->Element);
        curr=curr->ptrnext;
    };
};



template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun , const Node *curr) const{
    if(curr==nullptr){
        return;
    }else{
        PostOrderTraverse(fun,curr->ptrnext);
        fun(curr->Element);
    }
}

template <typename Data>
void List<Data>::PreOrderMap(MapFun fun,  Node *curr) {
    while(curr!=nullptr){
        fun(curr->Element);
        curr=curr->ptrnext;
    }
};


template <typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node *curr) {
    if(curr==nullptr){
        return;
    }else{
        PostOrderMap(fun,curr->ptrnext);
        fun(curr->Element);
    }
};



template <typename Data>
void lasd::List<Data>::Clear(){
    struct Node* in_esame=this->head;
    while(in_esame!=nullptr){
        struct Node*prox=in_esame->ptrnext;
        delete in_esame;
        in_esame=prox;
    };
    this->size=0;
    this->head=nullptr;
    this->tail=nullptr;
};



/* ************************************************************************** */

}
