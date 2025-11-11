
#ifndef HEAP_HPP
#define HEAP_HPP
#include "../container/linear.hpp"

namespace lasd 
{
template <typename Data>
class Heap : virtual public SortableLinearContainer<Data>, virtual public ClearableContainer //estendo da SortableLinearContainer e ClearableContainer
{
private:
  //No mebri privati
protected:
  // No membri protetti
public:

  virtual ~Heap() = default; //distruttore di default virtuale

  Heap& operator = (const Heap&) = delete; //L'assegnamento di copia non è disponibile

  Heap& operator = (Heap&&) noexcept = delete; //L'assegnamento di spostamento non è disponibile

  virtual bool IsHeap() const =0; //Verifica se il contenitore è un heap

  virtual void Heapify() =0; // Trasforma il contenitore in un heap

};

}

#endif
