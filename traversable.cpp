namespace lasd { // Inizio dello spazio dei nomi lasd

    // Metodo Exists: verifica se un elemento è presente nel contenitore
    template <typename Data>
    inline bool TraversableContainer<Data>::Exists(const Data& Value) const noexcept 
    {
      bool Found = false; // Variabile per tracciare se l'elemento è stato trovato
      Traverse([&Found,Value](const Data& Element) 
      { // Funzione lambda per la traversata
        if (Element == Value) // Se l'elemento corrente è uguale a quello cercato
          Found = true; // Segna come trovato
      });
      return Found; // Ritorna true se trovato, altrimenti false
    }
    
    // Metodo Fold: applica una funzione di folding a tutti gli elementi del contenitore
    template <typename Data>
    template <typename Accumulator>
    inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const
    {
        Traverse([fun, &acc](const Data &Element) { // Lambda che applica la funzione di folding
              acc=fun(Element,acc); // Aggiorna l'accumulatore con il risultato della funzione
          });
          return acc; // Ritorna il valore accumulato
    }
    
    // Metodo Traverse per PreOrderTraversableContainer: esegue una traversata in pre-ordine
    template <typename Data>
    void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun)const
    {
        PreOrderTraverse(fun); // Chiama la funzione di traversata in pre-ordine
    }
    
    // Metodo PreOrderFold: folding in pre-ordine
    template <typename Data>
    template <typename Accumulator>
    Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
        PreOrderTraverse([fun, &acc](const Data& Element) 
        { // Lambda per la traversata in pre-ordine
            acc=fun(Element,acc); // Aggiorna l'accumulatore
        });
        return acc; // Ritorna il valore accumulato
    }
    
    // Metodo Traverse per PostOrderTraversableContainer: esegue una traversata in post-ordine
    template <typename Data>
    void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun)const
    {
        PostOrderTraverse(fun); // Chiama la funzione di traversata in post-ordine
    }
    
    // Metodo PostOrderFold: folding in post-ordine
    template <typename Data>
    template <typename Accumulator>
    Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
        PostOrderTraverse([&](const Data& Element) 
        { // Lambda per la traversata in post-ordine
            acc=fun(Element,acc); // Aggiorna l'accumulatore
        });
        return acc; // Ritorna il valore accumulato
    }
    
}