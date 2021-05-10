#pragma once
#ifndef LIST_H
#define LIST_H
#include "node.h"
#include <list>
template<typename T>
class List
{
    Node<T>* head;
    unsigned counter;

public:
    List();
    Node<T>* addFront(Node<T>*);
    Node<T>* deleteElement(Node<T>*);
    int size();
    Node<T>* getHead();
    std::list<Node <T>*> getElements(std::string);
    Node <T>* getElement(T&);
    Node <T>* getElement(int);
    void setCounter(int);
    void increase_counter();
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
std::list<Node <T>*>  List<T>::getElements(std::string name)
{
    Node<T>* tmp = this->head;
    std::list<Node <T>*> returnData;
    while (tmp)
    {
        if (tmp->getCurrentData() == name)
        {
            returnData.push_back(tmp);
        }

            tmp = tmp->getNext();
    }
    return returnData;
}

template<typename T>
Node<T>* List<T>::getElement(int num)
{
    Node<T>* tmp = this->head;

    while (tmp)
    {
        if (tmp->getCurrentData() == num)
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
