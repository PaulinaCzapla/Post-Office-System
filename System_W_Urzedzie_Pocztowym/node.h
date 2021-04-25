#pragma once
#ifndef NODE_H
#define NODE_H
#include <iostream>

template<typename T>
class Node
{
    Node* next, *prev;
    T data;

public:
    Node(T);
    Node(Node*);
    Node(T, Node<T>*, Node<T>*);
    void setNext(Node*);
    Node * getNext();
    void setPrev(Node*);
    Node* getPrev();
    T& getCurrentData();
    Node* getCurrent();
    Node& operator=(const Node&);
    bool operator==(const std::string&);
    ~Node();
};


template<typename T>
Node<T>::Node(T data_)
{
    this->data = data_;
    this->next = nullptr;
    this->prev = nullptr;
}

template <typename T>
Node<T>::Node(Node<T>* node_)
{
    this->data = node_->data;
    this->next = node_->next;
    this->prev = node_->prev;
}

template <typename T>
Node<T>::Node(T data_, Node<T>* next_, Node<T>* prev_)
{
    this->data = data_;
    this->next = next_;
    this->prev = prev_;
}


template <typename T>
void Node<T>::setNext(Node<T>* next_)
{
    this->next = next_;
}

template <typename T>
Node<T>* Node<T>::getNext()
{
    return this->next;
}

template <typename T>
void Node<T>::setPrev(Node<T>* prev_)
{
    this->prev = prev_;
}

template <typename T>
Node<T>* Node<T>::getPrev()
{
    return this->prev;
}


template <typename T>
T& Node<T>::getCurrentData()
{
    return this->data;
}

template <typename T>
Node<T>* Node<T>::getCurrent()
{
    return this;
}

template <typename T>
Node<T>& Node<T>::operator=(const Node<T>& other)
{
    this->next = other->next;
    this->data = other->data;

    return*this;
}

template <typename T>
bool Node<T>::operator==(const std::string& id)
{
    if (this->data == id)
        return true;
    else
        return false;
}

template <typename T>
Node<T>::~Node()
{

}

#endif
