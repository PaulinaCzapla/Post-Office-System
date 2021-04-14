#pragma once
#ifndef LIST_H
#define LIST_H
#include "node.h"

template<typename T>
class List
{
    Node<T>* head;
    unsigned counter;

public:
    List();
    Node<T>* addFront(Node<T>*);						//dodaje na poczatek listy
    Node<T>* deleteElement(Node<T>*);					//usuwa wybrany element
    int size();										//zwraca ilość elementów listy
    Node<T>* getHead();
    Node <T>* getElement(std::string);           //szukanie elementu po ID, zwraca znaleziony element albo nullptr
    Node <T>* getElement(T&);
    T pop();
    void setCounter(int);
    void increase_counter();
    T& getData(Node<T>*);
    ~List();
};




template<typename T>
List<T>::List()
{
    this->head = nullptr;
    this->counter = 0;
}

template<typename T>
Node<T>* List<T>::addFront(Node<T>* node_)
{
    node_->setNext(this->head);
    node_->setPrev(nullptr);

    if (this->head)
        this->head->setPrev(node_);
    this->head = node_;

    counter++;
    return this->head;
}

template<typename T>
Node<T>* List<T>::deleteElement(Node<T>* node_)
{
    Node<T>* tmp;

    if (node_->getPrev())
        node_->getPrev()->setNext(node_->getNext());
    else
        this->head = node_->getNext();

    if (node_->getNext())
        node_->getNext()->setPrev(node_->getPrev());

    delete node_;
    node_ = nullptr;
    counter--;
    return this->head;
}

template<typename T>
Node<T>* List<T>::getElement(std::string id)
{
    Node<T>* tmp = this->head;

    while (tmp)
    {
        if (tmp->getCurrentData() == id)
            return tmp;
        else
            tmp = tmp->getNext();
    }
    return nullptr;
}


template<typename T>
Node<T>* List<T>::getElement(T& data)
{
    Node<T>* tmp = this->head;

    while (tmp)
    {
        if (tmp->getCurrentData() == data)
            return tmp;
        else
            tmp = tmp->getNext();
    }
    return nullptr;
}


template<typename T>
int List<T>::size()
{
    return this->counter;
}

template<typename T>
T List<T>::pop()
{
     if(head)
     {
       auto p = head->next;
       auto tp = head->data();
       delete head;
       head = nullptr;
       head = p;
       counter--;
       return tp;
     }
  }

template<typename T>
void List<T>::setCounter(int counter_)
{
    this->counter = counter_;
}

template<typename T>
void List<T>::increase_counter()
{
    this->counter++;
}

template<typename T>
T& List<T>::getData(Node<T>* node)
{
    return node->getCurrentData();
}

template<typename T>
Node<T>* List<T>::getHead()
{
    return head;
}

template<typename T>
List<T>::~List()
{
    Node <T>* p;

    while (this->head)
    {
        p = this->head->getNext();
        delete this->head;
        this->head = p;
    }
    this->head = nullptr;
}

#endif
