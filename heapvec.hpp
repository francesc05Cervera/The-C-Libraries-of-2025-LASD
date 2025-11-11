#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP
#include "../heap.hpp"
#include "../../vector/vector.hpp"

namespace lasd 
{

template <typename Data>
class HeapVec : virtual public Heap<Data>, public SortableVector<Data> //Estende Heap<Data> e SortableVector<Data>
{
private:

  using Container::size; //utilizza la dimensione del container

protected:
  using SortableVector<Data>::elementi; //utilizza gli elementi del SortableVector<Data>

public:
   
  HeapVec() { this->size = 0; this->elementi = nullptr; } //costruttore di default esplicito

  HeapVec(const TraversableContainer<Data>&); //costruttore da TraversableContainer
  HeapVec(MappableContainer<Data>&); //costruttore da MappableContainer

  HeapVec(const HeapVec&); //copy constructor
  HeapVec(HeapVec&&) noexcept; //move constructor

  virtual ~HeapVec() = default; //distruttore 

  HeapVec& operator = (const HeapVec&); //operatore di assegnamento di copia

  HeapVec& operator = (HeapVec&&) noexcept; //operatore di assegnamento di spostamento

  using Vector<Data>::operator==; //utilizzo l'operatore di uguaglianza della classe Vector<Data>
  using Vector<Data>::operator!=; //utilizzo l'operatore di disuguaglianza della classe Vector<Data>


  bool IsHeap() const override; //Override IsHeap 
  void Heapify() override; //Override Heapify
  void Sort() override; //per Heap Sort utilizza il metodo Sort della classe SortableVector<Data>
  using Vector<Data>::Clear; //utilizzo il metodo Clear della classe Vector<Data>
  void HeapifyIndex(size_t index);
};

}

#include "heapvec.cpp"

#endif
