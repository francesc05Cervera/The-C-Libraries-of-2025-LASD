#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP
#include <functional> //libreria per le funzioni
#include "testable.hpp" 


namespace lasd {


template <typename Data>
class TraversableContainer : virtual public TestableContainer<Data> //estende TestableContainer<Data>
{
public:
   virtual ~TraversableContainer() = default; //distruttore di default  
   TraversableContainer &operator=(const TraversableContainer &) = delete; //copia non disponibile
   TraversableContainer &operator=(TraversableContainer &&) noexcept = delete; //move non disponibile
  bool operator==(const TraversableContainer &) const noexcept = delete; //operatore di confronto di uguaglianza non disponibile
  bool operator!=(const TraversableContainer &) const noexcept = delete; //operatore di confronto di disuguaglianza non disponibile

  using TraverseFun = std::function<void(const Data &)>; 

  virtual void Traverse(TraverseFun) const = 0; // funzione pura virtuale per la traversata del container
  template <typename Accumulator> 
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator>, Accumulator) const; // funzione pura virtuale per la riduzione del container
  // FoldFun<Accumulator> è una funzione che prende un elemento di tipo Data e un accumulatore di tipo Accumulator e restituisce un accumulatore di tipo Accumulator

  bool Exists(const Data &) const noexcept override; //override di TestableContainer
};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : public virtual TraversableContainer<Data> // estende TraversableContainer<Data>
{
public:
  virtual ~PreOrderTraversableContainer() = default; //distruttore di default
  PreOrderTraversableContainer &operator=(const PreOrderTraversableContainer &) = delete; // copia non disponibile
  PreOrderTraversableContainer &operator=(PreOrderTraversableContainer &&) noexcept = delete; //move non disponibile
  bool operator==(const PreOrderTraversableContainer &) const noexcept = delete; //operatore di confronto di uguaglianza non disponibile
  bool operator!=(const PreOrderTraversableContainer &) const noexcept = delete; //operatore di confronto di disuguaglianza non disponibile


  using typename TraversableContainer<Data>::TraverseFun; 

  // type PreOrderTraverse(arguments) specifiers;
  
  virtual void PreOrderTraverse(TraverseFun) const = 0; // funzione pura virtuale per la traversata in pre-ordine del container

    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

    template <typename Accumulator>
    Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const; // funzione pura virtuale per la riduzione in pre-ordine del container
  // FoldFun<Accumulator> è una funzione che prende un elemento di tipo Data e un accumulatore di tipo Accumulator e restituisce un accumulatore di tipo Accumulator

    void Traverse(TraverseFun) const override; //override di TraversableContainer
};


template <typename Data>
class PostOrderTraversableContainer : public virtual TraversableContainer<Data>
{
public:

   virtual ~PostOrderTraversableContainer() = default; //distruttore di default
   PostOrderTraversableContainer &operator=(const PostOrderTraversableContainer &) = delete; //copia non disponibile  
  PostOrderTraversableContainer &operator=(PostOrderTraversableContainer &&) noexcept = delete; //move non disponibile
   bool operator==(const PostOrderTraversableContainer &) const noexcept = delete; //operatore di confronto di uguaglianza non disponibile
   bool operator!=(const PostOrderTraversableContainer &) const noexcept = delete; //operatore di confronto di disuguaglianza non disponibile


  using typename TraversableContainer<Data>::TraverseFun;
  virtual void PostOrderTraverse(TraverseFun) const = 0; // funzione pura virtuale per la traversata in post-ordine del container

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator) const; // funzione pura virtuale per la riduzione in post-ordine del container
  // FoldFun<Accumulator> è una funzione che prende un elemento di tipo Data e un accumulatore di tipo Accumulator e restituisce un accumulatore di tipo Accumulator

  void Traverse(TraverseFun) const override; //override di TraversableContainer
};

}

#include "traversable.cpp" //includo il file cpp per le implementazioni delle funzioni

#endif