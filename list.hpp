#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class List : virtual public MutableLinearContainer<Data>, virtual public ClearableContainer //estende MutableLinearContainer<Data> e ClearableContainer
  {
  protected:
    using Container::size; //prendo in eredità la dimensione del container

    struct Node
    {
      /*un nodo è composto da una parte contenente il dato (int, float, double, string .....) e da 
      una seconda parte contenente il linker al nodo successivo che di norma deve essere inizializzato
      a NULL (in c++: nullptr) visto che il primo nodo è sia quello di testa che di coda (quindi non ha successore)*/

      Data elements; //questo è l'elemento del nodo

      Node *next = nullptr; //link al successore

      Node(Data &&) noexcept; //costruttore

      Node(const Data &); //costruttore
      
      /* ********************************************************************** */

      
      Node(Node &&) noexcept; // Move constructor
      
   
      Node(const Node &);    // Copy constructor

      virtual ~Node() = default; //distruttore node di default
      
       bool operator==(const Node &) const noexcept; //op. comparazione ==

      bool operator!=(const Node &) const noexcept; //op. comparazione !=
    };
    Node *head = nullptr;
    Node *tail = nullptr;

  public:
   
    List() = default; //costruttore di default 

    /* ************************************************************************ */

    // Specific constructor
    List(const TraversableContainer<Data> &); //costruttore di una lista ottenuta da un TraversableContainer
    
    List(MappableContainer<Data> &&) noexcept; //costruttore di una lista ottenuta da un Mappable

    /* ************************************************************************ */

    // Copy constructor
  List(const List &);

    // Move constructor
    List(List &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~List() 
    {
      Node *tmp = head; //inizializzo un puntatore temporaneo al nodo di testa
		  while(tmp != nullptr) //finchè il nodo temporaneo non è nullo
      //scorro la lista e cancello i nodi uno alla volta
      {
			  Node *tmp1 = tmp; //creo un secondo puntatore temporaneo che punta al nodo corrente
			  tmp = tmp->next; //sposto il puntatore temporaneo al nodo successivo
			  delete tmp1; //cancello il nodo corrente
		  }
      //una volta cancellati tutti i nodi, inizializzo i puntatori di testa e coda a nullptr
		  head = nullptr;
		  tail = nullptr;
      size = 0; //e la size a 0
    }

    List &operator=(const List &);     // Copy assignment

    List &operator=(List &&) noexcept;     // Move assignment

    bool operator==(const List &) const noexcept; //operatore di confronto di uguaglianza
    bool operator!=(const List &) const noexcept; //operatore di confronto di disuguaglianza

    virtual void InsertAtFront(const Data &); //inserimento in testa per copia
  
    virtual void InsertAtFront(Data &&); //stessa cosa, per move

    virtual void RemoveFromFront(); //rimozione dalla testa

    virtual Data FrontNRemove(); //rimozione dalla testa restituendo il dato

    virtual void InsertAtBack(const Data &); //inserimento in coda per coda

    virtual void InsertAtBack(Data &&); //inserimento in coda per move

    virtual void RemoveFromBack(); //rimozione dalla coda

    virtual Data BackNRemove(); //rimozione dalla coda restituendo il dato

    // Specific member functions (inherited from MutableLinearContainer)

    Data &operator[](ulong) override; // Override MutableLinearContainer member. Accesso all'elemento per indice 

    Data &Front() override;  // Override MutableLinearContainer member. Accesso al primo elemento

    Data &Back() override; // Override MutableLinearContainer member. Accesso all'ultimo elemento

    const Data &operator[](ulong) const override; // Override LinearContainer member
    const Data &Front() const override; // Override LinearContainer member
    const Data &Back() const override; // Override LinearContainer member

    using typename MappableContainer<Data>::MapFun;

    void Map(MapFun) override;  // Override MappableContainer member

    void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

    void PostOrderMap(MapFun) override;  // Override PostOrderMappableContainer member

    using typename TraversableContainer<Data>::TraverseFun;

    void Traverse(TraverseFun) const override; // Override TraversableContainer member

    void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

    void PostOrderTraverse(TraverseFun) const override;    // Override PostOrderTraversableContainer member

    void Clear() override; // Override ClearableContainer member

  protected:
  
    void CopyFrom(const List &); //copia di una lista
    void MoveFrom(List &&) noexcept; //move di una lista
  };

}

#include "list.cpp" //includo il file cpp per la definizione delle funzioni

#endif