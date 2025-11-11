#include "pqheap.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <utility>

namespace lasd 
{

// Tip(): Restituisce il primo elemento (massima priorità)
template <typename Data>
const Data& PQHeap<Data>::Tip() const 
{
    if (this->Empty()) //controlla se la coda a priorità è vuota
    {
        throw std::length_error("La coda a priorità è vuota!"); //se si, lancia un'eccezione
    }
    return elementi[0]; //altrimenti, Restituisce il primo elemento (massima priorità)
}


// RemoveTip(): Rimuove il primo elemento
template <typename Data>
void PQHeap<Data>::RemoveTip() 
{
     if (this->Empty()) //controlla se la coda a priorità è vuota
    {
        throw std::length_error("La coda a priorità è vuota!"); //se si, lancia un'eccezione
    }
    
     std::swap(elementi[0], elementi[size-1]); // Scambia il primo elemento con l'ultimo
     this->Resize(this->size-1); // Riduce la dimensione dell'array sottostante
     // Dopo il resize, l'ultimo elemento non fa più parte dell'heap

     this->HeapifyDown(0); // Ripristina la proprietà dell'heap scendendo
}

// TipNRemove(): Restituisce e rimuove il primo elemento
template <typename Data>
Data PQHeap<Data>::TipNRemove() 
{
    Data tip = Tip(); // Ottiene il primo elemento (massima priorità)
    RemoveTip(); // Rimuove il primo elemento
    return tip; // Restituisce il primo elemento
}

// HeapifyUp(): Ripristina la proprietà dell'heap risalendo
template <typename Data>
void PQHeap<Data>::HeapifyUp(size_t index)  
{
    while (index > 0 && elementi[index] > elementi[(index - 1) / 2]) // Controlla se l'elemento corrente è maggiore del suo genitore
    {
        std::swap(elementi[index], elementi[(index - 1) / 2]); // Scambia l'elemento corrente con il suo genitore
        index = (index - 1) / 2; // Aggiorna l'indice corrente per risalire nell'heap
    }
}

// Insert(): Inserisce un valore nella coda (copia)
template <typename Data>
void PQHeap<Data>::Insert(const Data& value) 
{

       if(capacity == size) //se la capacità è uguale alla dimensione attuale
       {
            this->Resize(size + 1);  // Ridimensiona l'array sottostante per fare spazio al nuovo elemento
         }

        elementi[size] = value; // Inserisce il nuovo elemento alla fine dell'array
        HeapifyUp(size); // Ripristina la proprietà dell'heap risalendo
        size++; // Incrementa la dimensione della coda a priorità
}

// Insert(): Inserisce un valore nella coda (move)
template <typename Data>
void PQHeap<Data>::Insert(Data&& value)
{
     if(capacity == size) //se la capacità è uguale alla dimensione attuale
     {
            this->Resize(size + 1); // Ridimensiona l'array sottostante per fare spazio al nuovo elemento
        }
        elementi[size] = std::move(value); // Inserisce il nuovo elemento alla fine dell'array
        // Utilizza std::move per evitare una copia costosa
        HeapifyUp(size); // Ripristina la proprietà dell'heap risalendo
        size++; // Incrementa la dimensione della coda a priorità
}

 // Change(): Modifica la priorità di un valore (copia)
template <typename Data>
void PQHeap<Data>::Change(ulong idx, const Data& value) 
{
    if (idx >= this->size) throw std::out_of_range("Indice non valido!"); //se l'indice è fuori dai limiti, lancia eccezione
    elementi[idx] = value; // Modifica il valore dell'elemento all'indice specificato
    ReorderPriority(idx); // Riorganizza la priorità dell'elemento modificato
}

/* ************************************************************************** */

// Change(): Modifica la priorità di un valore (move)
template <typename Data>
void PQHeap<Data>::Change(ulong idx, Data&& value) 
{
    if (idx >= this->size) throw std::out_of_range("Indice non valido!"); //se l'indice è fuori dai limiti, lancia eccezione
    elementi[idx] = std::move(value); // Modifica il valore dell'elemento all'indice specificato usando std::move
    // Se value è un rvalue, viene spostato, altrimenti viene copiato
    ReorderPriority(idx); // Riorganizza la priorità dell'elemento modificato
}

// ReorderPriority(): Riorganizza la priorità di un elemento nell'heap
template <typename Data>
void PQHeap<Data>::ReorderPriority(size_t index) 
{
    if (index >= this->size) //se l'indice è fuori dai limiti
    {
        throw std::out_of_range("Indice non valido!"); //lancia un'eccezione
    }
    
    HeapifyUp(index); // Ripristina la proprietà dell'heap risalendo
    this->HeapifyDown(index); // Ripristina la proprietà dell'heap scendendo
}


// Clear(): Svuota la coda a priorità
template <typename Data>
void PQHeap<Data>::Clear() 
{
    HeapVec<Data>::Clear(); // Chiama il metodo Clear della classe base HeapVec<Data>
}


// Sort(): Ordina la coda a priorità
template <typename Data>
void PQHeap<Data>::Sort() 
{
    HeapVec<Data>::Sort(); //chiama il metodo Sort della classe base HeapVec<Data>
}


template <typename Data>
void PQHeap<Data>::HeapifyDown(size_t index)
{
    HeapVec<Data>::HeapifyIndex(index); // Riorganizza l'heap verso il basso a partire dall'indice specificato
}


template <typename Data>
void PQHeap<Data>::Resize(ulong newsize) 
{
    // Resize(): Ridimensiona la capacità dell'array sottostante.
    // Se newsize == 0, imposta la capacità a 2 per evitare problemi di allocazione.
    // Se newsize è più piccolo della dimensione attuale, tronca il numero di elementi.
    
    if (size == 0) { return; } // Se la coda a priorità è vuota, non fa nulla.

    if (newsize == 0) // Se la nuova dimensione richiesta è 0.
    {
        delete[] elementi; // Elimina l'array dinamico per prevenire memory leak.
        elementi = new Data[2]; // Crea un nuovo array con capacità minima di 2.
        size = 0; // Reset della dimensione attuale.
        capacity = 2; // Evita una capacità di 0, che potrebbe causare problemi di allocazione.
        return;
    }

    if (newsize > capacity) // Se la nuova dimensione è maggiore della capacità attuale.
    {
        Data *v = new Data[newsize]; // Alloca un nuovo array più grande.
        
        // Copia i vecchi elementi nel nuovo array.
        for (ulong i = 0; i < size; i++) { v[i] = elementi[i]; }
        
        delete[] elementi; // Libera la memoria precedente per evitare memory leak.
        elementi = v; // Sostituisce l'array precedente con il nuovo.
        capacity = newsize; // Aggiorna la capacità.
    }
    else if (newsize > size && newsize < capacity)
    {
        // Se la nuova dimensione è maggiore della dimensione attuale ma inferiore alla capacità,
        // non serve ridimensionare l'array, quindi semplicemente ritorna.
        return;
    }
    else if (newsize < size && size > (capacity * 0.5))
    {
        // Se la nuova dimensione è minore della dimensione attuale,
        // ma il numero di elementi occupati è ancora superiore al 50% della capacità,
        // allora si riduce solo il valore di `size`, senza riallocare memoria.
        size = newsize;
    }
    else if (newsize < size && size <= (capacity * 0.5))
    {
        // Se la nuova dimensione è minore della dimensione attuale e gli elementi occupano
        // meno della metà della capacità, allora si ridimensiona l'array per ottimizzare la memoria.
        Data *v = new Data[newsize]; // Alloca un nuovo array con capacità ridotta.
        
        // Copia solo i primi `newsize` elementi nel nuovo array.
        for (ulong i = 0; i < newsize; i++) { v[i] = elementi[i]; }
        
        delete[] elementi; // Libera la memoria precedente.
        elementi = v; // Sostituisce l'array con quello ridotto.
        capacity = newsize; // Aggiorna la capacità.
        size = capacity; // Adatta la dimensione per evitare riferimenti errati.
    }
}
 

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) 
{
    ulong i = 0; // Indice per scorrere gli elementi nel nuovo array
    
    delete [] elementi; // Libera la memoria del vecchio array per evitare memory leak
    
    if(other.size > 0) // Se l'altro heap ha elementi, esegui la copia
    {
        Data *v = new Data[other.capacity]; // Alloca un nuovo array con la stessa capacità dell'heap originale
        
        other.Traverse([this, &i, &v](const Data &d) {
            // Funzione lambda per copiare gli elementi dall'altro heap
            v[i] = d; // Assegna l'elemento corrente nel nuovo array
            i++; // Incrementa l'indice
        });

        elementi = v; // Aggiorna il puntatore agli elementi con il nuovo array
    }
    
    // Aggiorna capacità e dimensione per riflettere il nuovo stato dell'heap
    capacity = other.capacity;
    size = other.size;

    return *this; // Restituisce il riferimento all'oggetto corrente
}

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) noexcept  //operatore = (move)
{
    std::swap(elementi, other.elementi); // Scambia i puntatori agli array di elementi per evitare memory leak
    std::swap(size, other.size); // Scambia le dimensioni per evitare memory leak
    std::swap(capacity, other.capacity); // Scambia le capacità per evitare memory leak
    return *this; // Restituisce il riferimento all'oggetto corrente
}


// Costruttore da TraversableContainer
template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& container) : HeapVec<Data>::HeapVec(container) //utilizza il costruttore della classe base HeapVec<Data>
{
capacity = size; //allinea la capacità alla dimensione attuale
}
  
// Costruttore da MappableContainer
template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data>&& container) : HeapVec<Data>::HeapVec(std::move(container)) //utilizza il costruttore della classe base HeapVec<Data>
{
    capacity = size; //allinea la capacità alla dimensione attuale
}

// Costruttore di copia
template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& other)
{
    ulong i = 0;
    if (other.capacity > 0) 
    {
        Data* v = new Data[other.capacity]; // Alloca un nuovo array con la capacità del `other`
        
        other.Traverse([this, &v, &i](const Data& d){
            v[i] = d; // Copia ogni elemento in `v`
            i++; // Incrementa l’indice
        });

        elementi = v; // Aggiorna il puntatore agli elementi
    }
    
    capacity = other.capacity;
    size = other.size;
}


// Costruttore di move
template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data>&& other) noexcept
{
    std::swap(elementi, other.elementi); // Scambia i puntatori agli array di elementi
    std::swap(size, other.size); // Scambia le dimensioni per evitare memory leak
    std::swap(capacity, other.capacity); //scambia la capacità per evitare memory leak
}


}