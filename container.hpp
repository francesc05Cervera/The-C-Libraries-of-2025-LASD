#ifndef CONTAINER_HPP 
#define CONTAINER_HPP 

/* ************************************************************************** */
using ulong = unsigned long; //definizione di ulong come unsigned long

namespace lasd
{

  /* ************************************************************************** */

  class Container
  {

  protected:
    ulong size = 0; //dimensione del container
    Container() = default; //costruttore di default
  public:
    virtual ~Container() = default; //distruttore di default
    Container &operator=(const Container &) = delete; //operatore di assegnamento di copia NON disponbile
    Container &operator=(Container &&) noexcept = delete; //operatore di assegnamento di spostamento NON disponbile
    bool operator==(const Container &) const noexcept = delete; //operaotre di confronto di uguaglianza NON disponbile
    bool operator!=(const Container &) const noexcept = delete; //operaotre di confronto di disuguaglianza NON disponbile
    virtual bool Empty() const noexcept //metodo per verificare se il container è vuoto
    {
      return (size == 0); //restituisce true se size è uguale a 0
    } //altrimenti false

    inline virtual ulong Size() const noexcept //metodo per restituire la dimensione del container
    {
      return size; //restituisce la dimensione del container
    }
  };

  /* ************************************************************************** */

  class ClearableContainer : public virtual Container //estendo la classe Container
  {
  public:
    virtual ~ClearableContainer() = default; //distruttore di default
    ClearableContainer &operator=(const ClearableContainer &) = delete; //operatore di assegnamento di copia NON disponbile
    ClearableContainer &operator=(ClearableContainer &&) noexcept = delete; //operatore di assegnamento di spostamento NON disponbile
    bool operator==(const ClearableContainer &) const noexcept = delete; //operatore di confronto di uguaglianza NON disponbile
    bool operator!=(const ClearableContainer &) const noexcept = delete; //operatore di confronto di disuguaglianza NON disponbile
    virtual void Clear() = 0; //metodo virtuale puro per svuotare il container
  };

  /* ************************************************************************** */

  class ResizableContainer : public virtual ClearableContainer //estendo la classe ClearableContainer
  {

  public:
    virtual ~ResizableContainer() = default; //distruttore di default
    ResizableContainer &operator=(const ResizableContainer &) = delete; //operatore di assegnamento di copia NON disponbile
    ResizableContainer &operator=(ResizableContainer &&) noexcept = delete; // operatore di assegnamento di spostamento NON disponbile.
    bool operator==(const ResizableContainer &) const noexcept = delete; //operatore di confronto di uguaglianza NON disponbile.
    bool operator!=(const ResizableContainer &) const noexcept = delete; //operatore di confronto di disuguaglianza NON disponbile.
    virtual void Resize(const ulong) = 0; //metodo virtuale puro per ridimensionare il container


    inline void Clear() override //override del metodo Clear della classe ClearableContainer
    {
      Resize(0); //richiamo il metodo Resize con 0 come parametro
    } //svuoto il container

  };

}

#endif