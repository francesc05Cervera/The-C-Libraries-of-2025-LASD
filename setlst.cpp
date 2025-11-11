#include "setlst.hpp"
#include <stdexcept>

namespace lasd
{

    // Costruttore da TraversableContainer
    template <typename Data>
    SetLst<Data>::SetLst(const TraversableContainer<Data> &container) { // Inserisce tutti gli elementi del container
        container.Traverse([this](const Data &elem)
                           { this->Insert(elem); }); // Inserisce ogni elemento tramite Insert
    }

    // Costruttore da MappableContainer (move)
    template <typename Data>
    SetLst<Data>::SetLst(MappableContainer<Data> &&container) noexcept { // Inserisce tutti gli elementi tramite move
        for (ulong i = 0; i < container.Size(); ++i) {
            Insert(std::move(container[i])); // Inserisce ogni elemento tramite move
        }
    }

    // Costruttore di copia
    template <typename Data>
    SetLst<Data>::SetLst(const SetLst<Data> &other) : List<Data>(other) {} // Costruisce tramite copia della lista

    // Costruttore di move
    template <typename Data>
    SetLst<Data>::SetLst(SetLst<Data> &&other) noexcept : List<Data>(std::move(other)) {} // Costruisce tramite move della lista

    // Assegnamento di copia
    template <typename Data>
    SetLst<Data> &SetLst<Data>::operator=(const SetLst<Data> &other) {
        List<Data>::operator=(other); // Copia la lista
        return *this;
    }

    // Assegnamento di move
    template <typename Data>
    SetLst<Data> &SetLst<Data>::operator=(SetLst<Data> &&other) noexcept {
        List<Data>::operator=(std::move(other)); // Move della lista
        return *this;
    }

    // Operatore di uguaglianza
    template <typename Data>
    bool SetLst<Data>::operator==(const SetLst<Data> &other) const noexcept {
        return List<Data>::operator==(other); // Confronta le liste
    }

    // Operatore di disuguaglianza
    template <typename Data>
    bool SetLst<Data>::operator!=(const SetLst<Data> &other) const noexcept {
        return !(*this == other); // Negazione dell'uguaglianza
    }

    // Restituisce il minimo (primo elemento)
    template <typename Data>
    const Data &SetLst<Data>::Min() const {
        if (this->Empty())
            throw std::length_error("SetLst is empty"); // Eccezione se vuoto
        return this->Front(); // Ritorna il primo elemento
    }

    // Restituisce e rimuove il minimo
    template <typename Data>
    Data SetLst<Data>::MinNRemove() {
        if (this->Empty())
            throw std::length_error("SetLst is empty"); // Eccezione se vuoto
        Data min = this->Front(); // Prende il primo elemento
        this->RemoveFromFront(); // Rimuove il primo elemento
        return min; // Ritorna il valore rimosso
    }

    // Rimuove il minimo
    template <typename Data>
    void SetLst<Data>::RemoveMin() {
        if (this->Empty())
            throw std::length_error("SetLst is empty"); // Eccezione se vuoto
        this->RemoveFromFront(); // Rimuove il primo elemento
    }

    // Restituisce il massimo (ultimo elemento)
    template <typename Data>
    const Data &SetLst<Data>::Max() const {
        if (this->Empty())
            throw std::length_error("SetLst is empty"); // Eccezione se vuoto
        return this->Back(); // Ritorna l'ultimo elemento
    }

    // Restituisce e rimuove il massimo
    template <typename Data>
    Data SetLst<Data>::MaxNRemove() {
        if (this->Empty())
            throw std::length_error("SetLst is empty"); // Eccezione se vuoto
        Data max = this->Back(); // Prende l'ultimo elemento
        this->RemoveFromBack(); // Rimuove l'ultimo elemento
        return max; // Ritorna il valore rimosso
    }

    // Rimuove il massimo
    template <typename Data>
    void SetLst<Data>::RemoveMax() {
        if (this->Empty())
            throw std::length_error("SetLst is empty"); // Eccezione se vuoto
        this->RemoveFromBack(); // Rimuove l'ultimo elemento
    }

    // Restituisce il predecessore di un valore
    template <typename Data>
    const Data &SetLst<Data>::Predecessor(const Data &value) const {
        if (this->Empty())
            throw std::length_error("Predecessore non trovato"); // Eccezione se vuoto

        ulong pos = 0;
        BinarySearch(value, pos); // Trova la posizione dove sarebbe value

        if (pos == 0)
            throw std::length_error("Predecessore non trovato"); // Nessun predecessore

        Node *curr = this->head;
        for (ulong i = 0; i < pos - 1; ++i)
            curr = curr->next; // Scorri fino al predecessore

        return curr->elements; // Ritorna il valore del predecessore
    }

    // Restituisce e rimuove il predecessore
    template <typename Data>
    Data SetLst<Data>::PredecessorNRemove(const Data &value) {
        if (this->Empty())
            throw std::length_error("Predecessore non trovato"); // Eccezione se vuoto

        ulong pos = 0;
        BinarySearch(value, pos);
        if (pos == 0)
            throw std::length_error("Predecessore non trovato"); // Nessun predecessore

        Node *curr = this->head;
        for (ulong i = 0; i < pos - 1; ++i)
            curr = curr->next; // Scorri fino al predecessore

        Data predValue = curr->elements; // Salva il valore
        Remove(predValue); // Rimuovi il predecessore
        return predValue; // Ritorna il valore rimosso
    }

    // Rimuove il predecessore
    template <typename Data>
    void SetLst<Data>::RemovePredecessor(const Data &value) {
        if (this->Empty())
            throw std::length_error("Predecessore non trovato"); // Eccezione se vuoto

        ulong pos = 0;
        BinarySearch(value, pos);
        if (pos == 0)
            throw std::length_error("Predecessore non trovato"); // Nessun predecessore

        Node *curr = this->head;
        for (ulong i = 0; i < pos - 1; ++i)
            curr = curr->next; // Scorri fino al predecessore

        Remove(curr->elements); // Rimuovi il predecessore
    }

    // Restituisce il successore di un valore
    template <typename Data>
    const Data &SetLst<Data>::Successor(const Data &value) const {
        if (this->Empty())
            throw std::length_error("Successore non trovato"); // Eccezione se vuoto

        ulong pos = 0;
        bool found = BinarySearch(value, pos); // Trova la posizione

        Node *curr = this->head;
        for (ulong i = 0; i < pos; ++i)
            curr = curr->next; // Scorri fino alla posizione

        if (found) {
            if (curr == nullptr || curr->next == nullptr)
                throw std::length_error("Successore non trovato"); // Nessun successore
            curr = curr->next; // Successore è il prossimo nodo
        }

        if (curr == nullptr || !(curr->elements > value))
            throw std::length_error("Successore non trovato"); // Nessun successore valido

        return curr->elements; // Ritorna il valore del successore
    }

    // Restituisce e rimuove il successore
    template <typename Data>
    Data SetLst<Data>::SuccessorNRemove(const Data &value) {
        if (this->Empty())
            throw std::length_error("Successore non trovato"); // Eccezione se vuoto

        ulong pos = 0;
        BinarySearch(value, pos);

        Node *curr = this->head;
        for (ulong i = 0; i < pos; ++i)
            curr = curr->next; // Scorri fino alla posizione

        if (curr == nullptr)
            throw std::length_error("Successore non trovato"); // Nessun successore
        if (!(curr->elements > value))
            throw std::length_error("Successore non trovato"); // Nessun successore valido

        Data succValue = curr->elements; // Salva il valore
        Remove(succValue); // Rimuovi il successore
        return succValue; // Ritorna il valore rimosso
    }

    // Rimuove il successore
    template <typename Data>
    void SetLst<Data>::RemoveSuccessor(const Data &value) {
        if (this->Empty())
            throw std::length_error("Successore non trovato"); // Eccezione se vuoto

        ulong pos = 0;
        BinarySearch(value, pos);

        Node *curr = this->head;
        for (ulong i = 0; i < pos; ++i)
            curr = curr->next; // Scorri fino alla posizione

        if (curr == nullptr)
            throw std::length_error("Successore non trovato"); // Nessun successore
        if (!(curr->elements > value))
            throw std::length_error("Successore non trovato"); // Nessun successore valido

        Remove(curr->elements); // Rimuovi il successore
    }

    // Inserisce un elemento nel set
    template <typename Data>
    bool SetLst<Data>::Insert(const Data &value) {
        if(Exists(value)){return false;} // Non inserisce se già presente
         
        if(this->head == nullptr){
            this->InsertAtFront(value); // Inserisce in testa se lista vuota
        }else if(value < head->elements){
           this->InsertAtFront(value); // Inserisce in testa se minore del primo
        }else if(value > tail->elements){
            this->InsertAtBack(value); // Inserisce in coda se maggiore dell'ultimo
        }else if(value > head->elements && value < tail->elements){
           Node *predecessor = head;
           Node *successor = nullptr;
           Node *tmp = nullptr;
           while(predecessor->next->elements < value){
            predecessor = predecessor->next; // Trova il predecessore
           }
           successor = predecessor->next;
           tmp = new Node(value); // Crea nuovo nodo
           tmp->next = successor; // Collega il nuovo nodo
           predecessor->next = tmp;
           size++; // Aggiorna la dimensione
        }
        return true;
    }

    // Inserisce un elemento tramite move
    template <typename Data>
    bool SetLst<Data>::Insert(Data &&value) noexcept {
        if(Exists(value)){return false;} // Non inserisce se già presente
         
        if(this->head == nullptr){
            this->InsertAtFront(value); // Inserisce in testa se lista vuota
        }else if(value < head->elements){
           this->InsertAtFront(value); // Inserisce in testa se minore del primo
        }else if(value > tail->elements){
            this->InsertAtBack(value); // Inserisce in coda se maggiore dell'ultimo
        }else if(value > head->elements && value < tail->elements){
           Node *predecessor = head;
           Node *successor = nullptr;
           Node *tmp = nullptr;
           while(predecessor->next->elements < value){
            predecessor = predecessor->next; // Trova il predecessore
           }
           successor = predecessor->next;
           tmp = new Node(std::move(value)); // Crea nuovo nodo con move
           tmp->next = successor;
           predecessor->next = tmp;
           size++; // Aggiorna la dimensione
        }
        return true;
    }

    // Rimuove un elemento dal set
    template <typename Data>
    bool SetLst<Data>::Remove(const Data &val) {
        if(size >0 && Exists(val)){
            if(val == head->elements){
                this->RemoveFromFront(); // Rimuove dalla testa
            }else if(val == tail->elements){
                this->RemoveFromBack(); // Rimuove dalla coda
            }else{
                Node *predecessor = head;
                Node *tmp = nullptr;
                while(predecessor->next->elements != val){predecessor = predecessor->next;} // Trova il predecessore
                tmp = predecessor->next;
                predecessor->next = tmp->next; // Rimuove il nodo
                tmp->next = nullptr;
                delete tmp; // Libera la memoria
                size--; // Aggiorna la dimensione
            } 
           return true;
        }
        return false;
    }

    // Verifica se un elemento è presente nel set
    template <typename Data>
    bool SetLst<Data>::Exists(const Data &value) const noexcept {
        ulong pos;
        return BinarySearch(value, pos); // Usa la ricerca binaria
    }

    // Svuota il set
    template <typename Data>
    void SetLst<Data>::Clear() {
       List<Data>::Clear(); // Svuota la lista
    }

    // Ricerca binaria ausiliaria su lista
    template <typename Data>
    bool SetLst<Data>::BinarySearch(const Data &value, ulong &pos) const {
        ulong count = 0;
        Node *tmp = this->head;
        while (tmp) {
            ++count; // Conta i nodi
            tmp = tmp->next;
        }

        long left = 0;
        long right = count - 1;
        while (left <= right) {
            long mid = (left + right) / 2;

            Node *midNode = this->head;
            for (long i = 0; i < mid; ++i)
                midNode = midNode->next; // Scorri fino al nodo mid

            if (midNode->elements == value) {
                pos = mid; // Trovato
                return true;
            }
            else if (midNode->elements < value) {
                left = mid + 1; // Cerca a destra
            }
            else {
                right = mid - 1; // Cerca a sinistra
            }
        }
        pos = left; // Dove inserirlo se non c'è
        return false;
    }

} // namespace lasd