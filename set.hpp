#ifndef SET_HPP
#define SET_HPP

#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"
#include "../container/linear.hpp"

namespace lasd 
{

template <typename Data>
class Set: virtual public OrderedDictionaryContainer<Data>, virtual public LinearContainer<Data>, virtual public ClearableContainer 
{


public:
  virtual ~Set() = default; // Distruttore virtuale

  Set &operator=(const Set &) = delete; // Assegnamento di copia disabilitato
  Set &operator=(Set &&) noexcept = delete; // Assegnamento di move disabilitato

};

}

#endif