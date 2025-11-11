#ifndef LINEAR_HPP
#define LINEAR_HPP

#include "mappable.hpp"

namespace lasd {

template <typename Data>
class LinearContainer: public virtual PreOrderTraversableContainer<Data>, public virtual PostOrderTraversableContainer<Data> {

private:
  // Sezione privata per eventuali membri futuri

protected:
  // Sezione protetta per eventuali membri futuri

public:
  virtual ~LinearContainer()= default; // Distruttore virtuale

  LinearContainer &operator=(const LinearContainer &) = delete; // Assegnamento di copia disabilitato
  LinearContainer &operator=(const LinearContainer &&) noexcept = delete; // Assegnamento di move disabilitato

  bool operator==(const LinearContainer &) const noexcept; // Operatore di uguaglianza tra contenitori lineari
  bool operator!=(const LinearContainer &) const noexcept; // Operatore di disuguaglianza tra contenitori lineari

  virtual const Data& operator[](const ulong) const = 0; // Accesso in sola lettura all'elemento in posizione data (eccezione se fuori range)
  virtual const Data& Front() const; // Ritorna riferimento costante al primo elemento (eccezione se vuoto)
  virtual const Data& Back() const; // Ritorna riferimento costante all'ultimo elemento (eccezione se vuoto)

  using typename TraversableContainer<Data>::TraverseFun; // Alias per funzione di visita

  void Traverse(TraverseFun) const override; // Visita tutti gli elementi (ordine indefinito)

  void PreOrderTraverse(TraverseFun) const override; // Visita tutti gli elementi in pre-ordine
  void PostOrderTraverse(TraverseFun) const override; // Visita tutti gli elementi in post-ordine
};

template <typename Data>
class MutableLinearContainer: public virtual LinearContainer<Data>, public virtual PreOrderMappableContainer<Data>, public virtual PostOrderMappableContainer<Data>{

private:
  // Sezione privata per eventuali membri futuri

protected:
  // Sezione protetta per eventuali membri futuri

public:
  virtual ~MutableLinearContainer() = default; // Distruttore virtuale

  MutableLinearContainer &operator=(const MutableLinearContainer &) = delete; // Assegnamento di copia disabilitato
  MutableLinearContainer &operator=(const MutableLinearContainer &&) = delete; // Assegnamento di move disabilitato

  virtual Data& operator[](const ulong) = 0; // Accesso in scrittura all'elemento in posizione data (eccezione se fuori range)
  virtual Data& Front(); // Ritorna riferimento al primo elemento (eccezione se vuoto)
  virtual Data& Back(); // Ritorna riferimento all'ultimo elemento (eccezione se vuoto)

  using LinearContainer<Data>::Front;
  using LinearContainer<Data>::Back;
  using LinearContainer<Data>::operator[];

  using typename MappableContainer<Data>::MapFun; // Alias per funzione di mappatura

  void Map(MapFun) override; // Applica una funzione a tutti gli elementi (ordine indefinito)
  void PreOrderMap(MapFun) override; // Applica una funzione a tutti gli elementi in pre-ordine
  void PostOrderMap(MapFun) override; // Applica una funzione a tutti gli elementi in post-ordine
};
template <typename Data>
class SortableLinearContainer: public virtual MutableLinearContainer<Data> 
{
public:
  virtual ~SortableLinearContainer() = default; // Distruttore virtuale

  SortableLinearContainer &operator=(const SortableLinearContainer &) = delete; // Assegnamento di copia disabilitato
  SortableLinearContainer &operator=(const SortableLinearContainer &&) noexcept = delete; // Assegnamento di move disabilitato

  virtual void Sort() = 0; // Metodo astratto per ordinare il contenitore

protected:
  virtual void InsertionSort(); // Metodo protetto per ordinamento tramite insertion sort
};

}

#include "linear.cpp"

#endif