#ifndef TESTABLE_HPP
#define TESTABLE_HPP

#include "container.hpp"

namespace lasd
{

  template <typename Data>
  class TestableContainer: public virtual Container
  {
  public:
    virtual ~TestableContainer() = default; // Distruttore virtuale

    TestableContainer &operator=(const TestableContainer &) = delete; // Assegnamento di copia disabilitato
    TestableContainer &operator=(TestableContainer &&) noexcept = delete; // Assegnamento di move disabilitato

    bool operator==(const TestableContainer &) const noexcept = delete; // Operatore di uguaglianza disabilitato
    bool operator!=(const TestableContainer &) const noexcept = delete; // Operatore di disuguaglianza disabilitato

    virtual bool Exists(const Data&) const noexcept = 0; // Metodo astratto: verifica presenza elemento
  };

}

#endif