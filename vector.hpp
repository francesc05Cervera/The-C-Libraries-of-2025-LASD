#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector: public virtual MutableLinearContainer<Data>, public virtual ResizableContainer  //estende MutableLinearContainer<Data>, ResizableContainer 
{
protected:
  using Container::size; //ereditiamo la dimensione del container
  Data *elementi = nullptr; //elementi del vettore
public:

  Vector()=default;   //costruttore di default
  Vector(ulong); //costruttore di un vettore con dimensione specificata
  Vector(MappableContainer<Data>&&); // costruttore di un vettore ottenuto tramite un MappableContainer
  Vector(const TraversableContainer<Data>&); // costruttore di un vettore ottenuto tramite un TraversableContainer

  Vector(Vector&&) noexcept;    // Move constructor
  Vector(const Vector&);   // Copy constructor

  virtual ~Vector(); //distruttore 

  
  Vector& operator = (Vector&&) noexcept;  // Move assignment

  Vector& operator = (const Vector&);  // Copy assignment

  bool virtual operator==(const Vector&) const noexcept;
  bool virtual operator!=(const Vector&) const noexcept;

   Data& operator[](ulong) override; // Override MutableLinearContainer 
  
   Data& Front() override; // Override MutableLinearContainer 

   Data& Back() override; // Override MutableLinearContainer )
  
  const Data& operator[](const ulong) const override; // Override LinearContainer member 
  const Data& Front() const override;  // Override LinearContainer member 

  const Data& Back() const override; // Override LinearContainer member 

  void Resize(const ulong) override;   // Override ResizableContainer member

  void Clear() override; // Override ClearableContainer member

protected:

  void CopyFrom(const Vector<Data> &); //metodo per copiare 1 vettore in un altro

};

/* ************************************************************************** */

template <typename Data>
class SortableVector: public Vector<Data>, public virtual SortableLinearContainer<Data>  {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  // using Container::???;
using Container::size;
using Vector<Data>::elementi;
  // ...

public:
  using Vector<Data>::operator[];
          /*per le descrizioni: vedi classe precedente*/
  
  SortableVector() = default;

  
  SortableVector(const ulong); 
  SortableVector(const TraversableContainer<Data> &);
  SortableVector(MappableContainer<Data> &&); 

  // Copy constructor
  SortableVector(const SortableVector&);

  // Move constructor
  SortableVector(SortableVector<Data>&&) noexcept;


  // Destructor
   ~SortableVector(){}

  // Copy assignment
  SortableVector &operator=(const SortableVector&);

  // Move assignment
  SortableVector &operator=(SortableVector&&) noexcept;

  void Sort() override; //metodo di ordinamento 

protected:

  void CopyFrom(const SortableVector<Data> &); 

};

}

#include "vector.cpp"

#endif
