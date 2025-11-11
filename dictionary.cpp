namespace lasd {

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &container) { // Inserisce tutti gli elementi da un altro contenitore, restituisce true se tutti inseriti
    bool Inserimento_Completato = true;
    container.Traverse([this, &Inserimento_Completato](const Data& Dato){
        if(!this->Insert(Dato))
            Inserimento_Completato = false;
    });
    return Inserimento_Completato;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&container) noexcept { // Inserisce tutti gli elementi tramite move, restituisce true se tutti inseriti
    bool Inserimento_Completato = true;
    container.Map([this, &Inserimento_Completato](const Data& Dato){
        if(!this->Insert(std::move(Dato)))
            Inserimento_Completato = false;
    });
    return Inserimento_Completato;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &container) { // Rimuove tutti gli elementi presenti in un altro contenitore, restituisce true se tutti rimossi
    bool Rimozione_Completata = true;
    container.Traverse([this, &Rimozione_Completata](const Data& Dato){
        if(!this->Remove(Dato))
            Rimozione_Completata = false;
    });
    return Rimozione_Completata;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &container) { // Inserisce almeno un elemento da un altro contenitore, restituisce true se almeno uno inserito
    bool Alcuni_Inseriti = false;
    container.Traverse([this, &Alcuni_Inseriti](const Data& Dato){
        if(this->Insert(Dato))
            Alcuni_Inseriti = true;
    });
    return Alcuni_Inseriti;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&container) noexcept { // Inserisce almeno un elemento tramite move, restituisce true se almeno uno inserito
    bool Alcuni_Inseriti = false;
    container.Traverse([this, &Alcuni_Inseriti](const Data& Dato){
        if(this->Insert(std::move(Dato)))
            Alcuni_Inseriti = true;
    });
    return Alcuni_Inseriti;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &container) { // Rimuove almeno un elemento presente in un altro contenitore, restituisce true se almeno uno rimosso
    bool Alcuni_Rimossi = false;
    container.Traverse([this, &Alcuni_Rimossi](const Data& Dato){
        if(this->Remove(Dato))
            Alcuni_Rimossi = true;
    });
    return Alcuni_Rimossi;
}

}