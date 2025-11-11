#include <stdexcept>
#include "linear.hpp"
namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline bool LinearContainer<Data>::operator==(const LinearContainer<Data> &other) const noexcept { // Confronta due contenitori linearmente elemento per elemento
    if (this->Size() != other.Size())
        return false;
    
    for (ulong i = 0; i<this->Size(); i++) {
        if ((*this)[i] != other[i])
            return false;
    }

    return true;
}

template <typename Data>
inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data> &other) const noexcept { // Restituisce vero se i contenitori sono diversi
    return !(*this == other);
}

template <typename Data>
inline const Data &LinearContainer<Data>::Front() const { // Restituisce il primo elemento (eccezione se vuoto)
    if (this->Size() == this->Empty())
        throw std::length_error("Container e` vuoto");
    else
        return (*this)[0];
}

template <typename Data>
inline const Data &LinearContainer<Data>::Back() const { // Restituisce l'ultimo elemento (eccezione se vuoto)
    if (this->Size() == this->Empty())
        throw std::length_error("Container e` vuoto");
    else
        return (*this)[this->Size() - 1];
} 

template <typename Data>
void LinearContainer<Data>::Traverse(TraverseFun fun) const { // Visita tutti gli elementi in pre-ordine
    PreOrderTraverse(fun);
}

template <typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const { // Visita tutti gli elementi dal primo all'ultimo
    for (ulong i = 0; i< this->Size(); i++){
        fun((*this)[i]);
    }
}

template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const { // Visita tutti gli elementi dall'ultimo al primo
    for (long i = static_cast<long>(this->Size())-1; i >= 0; i--){
        fun((*this)[i]);
    }
}

template <typename Data>
Data& MutableLinearContainer<Data>::Front() { // Restituisce riferimento al primo elemento (eccezione se vuoto)
    if (this->Size() == this->Empty())
        throw std::length_error("Container e` vuoto");
    else
        return (*this)[0];
}

template <typename Data>
Data& MutableLinearContainer<Data>::Back(){ // Restituisce riferimento all'ultimo elemento (eccezione se vuoto)
    if (this->Size() == this->Empty())
        throw std::length_error("Container e` vuoto");
    else
        return (*this)[this->Size()-1];
}

template <typename Data>
void MutableLinearContainer<Data>::Map(MapFun fun) { // Applica una funzione a tutti gli elementi in pre-ordine
    PreOrderMap(fun);
}

template <typename Data>
void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) { // Applica una funzione dal primo all'ultimo elemento
    for (ulong i = 0; i < this->Size(); i++){
        fun((*this)[i]);
    }
}

template <typename Data>
void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) { // Applica una funzione dall'ultimo al primo elemento
    for (long i = static_cast<long>(this->Size()) - 1; i >= 0; i--) {
        fun((*this)[i]);
    }
}

template <typename Data>
void SortableLinearContainer<Data>::InsertionSort() 
{ // Ordina il contenitore usando l'insertion sort
    // Si parte dal secondo elemento e si scorre tutto il contenitore
    for (ulong i = 1; i < this->Size(); i++) 
    {
        Data key = (*this)[i]; // Salva il valore corrente da inserire nella posizione corretta
        long j = i - 1;
        // Sposta gli elementi maggiori di key una posizione avanti
        while (j >= 0 && (*this)[j] > key) {
            (*this)[j + 1] = (*this)[j]; // Sposta l'elemento corrente in avanti
            j--;
        }
        // Inserisce key nella posizione corretta trovata
        (*this)[j + 1] = key;
    }
}

}