#include "dlist.h"

template <class T>
void Dlist<T>::removeAll(){
    node* p = this->first,* last;
    while (p){
        last = p;
        p = p->next;
        delete(last);
    }
    this->first = this->last = nullptr;
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l){
    this->removeAll();
    node* p = l.first;
    while (p){
        this->insertBack(p);
        p = p->next;
    }
}

template <class T>
bool Dlist<T>::isEmpty()const{
    return (this->first == nullptr);
}

template <class T>
void Dlist<T>::insertFront(T* op){
    node* p = new node;
    p->op = op;
    if (this->isEmpty()){
        this->first = this->last = p;
        p->next = p->prev = nullptr;
    }
    else{
        p->next = this->first;
        this->first->prev = p;
        this->first = p;
        p->prev = nullptr;
    }
}

template <class T>
void Dlist<T>::insertBack(T* op){
    node* p = new node;
    p->op = op;
    if (this->isEmpty()){
        this->first = this->last = p;
        p->next = p->prev = nullptr;
    }
    else{
        p->prev = this->last;
        this->last->next = p;
        this->last = p;
        p->next = nullptr;
    }
}

template <class T>
T* Dlist<T>::removeFront(){
    if (this->isEmpty())
        throw (new emptyList);
    T* op = this->first->op;
    node* newFirst = this->first->next;
    if (this->first->next)
        this->first->next->prev = nullptr;
    delete(this->first);
    this->first = newFirst;
    if (!newFirst){
        this->last = nullptr;
    }
    return op;
}

template <class T>
T* Dlist<T>::removeBack(){
    if (this->isEmpty())
        throw (new emptyList);
    T* op = this->last->op;
    node* newLast = this->last->prev;
    if (this->last->prev)
        this->last->prev->next = nullptr;
    delete(this->last);
    this->last = newLast;
    if (!newLast){
        this->first = nullptr;
    }
    return op;
}

template <class T>
Dlist<T>::Dlist(){
    this->first = this->last = nullptr;
}

template <class T>
Dlist<T>::Dlist(const Dlist &l){
    this->first = this->last = nullptr;
    (*this) = l;
}

template <class T>
Dlist<T>& Dlist<T>::operator= (const Dlist &l){
    this->removeAll();
    if (this != &l){
        node* p = l.first;
        if (p == nullptr)
            this->first = this->last = nullptr;
        else{
            while (p){
                insertBack(p->op);
                p = p->next;
            }
        }
    }
    return (*this);
}


template <class T>
Dlist<T>::~Dlist(){
    node* p = this->first;
    while (p){
        node* next = p->next;
        delete p;
        p = next;
    }
}