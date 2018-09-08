#ifndef DLIST_H
#define DLIST_H

#include <stdexcept>
#include "iterator.h"

template <typename T>
class DListIterator : public Iterator<T> {     
    public: 
        DListIterator() : Iterator<T>() {};
        DListIterator(Node<T> *current) : Iterator<T>(current) {};
        DListIterator<T> operator++(){
            this->current = this->current->next;
            return *this;
        }
        DListIterator<T> operator--(){
            this->current = this->current->prev;
            return *this;
        }
};

template <typename Tr>
class DList {     
    public:
        typedef typename Tr::T T;
        typedef DListIterator<T> iterator;
      
    private:
        Node<T>* head;
        Node<T>* tail;
              
    public:
        DList() {
            head = tail = nullptr;
        };

        void push_front(T data) {
            Node<T>* temp = new Node<T>(data);
            if (!head){
                head = temp;
                tail = temp;
            }else{
                temp->next = head;
                head->prev = temp;
                temp->prev = nullptr;
                head = temp;
            }
        }

        void push_back(T data) {
            Node<T>* temp = new Node<T>(data);
            if (!head){
                head = temp;
                tail = temp;
            }else{
                temp->prev = tail;
                tail->next = temp;
                temp->next = nullptr;
                tail = temp;
            }
        }
             
        void pop_front() {
            if (!head){
                throw "Lista vacia";
            }else{
                Node<T> *temp = head;
                head->next->prev = nullptr;
                head = head->next;
                delete temp;
            }
        }
             
        void pop_back() {
            if (!head){
                throw "Lista vacia";
            }else{
                Node<T> *temp = tail;
                tail->prev->next = nullptr;
                tail = tail->prev;
                delete temp;
            }
        }
             
        iterator begin() {
            if (!head){
                throw "Lista vacia";
            }else{
                DListIterator<T> it(head);
                return it;
            }
        }
             
        iterator end() {
            if (!head){
                throw "Lista vacia";
            }else{
                DListIterator<T> it(nullptr);
                return it;
            }
        }
             
        ~DList() {
            if (head) {
                head->killSelf();
            } 
        }         
};

#endif