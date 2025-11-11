#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "testable.hpp"
#include "mappable.hpp"

namespace lasd {

template <typename Data>
class DictionaryContainer: public virtual TestableContainer<Data> 
{

public:
  virtual ~DictionaryContainer() = default; // Distruttore virtuale

  DictionaryContainer &operator=(const DictionaryContainer &) = delete; // Assegnamento di copia disabilitato
  DictionaryContainer &operator=(const DictionaryContainer &&) noexcept = delete; // Assegnamento di move disabilitato

  bool operator==(const DictionaryContainer &) const noexcept = delete; // Operatore di uguaglianza disabilitato
  bool operator!=(const DictionaryContainer &) const noexcept = delete; // Operatore di disuguaglianza disabilitato

  virtual bool Insert(const Data&) = 0; // Inserisce una copia del dato, restituisce true se inserito
  virtual bool Insert(Data&&) = 0; // Inserisce il dato tramite move, restituisce true se inserito
  virtual bool Remove(const Data &) = 0; // Rimuove il dato, restituisce true se rimosso

  virtual bool InsertAll(const TraversableContainer<Data> &); // Inserisce tutti gli elementi da un altro contenitore, restituisce true se tutti inseriti
  virtual bool InsertAll(MappableContainer<Data> &&) noexcept; // Inserisce tutti gli elementi tramite move, restituisce true se tutti inseriti
  virtual bool RemoveAll(const TraversableContainer<Data> &); // Rimuove tutti gli elementi presenti in un altro contenitore, restituisce true se tutti rimossi

  virtual bool InsertSome(const TraversableContainer<Data> &); // Inserisce almeno un elemento da un altro contenitore, restituisce true se almeno uno inserito
  virtual bool InsertSome(MappableContainer<Data> &&) noexcept; // Inserisce almeno un elemento tramite move, restituisce true se almeno uno inserito
  virtual bool RemoveSome(const TraversableContainer<Data> &); // Rimuove almeno un elemento presente in un altro contenitore, restituisce true se almeno uno rimosso
};

template <typename Data>
class OrderedDictionaryContainer: public virtual DictionaryContainer<Data> 
{

public:
  virtual ~OrderedDictionaryContainer()= default; // Distruttore virtuale

  OrderedDictionaryContainer &operator=(const OrderedDictionaryContainer &) = delete; // Assegnamento di copia disabilitato
  OrderedDictionaryContainer &operator=(const OrderedDictionaryContainer &&) noexcept = delete; // Assegnamento di move disabilitato

  bool operator==(const OrderedDictionaryContainer &) const noexcept = delete; // Operatore di uguaglianza disabilitato
  bool operator!=(const OrderedDictionaryContainer &) const noexcept = delete; // Operatore di disuguaglianza disabilitato

  virtual const Data& Min() const = 0; // Restituisce il minimo (eccezione se vuoto)
  virtual Data MinNRemove() = 0; // Restituisce e rimuove il minimo (eccezione se vuoto)
  virtual void RemoveMin() = 0; // Rimuove il minimo (eccezione se vuoto)

  virtual const Data& Max() const = 0; // Restituisce il massimo (eccezione se vuoto)
  virtual Data MaxNRemove() = 0; // Restituisce e rimuove il massimo (eccezione se vuoto)
  virtual void RemoveMax() = 0; // Rimuove il massimo (eccezione se vuoto)

  virtual const Data& Predecessor(const Data&) const = 0; // Restituisce il predecessore (eccezione se non trovato)
  virtual Data PredecessorNRemove(const Data&) = 0; // Restituisce e rimuove il predecessore (eccezione se non trovato)
  virtual void RemovePredecessor(const Data&) = 0; // Rimuove il predecessore (eccezione se non trovato)

  virtual const Data& Successor(const Data&) const = 0; // Restituisce il successore (eccezione se non trovato)
  virtual Data SuccessorNRemove(const Data&) = 0; // Restituisce e rimuove il successore (eccezione se non trovato)
  virtual void RemoveSuccessor(const Data&) = 0; // Rimuove il successore (eccezione se non trovato)

  virtual bool Remove(const Data &) = 0; // Rimuove il dato, restituisce true se rimosso
};

}

#include "dictionary.cpp"

#endif