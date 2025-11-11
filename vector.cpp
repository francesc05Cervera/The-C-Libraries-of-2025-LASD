#include "vector.hpp"

namespace lasd {


    /*====================COSTRUTTORI E DISTRUTTORE==================== */

template<typename Data>
Vector<Data>::Vector(const ulong nuova_dimensione)   /*Costruttore con una dimensione inziale*/
{
    size = nuova_dimensione; //la dimensione iniziale viene salvata nella variabile "size" ereditata da Container
    elementi = new Data[size]; //new: funzione per allocare memoria, come in Java. (equivalente di malloc(...) in C)
}

template<typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& Container):Vector<Data>(Container.Size())/*Costruttore da MappableContainer*/
{
    ulong i = 0;
		Container.Map(
			[this, &i](Data& d) {
				std::swap(elementi[i], d);
				i++;
			});
		this->size = i;
}

//la descrizione di questa funzione (costr. TraversableContainer) è la stessa di quella precedente.
template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& Container) /*Costruttore da TraversableContainer*/
{
    size = Container.Size();
    elementi = new Data[size];
    ulong i = 0;
    Container.Traverse([&](const Data& dato){
        elementi[i++] = dato;
    });
}


template<typename Data>
Vector<Data>::Vector(Vector&& other) noexcept  /*Move Costructor*/
{
    std::swap(size, other.size); //swap: funzione della libreria standard. Scambia le dimensioni dei Vector (in questo caso)
    std::swap(elementi, other.elementi); //swap: funzione della libreria standard. Scambia gli elementi dei Vector (in questo caso)
    other.Clear();
};

template<typename Data>
Vector<Data>::Vector(const Vector& other) /*Copy Costructor*/
{
    CopyFrom(other); /*Funzione di copia*/
};


template<typename Data>
Vector<Data>::~Vector()  /*Distruttore (identificato da ~)*/
{
    delete[] elementi; //dealloca memoria (equivalente della funzione free(..) in C)
    elementi = nullptr;
    size = 0; 
};

    /*====================OPERATORI DI ASSEGNAZIONE (= move e copy)  E CONFRONTO (== e !=)==================== */


template<typename Data>
Vector<Data> &Vector<Data>::operator =(Vector && other) noexcept //operatore di assegnazione (MOVE)
{
    std::swap(size, other.size); //vengono scambiate le dimensioni dei due vettori
    std::swap(elementi, other.elementi); //vengono scambiati gli elementi dei due vettori
    return *this;  //ritorna il vettore attuale, non other
};

template<typename Data>
Vector<Data> &Vector<Data>::operator =(const Vector & other) //operaotre di assegnazione (COPY)
{
    if(this != &other){
        Vector<Data> temp(other); //crea un vettore temporaneo "temp" che contiene gli elementi di other
        std::swap(*this, temp);  //scambia gli elementi di this con quelli di temp
    }
        return *this;
};



template<typename Data>
bool Vector<Data>::operator == (const Vector& other)const noexcept //op. confronto (==)  
{
    if (size != other.size) // se le dimensioni non corrispondono, i vettori sono diversi
        return false;

for (ulong i = 0; i < size; i++) {
    if (elementi[i] != other.elementi[i]) //se gli elementi non corrispondono, sono diversi i vettori
        return false;
}
    return true; //se le condizioni degli if non sono soddisfatte, sono uguali
}

template<typename Data>
bool Vector<Data>::operator != (const Vector& other)const noexcept //op. confronto (!=)
{
    return (!(*this == other)); //viene eseguito il NOT della funzione precedente
}

        /*================= ACCESSI (che possono modificare la struttura dati, non const) =================*/

template<typename Data>
Data &Vector<Data>::operator[](ulong i) //op. di accesso in base all'indice "i"
{
    if(i >= size) //se l'indice è maggiore della dimensione genera l'eccezione "out of range"
    {
       throw std::out_of_range("Oltre la dimensione! (out of range)");
    }
       return elementi[i]; //altrimenti restituisce il valore in posizione i
}


template<typename Data>
Data& Vector<Data>::Front() //accesso al primo elemento
{
    if (size == 0) //se il vettore e' vuoto il primo elemento non esiste dunque viene inviata l'eccezione (lenght_error)
        throw std::length_error("VUOTO! (lenght_error)");
    
    return elementi[0]; //altrimenti restituisce il valore in prima posizione (i = 0)
}

template<typename Data>
Data& Vector<Data>::Back() //accesso all'ultimo elemento
{
    if (size == 0) //vedi descr. funz precedente
        throw std::length_error("VUOTO! (lenght_error)");
    
    return elementi[size -1]; //restituisce ultimo elemento
}

        /*================= ACCESSI (che NON possono modificare la struttura dati, const) =================*/

/*le funzioni in quest'area funzionano esattamente come le precedenti solo che hanno il "const", ovvero che non possono apportare 
                                                modifiche alla struttura dati. */

template<typename Data>
const Data& Vector<Data>::Front() const 
{
    if (size == 0)
        throw std::length_error("VUOTO! (lenght_error)");
    
    return elementi[0];
}

template<typename Data>
const Data& Vector<Data>::Back() const{
    if (size == 0)
        throw std::length_error("VUOTO! (lenght_error)");
    
    return elementi[size -1];
}

/* ********************************************************************************************** */

template<typename Data>
const Data &Vector<Data>::operator[](const ulong i) const{
    if(i >= size){
       throw std::out_of_range("Oltre la dimensione (out of range)");
    }
       return elementi[i];
}

template<typename Data>
void Vector<Data>::Resize(const ulong newSize) //funzione di ridimensionamento di un vettore 
{
    Data* newElementi = (newSize > 0) ? new Data[newSize] : nullptr; /* alloca un nuovo array dinamico di tipo DATA solo se la newSize > 0 altrimenti return nullptr*/
    ulong minSize = (size < newSize) ? size : newSize; /*calcola il minimo tra le due dimensioni. Per capire quanti elementi si possono copiare*/

    for(ulong i = 0; i < minSize; i++)
    {
        newElementi[i] = std::move(elementi[i]); //viene effettuata la copia
    }

    delete[] elementi; //deallocazione
    elementi = newElementi; //assegnazione dei nuovi elementi
    size = newSize; //cambiamento del valore size
}


template <typename Data>
void Vector<Data>::Clear() //metodo per pulire un vettore
{
    delete[] elementi; //dealloca gli elementi
    elementi = nullptr;
    size = 0; //gli assegna size = 0
}

template <typename Data>
void Vector<Data>::CopyFrom(const Vector<Data> &other) //copia un vettore in un altro
{
    delete[] elementi;
    size = other.size; //assegnata la dimensione di other al nostro vector

    elementi = new Data[size]; //viene allocato un nuovo array di tipo Data

    for(ulong i = 0; i<size; i++){
        elementi[i] = other.elementi[i]; //vengono messi gli elementi di other in elementi
    }
}

template <typename Data>
SortableVector<Data>::SortableVector(const ulong newSize): Vector<Data>::Vector(newSize) {} //costruttore di default, inizializza un vettore di dimensione newSize
//viene chiamato il costruttore di Vector<Data> con newSize come parametro

template <typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data> & container): Vector<Data>::Vector(container) {} //costruttore di un vettore ottenuto tramite un TraversableContainer
//viene chiamato il costruttore di Vector<Data> con container come parametro

template <typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data> && container): Vector<Data>::Vector(std::move(container)) {} //costruttore di un vettore ottenuto tramite un MappableContainer
//viene chiamato il costruttore di Vector<Data> con container come parametro

template <typename Data>
SortableVector<Data>::SortableVector(const SortableVector& other): Vector<Data>::Vector(other) {} //costruttore di copia
//viene chiamato il costruttore di Vector<Data> con other come parametro

template <typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data> &&other) noexcept: Vector<Data>::Vector(std::move(other)) {} //costruttore di move
//viene chiamato il costruttore di Vector<Data> con other come parametro

template <typename Data>
void SortableVector<Data>::Sort() //metodo di ordinamento
 {
    this->InsertionSort(); //chiamata al metodo di ordinamento
 }
template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& other) noexcept //operatore di assegnamento (MOVE)
{ 
    Vector<Data>::operator=(std::move(other)); //viene chiamato l'operatore di assegnamento di Vector<Data> con other come parametro
    return *this; //ritorna il vettore attuale, non other
}


template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& other)   //operatore di assegnamento (COPY)
{
    Vector<Data>::operator=(other); //viene chiamato l'operatore di assegnamento di Vector<Data> con other come parametro
    return *this; //ritorna il vettore attuale, non other
}



template <typename Data>
void SortableVector<Data>::CopyFrom(const SortableVector &other) //copia un vettore in un altro
//viene chiamato il metodo di copia di Vector<Data> con other come parametro
{
    Vector<Data>::CopyFrom(other);
}

/* ************************************************************************** */

}
