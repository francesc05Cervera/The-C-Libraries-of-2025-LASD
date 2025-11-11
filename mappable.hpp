#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

#include <functional>
#include "traversable.hpp"

namespace lasd {

template <typename Data>
class MappableContainer : public virtual TraversableContainer<Data> {

private:
  // Sezione privata per eventuali membri futuri

protected:
  // Sezione protetta per eventuali membri futuri

public:
  virtual ~MappableContainer() = default; // Distruttore virtuale

  MappableContainer &operator=(const MappableContainer &) = delete; // Assegnamento di copia disabilitato
  MappableContainer &operator=(const MappableContainer &&) noexcept = delete; // Assegnamento di move disabilitato

  bool operator==(const MappableContainer &) const noexcept = delete; // Operatore di uguaglianza disabilitato
  bool operator!=(const MappableContainer &) const noexcept = delete; // Operatore di disuguaglianza disabilitato

  using MapFun = std::function<void(Data &)>; // Alias per funzione di mappatura

  virtual void Map(MapFun) = 0; // Metodo astratto per applicare una funzione a tutti gli elementi
};

template <typename Data>
class PreOrderMappableContainer : public virtual MappableContainer<Data>, public virtual PreOrderTraversableContainer<Data> {

private:
  // Sezione privata per eventuali membri futuri

protected:
  // Sezione protetta per eventuali membri futuri

public:
  virtual ~PreOrderMappableContainer() = default; // Distruttore virtuale

  PreOrderMappableContainer &operator=(const PreOrderMappableContainer &) = delete; // Assegnamento di copia disabilitato
  PreOrderMappableContainer &operator=(const PreOrderMappableContainer &&) noexcept = delete; // Assegnamento di move disabilitato

  bool operator==(const PreOrderMappableContainer &) const noexcept = delete; // Operatore di uguaglianza disabilitato
  bool operator!=(const PreOrderMappableContainer &) const noexcept = delete; // Operatore di disuguaglianza disabilitato

  using typename MappableContainer<Data>::MapFun; // Alias per funzione di mappatura

  virtual void PreOrderMap(MapFun) = 0; // Metodo astratto per mappatura in pre-ordine

  void Map(MapFun) override; // Ridefinizione del metodo Map per chiamare PreOrderMap
};

template <typename Data>
class PostOrderMappableContainer: public virtual MappableContainer<Data>, public virtual PostOrderTraversableContainer<Data> {

private:
  // Sezione privata per eventuali membri futuri

protected:
  // Sezione protetta per eventuali membri futuri

public:
  virtual ~PostOrderMappableContainer() = default; // Distruttore virtuale

  PostOrderMappableContainer &operator=(const PostOrderMappableContainer &) = delete; // Assegnamento di copia disabilitato
  PostOrderMappableContainer &operator=(const PostOrderMappableContainer &&) noexcept = delete; // Assegnamento di move disabilitato

  bool operator==(const PostOrderMappableContainer &) const noexcept = delete; // Operatore di uguaglianza disabilitato
  bool operator!=(const PostOrderMappableContainer &) const noexcept = delete; // Operatore di disuguaglianza disabilitato

  using typename MappableContainer<Data>::MapFun; // Alias per funzione di mappatura

  virtual void PostOrderMap(MapFun) = 0; // Metodo astratto per mappatura in post-ordine

  void Map(MapFun) override; // Ridefinizione del metodo Map per chiamare PostOrderMap
};

}

#include "mappable.cpp"

#endif