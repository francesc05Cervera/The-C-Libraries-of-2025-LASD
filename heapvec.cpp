#include "heapvec.hpp"
namespace lasd 
{

    /*============COSTRUTTORI============*/

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& con) : SortableVector<Data>(con) 
{
    /*Costruttore da un TraversableContainer, utilizzo il costruttore di SortableVector e richiamo la Heapify per costruire l'Heap*/
  Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>& con) : SortableVector<Data>(con) 
{
    /*Costruttore da un MappableContainer, utilizzo il costruttore di SortableVector e richiamo la Heapify per costruire l'Heap*/
  Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& other) : SortableVector<Data>(other) {} //costruttore di copy

template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& other) noexcept : SortableVector<Data>(std::move(other)) {} //costruttore di move

    /*========== OPERATORI "=" ==========*/

template<typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& other) 
{
        SortableVector<Data>::operator=(other); //utilizzo l'operatore = (copy) del SortableVector<Data>

        return *this; // ritorno l'oggetto corrente
}

template<typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& other) noexcept {
     SortableVector<Data>::operator=(std::move(other)); //utilizzo l'operatore = (move) del SortableVector<Data>
     // In questo caso non è necessario gestire la dimensione o gli elementi, poiché SortableVector<Data> lo fa già.
     // Gli elementi sono già stati spostati e la dimensione è stata aggiornata.
     // Non è necessario fare altro, poiché gli elementi sono stati spostati correttamente.

     return *this; //ritorno l'oggetto corrente
}

    /*==========METODI isHeap AND Heapify==========*/
template <typename Data>
bool HeapVec<Data>::IsHeap() const // Metodo che verifica se il contenitore è un heap
{
    // Itera solo fino a metà dell'array, perché ogni nodo a partire dalla seconda metà
    // non ha figli (in un heap completo, i nodi foglia iniziano da size/2).
    for (size_t i = 0; i < size / 2; i++) 
    {
        // Calcola gli indici dei figli sinistro e destro nel vettore
        size_t left = (2 * i) + 1;
        size_t right = (2 * i) + 2;

        // Controlla se il nodo padre è maggiore dei suoi figli, rispettando la proprietà di Max-Heap.
        // Se uno dei figli esiste e ha un valore maggiore del nodo corrente, allora non è un heap.
        if ((left < size && elementi[i] < elementi[left]) || (right < size && elementi[i] < elementi[right])) 
        {
            return false; // Se la proprietà di heap non è rispettata, restituisce false
        }
    }

    return true; // Se il ciclo termina senza violazioni, il contenitore è un heap valido
}


template <typename Data>
void HeapVec<Data>::Heapify() // Metodo che trasforma il contenitore in un heap
{
        // Itera dalla metà dell'array fino all'inizio, eseguendo il processo di heapify su ogni nodo
        for (size_t i = size / 2; i > 0; i--) 
       {
            HeapifyIndex(i - 1); // Applica heapify al nodo corrente
        }
}

    /*FUNZIONI AUSILIARIE*/

template <typename Data>
void HeapVec<Data>::HeapifyIndex(size_t index) 
{
    // Inizializza il nodo corrente come il più grande
    size_t largest = index;
    // Calcola gli indici dei figli sinistro e destro
    size_t left = (2 * index) + 1;
    size_t right = (2 * index) + 2;

    // Controlla se il figlio sinistro esiste e ha un valore maggiore del nodo corrente
    if (left < size && elementi[left] > elementi[largest]) {
        largest = left;
    }

    // Controlla se il figlio destro esiste e ha un valore maggiore del nodo corrente o del sinistro
    if (right < size && elementi[right] > elementi[largest]) {
        largest = right;
    }

    // Se uno dei figli ha un valore maggiore del nodo corrente, scambia i valori e richiama ricorsivamente
    if (largest != index) {
        std::swap(elementi[index], elementi[largest]); // Swap tra nodo e figlio più grande
        HeapifyIndex(largest); // Richiama ricorsivamente per mantenere proprietà dell'heap
    }
}


    /*==========OVERRIDE SORT==========*/

   template <typename Data>
    void HeapVec<Data>::Sort() {
    // Ricostruisci l'heap (se non già heap)
    Heapify();

    // HeapSort vero e proprio
    for (size_t i = size; i > 1; --i) {
        // Scambia il massimo (in cima) con l'ultimo elemento non ordinato
        std::swap(elementi[0], elementi[i - 1]);
        // "Abbassa" la dimensione logica dell'heap temporaneamente
        size_t oldSize = size;
        size = i - 1;
        // Ripristina la proprietà di heap sulla radice
        HeapifyIndex(0);
        // Ripristina la dimensione logica per il prossimo ciclo
        size = oldSize;
    }
}
}

