#ifndef PQ_HPP
#define PQ_HPP
#include "../container/linear.hpp"

namespace lasd 
{

  template <typename Data>
class PQ : virtual public LinearContainer<Data>, virtual public ClearableContainer //estendo LinearContainer<Data> e ClearableContainer
{
public:

  virtual ~PQ() = default; //distruttore

  PQ& operator = (const PQ&) = delete; //operatore di assegnamento di copia disattivato
  PQ& operator=(PQ&&) noexcept = delete; //operatore di assegnamento di spostamento disattivato

  virtual const Data& Tip() const = 0; // Ritorna il valore di priorità più alta (eccezione se vuoto)
  virtual void RemoveTip() = 0; // Rimuove il valore di priorità più alta (eccezione se vuoto)
  virtual Data TipNRemove() = 0; // Ritorna e rimuove il valore di priorità più alta (eccezione se vuoto)

  virtual void Insert(const Data&) = 0; // Inserisce una copia del valore
  virtual void Insert(Data&&) = 0; // Inserisce il valore tramite spostamento

  virtual void Change(ulong, const Data&) { throw std::logic_error("Change(idx, value) non supportato"); } // Cambia il valore all'indice specificato (copia)
  virtual void Change(ulong, Data&&) { throw std::logic_error("Change(idx, value) non supportato"); } // Cambia il valore all'indice specificato (spostamento)

};

}

#endif
