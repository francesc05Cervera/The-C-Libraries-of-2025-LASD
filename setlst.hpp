#ifndef SETLST_HPP
#define SETLST_HPP

#include "../set.hpp"
#include "../../list/list.hpp"

namespace lasd
{

  template <typename Data>
  class SetLst : virtual public Set<Data>, virtual public List<Data>
  {

  private:
    // Sezione privata per eventuali membri futuri

  protected:
    using List<Data>::size;
    using List<Data>::head;
    using List<Data>::tail;
    using typename List<Data>::Node;

  public:
    SetLst() = default; // Costruttore di default

    SetLst(const TraversableContainer<Data> &); // Costruttore da TraversableContainer
    SetLst(MappableContainer<Data> &&) noexcept; // Costruttore da MappableContainer (move)

    SetLst(const SetLst &); // Costruttore di copia
    SetLst(SetLst &&) noexcept; // Costruttore di move

    ~SetLst(){ List<Data>::Clear(); } // Distruttore: svuota la lista

    SetLst &operator=(const SetLst &); // Assegnamento di copia
    SetLst &operator=(SetLst &&) noexcept; // Assegnamento di move

    bool operator==(const SetLst &) const noexcept; // Operatore di uguaglianza
    bool operator!=(const SetLst &) const noexcept; // Operatore di disuguaglianza

    const Data &Min() const override; // Restituisce il minimo (eccezione se vuoto)
    Data MinNRemove() override; // Restituisce e rimuove il minimo (eccezione se vuoto)
    void RemoveMin() override; // Rimuove il minimo (eccezione se vuoto)

    const Data &Max() const override; // Restituisce il massimo (eccezione se vuoto)
    Data MaxNRemove() override; // Restituisce e rimuove il massimo (eccezione se vuoto)
    void RemoveMax() override; // Rimuove il massimo (eccezione se vuoto)

    const Data &Predecessor(const Data &) const override; // Restituisce il predecessore (eccezione se non trovato)
    Data PredecessorNRemove(const Data &) override; // Restituisce e rimuove il predecessore (eccezione se non trovato)
    void RemovePredecessor(const Data &) override; // Rimuove il predecessore (eccezione se non trovato)

    const Data &Successor(const Data &) const override; // Restituisce il successore (eccezione se non trovato)
    Data SuccessorNRemove(const Data &) override; // Restituisce e rimuove il successore (eccezione se non trovato)
    void RemoveSuccessor(const Data &) override; // Rimuove il successore (eccezione se non trovato)

    bool Insert(const Data &) override; // Inserisce una copia del dato, restituisce true se inserito
    bool Insert(Data &&) noexcept override; // Inserisce il dato tramite move, restituisce true se inserito
    bool Remove(const Data &) override; // Rimuove il dato, restituisce true se rimosso

    using List<Data>::operator[]; // Accesso agli elementi tramite operatore []

    bool Exists(const Data &) const noexcept override; // Verifica se un elemento è presente nel set

    void Clear() override; // Svuota il set

  protected:
    bool BinarySearch(const Data&, ulong&) const; // Ricerca binaria ausiliaria

  };

}

#include "setlst.cpp"

#endif