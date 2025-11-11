#ifndef PQHEAP_HPP
#define PQHEAP_HPP
#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"
#include <stdexcept>
#include <iostream>

namespace lasd 
{

template <typename Data>
class PQHeap : virtual public PQ<Data>, public HeapVec<Data> //estendo PQ<Data> e HeapVec<Data>
{

protected:

  using Container::size; //uso la dimensione del container
  using HeapVec<Data>::elementi; //istanza di HeapVec<Data> per accedere agli elementi

  ulong capacity = 0; //capacità
  void ReorderPriority(size_t index); // Riorganizza la priorità
  void HeapifyUp(size_t); // Riorganizza l'heap verso l'alto
  void HeapifyDown(size_t); // Riorganizza l'heap verso il basso
  
public:

  PQHeap() 
  {
    this->size = 0; //inizializza la size a 0
    this->capacity = 2; //e la capacity a un valore minimo di sicurezza
    this->elementi = new Data[this->capacity]; //crea un array dinamico di Data
  }


  PQHeap(const TraversableContainer<Data>&);  //costruttore da TraversableContainer
  PQHeap(MappableContainer<Data>&&); //costruttore da MappableContainer

  PQHeap(const PQHeap&); //costruttore di copia
  PQHeap(PQHeap&&) noexcept; //costruttore di move

  virtual ~PQHeap() = default; //distruttore

  PQHeap& operator=(const PQHeap&); //operatore di copia
  PQHeap& operator=(PQHeap&&) noexcept; //operatore di move

  void Resize(ulong); // Ridimensiona la capacità dell'array sottostante

  const Data& Tip() const override; // Restituisce l'elemento con priorità massima (throw std::length_error se vuoto)
  void RemoveTip() override; // Rimuove l'elemento con priorità massima (throw std::length_error se vuoto)
  Data TipNRemove() override; // Restituisce e rimuove l'elemento con priorità massima (throw std::length_error se vuoto)

  void Insert(const Data&) override; // Inserisce una copia del valore
  void Insert(Data&&) override; // Inserisce il valore tramite move

  void Change(ulong, const Data&) override; // Cambia il valore all'indice specificato (copia)
  void Change(ulong, Data&&) override;      // Cambia il valore all'indice specificato (move)
  void Clear() override; // Svuota il contenitore
  void Sort() override; // Ordina gli elementi 


};


}

#include "pqheap.cpp"

#endif
