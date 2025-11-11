#include "setvec.hpp"
#include <stdexcept>
namespace lasd {

// Ricerca binaria su buffer circolare, restituisce true se trovato e pos indica la posizione, altrimenti pos è il punto di inserimento
template <typename Data>
bool SetVec<Data>::BinarySearch(const Data* elem, ulong head, ulong count, ulong cap,
                  const Data& value, ulong& pos) const {
  ulong left = 0;
  ulong right = count;
  while (left < right) { // Ciclo finché non si restringe la ricerca
    ulong mid = (left + right) / 2; // Calcola la posizione centrale
    const Data& midElem = elements[(head + mid) % cap]; // Accede all'elemento centrale considerando il buffer circolare
    if (midElem == value) { // Se trovato
      pos = mid; // Salva la posizione
      return true;
    }
    else if (midElem < value) { // Se il valore cercato è maggiore
      left = mid + 1; // Sposta la ricerca a destra
    }
    else {
      right = mid; // Altrimenti a sinistra
    }
  }
  pos = left; // Se non trovato, pos è il punto di inserimento
  return false;
}

// Distruttore: libera la memoria dell'array dinamico
template <typename Data>
SetVec<Data>::~SetVec() {
  delete[] elements; // Libera la memoria allocata per gli elementi
}

// Costruttore di copia: crea una copia profonda del set
template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& other) {
  head = 0; // Resetta la testa
  numelem = other.numelem; // Copia la capacità
  size = other.size; // Copia la dimensione logica
  if (numelem > 0) {
    elements = new Data[numelem]; // Alloca nuovo array
    for (ulong i = 0; i < size; ++i) {
      elements[i] = other.elements[(other.head + i) % other.numelem]; // Copia ogni elemento rispettando la circolarità
    }
  }
  else {
    elements = nullptr; // Se vuoto, nessun array
  }
}

// Costruttore di move: acquisisce risorse da un altro set
template <typename Data>
SetVec<Data>::SetVec(SetVec&& other) noexcept {
  head = other.head; // Copia la testa
  numelem = other.numelem; // Copia la capacità
  size = other.size; // Copia la dimensione logica
  elements = other.elements; // Prende possesso dell'array
  other.head = 0; // Resetta l'altro oggetto
  other.numelem = 0;
  other.size = 0;
  other.elements = nullptr;
}

// Costruttore da TraversableContainer: inserisce tutti gli elementi del container
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& container) {
  head = 0;
  size = 0;
  numelem = container.Size() > 0 ? container.Size() : 1; // Alloca almeno 1 elemento
  elements = new Data[numelem];
  container.Traverse([this](const Data& d) {
    Insert(d); // Inserisce ogni elemento del container
  });
}

// Costruttore da MappableContainer (rvalue): inserisce tutti gli elementi tramite move
template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& container) {
  head = 0;
  size = 0;
  numelem = container.Size() > 0 ? container.Size() : 1;
  elements = new Data[numelem];
  container.Map([this](Data& d) {
    Insert(std::move(d)); // Inserisce ogni elemento tramite move
  });
}

// Assegnamento di copia: copia profonda del set
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec& other) {
  if (this != &other) { // Evita auto-assegnamento
    delete[] elements; // Libera memoria esistente
    head = 0;
    numelem = other.numelem;
    size = other.size;
    if (numelem > 0) {
      elements = new Data[numelem];
      for (ulong i = 0; i < size; ++i) {
        elements[i] = other.elements[(other.head + i) % other.numelem]; // Copia ogni elemento
      }
    }
    else {
      elements = nullptr;
    }
  }
  return *this;
}

// Assegnamento di move: acquisisce risorse da un altro set
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec&& other) noexcept {
  if (this != &other) { // Evita auto-assegnamento
    delete[] elements; // Libera memoria esistente
    head = other.head;
    numelem = other.numelem;
    size = other.size;
    elements = other.elements;
    other.head = 0;
    other.numelem = 0;
    other.size = 0;
    other.elements = nullptr;
  }
  return *this;
}

// Operatore di uguaglianza: confronta due set elemento per elemento
template <typename Data>
bool SetVec<Data>::operator==(const SetVec& other) const noexcept {
  if (size != other.size) return false; // Se le dimensioni sono diverse, non sono uguali
  for (ulong i = 0; i < size; ++i) {
    if (elements[(head + i) % numelem] != other.elements[(other.head + i) % other.numelem])
      return false; // Se almeno un elemento differisce, non sono uguali
  }
  return true;
}

// Operatore di disuguaglianza: true se i set sono diversi
template <typename Data>
bool SetVec<Data>::operator!=(const SetVec& other) const noexcept {
  return !(*this == other); // Usa l'operatore di uguaglianza
}

// Restituisce il valore minimo (eccezione se vuoto)
template <typename Data>
const Data& SetVec<Data>::Min() const {
  if (size == 0)
    throw std::length_error("Empty set"); // Eccezione se il set è vuoto
  return elements[head]; // Il minimo è sempre in testa
}

// Restituisce e rimuove il minimo (eccezione se vuoto)
template <typename Data>
Data SetVec<Data>::MinNRemove() {
  Data v = Min(); // Prende il minimo
  RemoveMin(); // Lo rimuove
  return v; // Restituisce il valore rimosso
}

// Rimuove il minimo (eccezione se vuoto)
template <typename Data>
void SetVec<Data>::RemoveMin() 
{
  if (size == 0)
    throw std::length_error("Empty set"); // Eccezione se vuoto
  Remove(elements[head]); // Rimuove l'elemento in testa
}

// Restituisce il valore massimo (eccezione se vuoto)
template <typename Data>
const Data& SetVec<Data>::Max() const {
  if (size == 0)
    throw std::length_error("Empty set"); // Eccezione se vuoto
  return elements[(head + size - 1) % numelem]; // Il massimo è in coda
}

// Restituisce e rimuove il massimo (eccezione se vuoto)
template <typename Data>
Data SetVec<Data>::MaxNRemove() {
  Data v = Max(); // Prende il massimo
  RemoveMax(); // Lo rimuove
  return v; // Restituisce il valore rimosso
}

// Rimuove il massimo (eccezione se vuoto)
template <typename Data>
void SetVec<Data>::RemoveMax() {
  if (size == 0)
    throw std::length_error("Empty set"); // Eccezione se vuoto
  Remove(elements[(head + size - 1) % numelem]); // Rimuove l'elemento in coda
}

// Restituisce il predecessore di un valore (eccezione se non esiste)
template <typename Data>
const Data& SetVec<Data>::Predecessor(const Data& value) const {
  ulong pos;
  bool found = BinarySearch(elements, head, size, numelem, value, pos); // Cerca la posizione del valore
  if (!found) {
    if (pos == 0)  // Se il valore sarebbe in testa, non esiste predecessore
        throw std::length_error("No predecessor");
    return elements[(head + pos - 1) % numelem]; // Restituisce il precedente
  }
  if (pos == 0)
    throw std::length_error("No predecessor");
  return elements[(head + pos - 1) % numelem];
}

// Restituisce e rimuove il predecessore di un valore
template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& value) {
  Data p = Predecessor(value); // Trova il predecessore
  Remove(p); // Lo rimuove
  return p; // Restituisce il valore rimosso
}

// Rimuove il predecessore di un valore
template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& value) {
  Data p = Predecessor(value); // Trova il predecessore
  Remove(p); // Lo rimuove
}

// Restituisce il successore di un valore (eccezione se non esiste)
template <typename Data>
const Data& SetVec<Data>::Successor(const Data& value) const {
  ulong pos;
  bool found = BinarySearch(elements, head, size, numelem, value, pos); // Cerca la posizione del valore
  if (!found) {
    if (pos >= size)        // Se il valore sarebbe in coda, non esiste successore
      throw std::length_error("No successor");
    return elements[(head + pos) % numelem]; // Restituisce il successivo
  }
  if (pos + 1 >= size)
    throw std::length_error("No successor");
  return elements[(head + pos + 1) % numelem];
}

// Restituisce e rimuove il successore di un valore
template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& value) {
  Data s = Successor(value); // Trova il successore
  Remove(s); // Lo rimuove
  return s; // Restituisce il valore rimosso
}

// Rimuove il successore di un valore
template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& value) {
  Data s = Successor(value); // Trova il successore
  Remove(s); // Lo rimuove
}

// Inserisce un elemento (se non già presente), restituisce true se inserito
template <typename Data>
bool SetVec<Data>::Insert(const Data& value) {
  ulong pos;
  if (BinarySearch(elements, head, size, numelem, value, pos)) // Se già presente, non inserisce
    return false;
  if (size == numelem) { // Se pieno, raddoppia la capacità
    Resize(numelem == 0 ? 1 : numelem * 2);
  }
  // Sposta gli elementi a destra per fare spazio
  for (ulong i = size; i > pos; --i) {
    elements[(head + i) % numelem] = std::move(elements[(head + i - 1) % numelem]);
  }
  elements[(head + pos) % numelem] = value; // Inserisce il nuovo valore
  ++size; // Aggiorna la dimensione
  return true;
}

// Inserisce un elemento tramite move (se non già presente), restituisce true se inserito
template <typename Data>
bool SetVec<Data>::Insert(Data&& value) noexcept {
  ulong pos;
  if (BinarySearch(elements, head, size, numelem, value, pos))
    return false;
  if (size == numelem) { // Se pieno, raddoppia la capacità
    Resize(numelem == 0 ? 1 : numelem * 2);
  }
  ulong insertPos = (head + pos) % numelem;
  // Sposta gli elementi a destra per fare spazio
  for (ulong i = size; i > pos; --i) {
    elements[(head + i) % numelem] = std::move(elements[(head + i - 1) % numelem]);
  }
  elements[insertPos] = std::move(value); // Inserisce il nuovo valore
  ++size; // Aggiorna la dimensione
  return true;
}

// Rimuove un elemento, restituisce true se rimosso
template <typename Data>
bool SetVec<Data>::Remove(const Data& value) noexcept {
  ulong pos;
  if (!BinarySearch(elements, head, size, numelem, value, pos)) // Se non trovato, non rimuove
    return false;
  // Sposta gli elementi a sinistra per chiudere il "buco"
  for (ulong i = pos; i + 1 < size; ++i) {
    elements[(head + i) % numelem] = std::move(elements[(head + i + 1) % numelem]);
  }
  --size; // Aggiorna la dimensione
  return true;
}

// Accesso in sola lettura all'elemento in posizione i (eccezione se fuori range)
template <typename Data>
const Data& SetVec<Data>::operator[](const ulong i)  const 
{
  if (i >= size)
    throw std::out_of_range("i out of range"); // Eccezione se fuori range
  return elements[(head + i) % numelem]; // Restituisce l'elemento richiesto
}

// Verifica se un elemento è presente nel set
template <typename Data>
bool SetVec<Data>::Exists(const Data& value) const noexcept {
  ulong pos;
  return BinarySearch(elements, head, size, numelem, value, pos); // Restituisce true se trovato
}

// Svuota il set e libera la memoria
template <typename Data>
void SetVec<Data>::Clear() {
  delete[] elements; // Libera la memoria
  elements = nullptr;
  head = 0;
  size = 0;
  numelem = 0;
}

// Modifica la capacità allocata del vettore
template <typename Data>
void SetVec<Data>::Resize(ulong newSize) {
  Data* newEls = nullptr;
  if (newSize > 0) {
    newEls = new Data[newSize]; // Alloca nuovo array
    ulong toCopy = (size < newSize ? size : newSize); // Determina quanti elementi copiare
    for (ulong i = 0; i < toCopy; ++i) {
      newEls[i] = std::move(elements[(head + i) % numelem]); // Copia gli elementi
    }
    size = toCopy; // Aggiorna la dimensione
  }
  else {
    size = 0;
  }
  numelem = newSize; // Aggiorna la capacità
  delete[] elements; // Libera il vecchio array
  elements = newEls; // Aggiorna il puntatore
  head = 0; // Resetta la testa
}

} // namespace lasd