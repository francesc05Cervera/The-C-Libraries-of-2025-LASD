#ifndef SETVEC_HPP
#define SETVEC_HPP

#include "../set.hpp"
#include "../../vector/vector.hpp"

namespace lasd
{

  template <typename Data>
  class SetVec : public virtual Set<Data>, public virtual ResizableContainer {

  private:
    // Sezione privata per eventuali membri futuri

  protected:
    ulong head=0; // Indice di testa (non usato in SetVec, ma lasciato per compatibilità)
    ulong numelem=0; // Numero di elementi effettivi nel set
    using Container::size; // Alias per la dimensione logica del contenitore
    Data* elements=nullptr; // Puntatore all'array degli elementi

  public:
    SetVec() =default; // Costruttore di default

    SetVec(const TraversableContainer<Data> &); // Costruttore da contenitore traversabile
    SetVec(MappableContainer<Data> &&); // Costruttore da contenitore mappabile (move)

    SetVec(const SetVec &); // Costruttore di copia
    SetVec(SetVec &&) noexcept; // Costruttore di move

    virtual ~SetVec(); // Distruttore

    SetVec &operator=(const SetVec &); // Assegnamento di copia
    SetVec &operator=(SetVec &&) noexcept; // Assegnamento di move

    bool operator==(const SetVec &) const noexcept; // Operatore di uguaglianza
    bool operator!=(const SetVec &) const noexcept; // Operatore di disuguaglianza

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
    bool Remove(const Data &) noexcept override; // Rimuove il dato, restituisce true se rimosso

    const Data& operator[](const ulong) const override; // Accesso in sola lettura all'elemento in posizione data (eccezione se fuori range)

    bool Exists(const Data &) const noexcept override; // Verifica se un elemento è presente nel set

    void Clear() override; // Svuota il set

    void Resize(ulong) override; // Modifica la dimensione allocata del vettore

    inline ulong Size() const noexcept override { return size; }; // Restituisce la dimensione logica del set

    inline bool Empty() const noexcept override { return (size==0); }; // Verifica se il set è vuoto
 
  protected:
    bool BinarySearch(const Data* , ulong, ulong, ulong, const Data&, ulong&) const; // Ricerca binaria ausiliaria
  };

}

#include "setvec.cpp"

#endif