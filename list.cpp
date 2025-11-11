#include "list.hpp"
#include <stdexcept>
namespace lasd
{

    /* ================================== COSTRUTTORI E DISTRUTTORE (Node) ================================== */

    template <typename Data>
    List<Data>::Node::Node(Data &&newElements) noexcept   /*Move Constructor*/
    {
        std::swap(elements, newElements); /*Scambia i valori di elements e newElements*/
    }

    template <typename Data>
    List<Data>::Node::Node(const Data &newElements) /*Copy Constructor*/
    {
        elements = newElements;
    }

  
    template <typename Data>
    List<Data>::Node::Node(Node &&newNode) noexcept
    {
        std::swap(elements, newNode.elements);
        std::swap(next, newNode.next);
    }

    template <typename Data>
    List<Data>::Node::Node(const Node & newNode)
    {
        elements = newNode.elements;
        next = newNode.next;
    }


    /* ================================== OPERATORI DI COMPARAZIONE E ASSEGNAZIONE (Node)================================== */

    template <typename Data>
    inline bool List<Data>::Node::operator==(const Node &other) const noexcept /*op. == Nodi*/
    {
        return (other.elements==elements); /*restituisce TRUE se sono uguali gli elementi*/
    }

    template <typename Data>
    inline bool List<Data>::Node::operator!=(const Node &other) const noexcept /*op. != Nodi*/
    {
        return !(other.elements == elements); /*restituisce TRUE se sono diversi gli elementi*/
    }

     /* ================================== COSTRUTTORI E DISTRUTTORE (List) ================================== */
    template <typename Data>
    List<Data>::List(const TraversableContainer<Data> &container) /*Costruttore da un TraversableContainer*/
    {
        container.Traverse(
            [this](const Data &val) 
            { 
                InsertAtBack(val); /*prende il valore e lo inserisce in coda nella Lista*/
            });
    }

    template <typename Data>
    List<Data>::List(MappableContainer<Data> &&container) noexcept /*Costruttore da un MappableContainer*/
    {
        if(container.Size() > 0){
        container.Map(
            [this](Data &val)
            {
                InsertAtBack(std::move(val)); //prende il valore e lo inserisce in coda nella Lista
            });

            size = container.Size();
		}else{
		   size = 0;
		   head = nullptr;
		   tail = nullptr;
		}
    }

    template <typename Data>
    List<Data>::List(const List<Data> &other)
    {
        CopyFrom(other); //copia una lista in un altra
    }

    template <typename Data>
    List<Data>::List(List<Data> &&other) noexcept
    {
        std::swap(head, other.head);
		std::swap(tail, other.tail);
		std::swap(size, other.size);
    }

     /* ================================== OPERATORI DI CONFRONTO E ASSEGNAMENTO (List) ================================== */
    template <typename Data>
    List<Data> &List<Data>::operator=(const List &other)
    {
        if (this != &other) //se le due liste sono diverse
        {
            Clear(); //viene pulita una lista
            CopyFrom(other); //...e viene copiata
        }
        return *this; //ritorna la lista
    }

    template <typename Data>
    List<Data> &List<Data>::operator=(List &&other) noexcept
    {
        MoveFrom(std::move(other));
        return *this;
    }

    template <typename Data>
    bool List<Data>::operator==(const List &other) const noexcept //op. == tra liste
    {

        Node* tmp1= head; //viene salvato il nodo di testa della prima list
        Node* tmp2= other.head; //viene salvato il nodo di testa della seconda lista

        if (size != other.size) //viene controllato se la dimensione è diversa
            return false; //... se lo è allora le liste sono diverse

        for (ulong i=0; i < size; i++) //si scorrono le liste per verificare nodo per nodo
            {
                if (!(tmp1->elements == tmp2->elements)) //se i nodi sono diversi
                {
                    return false; //ritorna FALSE
                }   
                
                tmp1 = tmp1->next; //ora tmp1 punta al nodo successivo
                tmp2= tmp2->next; //ora tmp2 punta al nodo successivo
            }

        return true; //se l'if non viene soddisfatto per nessun nodo, ritorna TRUE
    }

    template <typename Data>
    bool List<Data>::operator!=(const List &other) const noexcept
    {
        return !(*this == other); //semplicemente, nega l'operatore == 
    }

    template <typename Data>
    void List<Data>::InsertAtFront(const Data &data) //inserimento in testa (copy)
    {
        Node* nod = new Node(data);
		Node* tmp = nullptr;
		if (this->size > 0 && this->head != nullptr) {
			tmp = this->head;
			this->head = nod;
			head->next = tmp;
		} else {
			this->head = nod;
			tail = head;
		}
		size++;
    }

     /* ================================== FUNZIONI DI INSERIMENTO E RIMOZIONE ================================== */

    template <typename Data>
    void List<Data>::InsertAtFront(Data &&data) //Inserimento in testa (move)
    {
       Node* nod = new Node(std::move(data));
		Node* tmp = nullptr;
		if (this->size > 0 && this->head != nullptr) {
			tmp = this->head;
			this->head = nod;
			head->next = tmp;
		} else {
			this->head = nod;
			tail = head;
		}
		size++;
    }

    template <typename Data>
    void List<Data>::RemoveFromFront() //rimozione dalla testa
    {
        Node* tmp = nullptr;
		if (this->size == 0) {
			throw std::length_error("Empty List");
		} else {
			tmp = head;
            head = head->next;
            delete tmp;
            size--;
        }
    }

    template <typename Data>
    Data List<Data>::FrontNRemove()
    {
        if (head == nullptr) //controlla se la lista e vuota...
            throw std::length_error("La Lista e' vuota!"); //in caso affermativo, lancia lengt_error (eccezione)

        Node *temp = head; //viene assegnato il rif.to al primo nodo a temp
        Data data = std::move(temp->elements); //in data, viene memorizzato il valore del nodo (temp->elements)
        RemoveFromFront(); //viene chiamata la funzione di rimozione in testa
        return data; //restituisce il valore eliminato
    }

    template <typename Data>
    void List<Data>::InsertAtBack(const Data &data) //inserimento in coda (copy)
    {
         Node* tmp = nullptr;
		if (size == 0) {
			InsertAtFront(std::move(data));
		} else {
		tmp = new Node(std::move(data));
		tail->next = tmp;
        tail = tmp;
		size++;
        }
    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data &&data) //inserimento in coda (move)
    {

      Node* tmp = nullptr;
		if (size == 0) {
			InsertAtFront(std::move(data));
		} else {
		tmp = new Node(std::move(data));
		tail->next = tmp;
        tail = tmp;
		size++;
        }
    }

    template <typename Data>
    void List<Data>::RemoveFromBack() //rimozione dalla coda
    {
      Node* tmp = nullptr;
      Node *tmp1 = nullptr;
		if (this->size == 0) {
			throw std::length_error("Empty List");
		} else if(tail != head){
			tmp = head;
            while(tmp->next->elements != tail->elements){tmp = tmp->next;}
            tmp1 = tmp->next; //tail
            tmp->next = nullptr;
            delete tmp1;
            tmp1 = nullptr;
            tail = tmp;
            size--;
    }else{
        delete head;
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    
}

    template <typename Data>
    Data List<Data>::BackNRemove() //rimuove il dato e lo restituisce
    {
        /*stesso ragionamento del FrontNRemove*/
        if (tail == nullptr)
            throw std::length_error("La Lista e' vuota!");

        Data data = Back();
        RemoveFromBack();
        return data;
    }

     /* ================================== FUNZIONI DI ACCESSO ================================== */

    template <typename Data>
    Data &List<Data>::operator[](ulong i) //accesso a elemento specifico
    {
        if (i >= size) //si controlla che l'indice "i" sia minore uguale della size, se è maggiore...
            throw std::out_of_range("Oltre la dimensione"); //lancia out_of_range(eccezione)

        Node *curr = head; //a curr si assegna il rif.to alla testa
        ulong index = i; //a index si assegna il valore di "i"
        while (index-- > 0) //si decrementa index fino a quando è > 0
            curr = curr->next; //si arriva al nodo interessato
        return curr->elements; //restituisce il valore del nodo 
    }

    template <typename Data>
    Data &List<Data>::Front() //accesso in testa
    {
        if (head == nullptr)
            throw std::length_error("La Lista e' vuota!");

        return head->elements;
    }

    template <typename Data>
    Data &List<Data>::Back() //accesso in coda
    {
        if (tail == nullptr)
            throw std::length_error("La Lista e' vuota!");

        return tail->elements;
    }

    template <typename Data>
    const Data &List<Data>::operator[](ulong i) const //accesso secondo indice
    {
        if (i >= size)
            throw std::out_of_range("Oltre la dimensione");

        Node *curr = head;
        ulong index = i;
        while (index-- > 0)
            curr = curr->next;

        return curr->elements;
    }

    template <typename Data>
    const Data &List<Data>::Front() const //lettura in testa
    {
        if (head == nullptr)
            throw std::length_error("La Lista e' vuota!");

        return head->elements;
    }

    template <typename Data>
    const Data &List<Data>::Back() const //lettura in coda
    {
        if (tail == nullptr)
            throw std::length_error("La Lista e' vuota!");

        return tail->elements;
    }

    template <typename Data>
    void List<Data>::Map(MapFun fun)
    {
        PreOrderMap(fun);
    }

    template <typename Data>
    void List<Data>::PreOrderMap(MapFun fun)
    {

        Node *curr = head;
        while (curr != nullptr)
        {
            fun(curr->elements);
            curr = curr->next;
        }
    }

    template <typename Data>
    void List<Data>::PostOrderMap(MapFun fun)
    {

        std::function<void(Node *)> helper = [&](Node *node)
        {
            if (node != nullptr)
            {
                helper(node->next);
                fun(node->elements);
            }
        };
        helper(head);
    }

    template <typename Data>
    void List<Data>::Traverse(TraverseFun fun) const
    {

        PreOrderTraverse(fun);
    }

    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun) const
    {

        Node *curr = head;

        while (curr != nullptr)
        {
            fun(curr->elements);
            curr = curr->next;
        }
    }
    template <typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun) const
    {

        std::function<void(Node *)> helper = [&](Node *node)
        {
            if (node != nullptr)
            {
                helper(node->next);
                fun(node->elements);
            }
        };
        helper(head);
    }
    template <typename Data>
    void List<Data>::Clear() {
        Node *tmp = head;
		  while(tmp != nullptr){
			Node *tmp1 = tmp;
			tmp = tmp->next;
			delete tmp1;
		  }
		  head = nullptr;
		  tail = nullptr;
          size = 0;
    }

    template <typename Data>
    void List<Data>::MoveFrom(List<Data> &&other) noexcept //metodo che scambia 2 liste
    {
        std::swap(size, other.size);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
       
     }

    template <typename Data>
    void List<Data>::CopyFrom(const List &other) //metodo che copia 2 liste
    {
        Node *curr = other.head;
        while (curr != nullptr)
        {
            InsertAtBack(curr->elements);
            curr = curr->next;
        }
    }

}