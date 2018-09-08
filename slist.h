#ifndef SLIST_H
#define SLIST_H

#include "iterator.h"

template <class T>
class SListIterator : public Iterator<T> {     
    public: 
        SListIterator() : Iterator<T>() {};
        SListIterator(Node<T> *current) : Iterator<T>(current) {};
        SListIterator<T> operator++(){
            this->current = this->current->next;
            return *this;
        }
};

template <typename Tr>
class SList {     
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;
        typedef SListIterator<T> iterator;
      
    private:
        Node<T>* head;
        Operation cmp;
              
    public:
        SList() {
            head = nullptr;
        };

        bool find(T search, Node<T> **&pointer) {
            while((*pointer)->next != nullptr){
                if ((*pointer)->data == search){
                    return true;
                }else if(!cmp((*pointer)->data,search)){
                    return false;
                }
                pointer = &((*pointer)->next);
            }
            return false;
        }
             
        bool insert(T data) {
            Node<T> **pointer = &head;
            if (head == nullptr){
                head = new Node<T>(data);
                head->next = nullptr;
                return true;
            }else if(!find(data,pointer)){
                Node<T>* temp = new Node<T>(data);
                if ((*pointer)->next == nullptr){
                    temp->next = nullptr;
                    (*pointer)->next = temp;
                }else{
                    temp->next = (*pointer)->next;
                    (*pointer)->next = temp;
                }
                return true;
            }
            return false;
        }
             
        bool remove(T item) {
            Node<T> *temp1 = head;
            Node<T> *temp2 = head;
            while(temp1 != nullptr){
                temp2 = temp1->next;
                if(temp2->data == item){
                    temp1->next = temp2->next;
                    delete temp2;
                    return true;
                }
                temp1 = temp1->next;    
            }
            return false;
        }  
             
        iterator begin() {
            if (!head){
                throw "Lista vacia";
            }else{
                SListIterator<T> it(head);
                return it;
            }
        }
             
        iterator end() {
            if (!head){
                throw "Lista vacia";
            }else{
                SListIterator<T> it(nullptr);
                return it;
            }
        }
             
        ~SList() {
            if (head) {
                head->killSelf();
            } 
        }         
};

#endif