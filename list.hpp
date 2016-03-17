/********************************************************************
* HW5 -- Linked List
*
* Author: Paul Thompson
*         prt@uakron.edu
*
* Purpose: Class definition for List<T>, which creates a list of
* Node<T>. The List<T> has a pointer to the head and tail, which
* are empty Node<T>, and a member variable count which is used to
* track the size of the list.
*
********************************************************************/
#ifndef LIST_HPP
#define  LIST_HPP

#include "Node.hpp"
#include "Iterator.hpp"
#include <cassert>
#include <iostream>

template <typename T>
struct List {
    Node<T> *head, *tail;
    int count;

public:
    List<T>():
        head(new Node<T>()),
        tail(new Node<T>()),
        count(0)
    {
        // The constructor for Node<T>() sets head->prev
        // and tail->next == nullptr. We update the two
        // required directions here when we make the list
        head->next = tail;
        tail->prev = head;
    }

    // The copy constructor uses a range-based for loop and
    // push_back() to add Node<T> from one list to the new one.
    List<T>(List<T> const& l):
        head(new Node<T>()),
        tail(new Node<T>()),
        count(0)
    {
        for(auto n : l) push_back(n);
    }

    // Initialize a list from a list of <T> in format: {1,2,3}. Like
    // the copy constructor, this uses a rand-based for look and
    // push_back to add the given elements as Node<T> to the list.
    List<T>(std::initializer_list<T> l) :
        head(new Node<T>()),
        tail(new Node<T>()),
        count(0)
    {
        head->next = tail;
        tail->prev = head;

        for(T n: l){
            push_back(n);
        }
    }

    ~List(){clear();}
    
     List& operator = (List<T> const& l){
         clear();
         head->next = tail;
         tail->prev = head;
         for(Iterator<T> i = l.begin(); i != l.end(); ++i) push_back(*i);
    }

    // Begin() and end() will return Iterators pointing to the head
    // and tail respectively. Begin() points to head->next so that
    // we can operate on that Node<T> immediately.
    Iterator<T> begin(){return head->next;}
    Iterator<T> begin() const {return head->next;}
    Iterator<T> end(){return tail;}
    Iterator<T> end() const {return tail;}

    // Both size() and is_empty() rely on count. Each time a Node<T>
    // is added or removed count is updated. Count will always represent
    // the length of the List<T>, not including the empty Node<T> of head
    // and tail.
    int size(){return count;}
    bool is_empty(){return size() == 0;}

    // Push_back() uses insert to add a Node<T> to the end of List<T>,
    // just before tail.
    void push_back(T data){
        insert(tail, data);
    }

    // Push_front() uses insert() to add a Node<T> with value data to the
    // beginning of the list, just after head.
    void push_front(T data){
        insert(head->next, data);
    }

    // Removes a Node<T> from the back of the list. Simply calls erase() on
    // the Node<T> previous to tail. Logical error to call pop_back() on
    // empty list, which is handled inside erase();
    void pop_back(){
        erase(tail->prev);
    }

    // Removes a Node<T> from the front of the list. Pop_front() calls erase()
    // on head->next.
    void pop_front(){
        erase(head->next);
    }

    // Clear() removes all elements from the List<T> including the empty Node<T>
    // head and tail. The while loop cycles through each Node<T> from head to
    // tail and deletes it.
    void clear(){
        while(!is_empty()){
            Node<T>* q = tail->prev->prev;
            erase(tail->prev);
            tail->prev = q;
        }

        // The list is now empty, so count must = 0
        count = 0;
    }

    // Insert() adds a new Node<T> to the List<T> before the given Iterator<T>
    // i. We are careful to set the pointers of the new Node<T> before updating
    // the Iterator so we don't lose the other Node<T>s.
    Iterator<T> insert(Iterator<T> i, T data){

        // Make new Node<T>. the Node<T>(data) constructor will set the new
        // node value to data so we don't have to assign that within this
        // function.
        Node<T> *node = new Node<T>(data);

        if(!is_empty()) {
            // Pointer updates.
            i.iter->prev->next = node;
            node->prev = i.iter->prev;
            node->next = i.iter;
            i.iter->prev = node;
        } else {
            head->next = node;
            node->prev = head;
            node->next = tail;
            tail->prev = node;
        }

        // Increment count to keep track of list.size()
        ++count;
        return --i;
    }

    // Erase() removes the element at the Iterator<T> i from the List<T>.
    // Because we're deleting an element, erase() first makes a copy of
    // the Node<T> so we don't lose the other nodes. Calling erase() on an
    // empty list is a logical error.
    Iterator<T> erase(Iterator<T> i){
        // Assert no logical errors
        assert(!is_empty());

        Node<T> *p = i.iter->next;
        // Updating only two pointers since we're about to delete the
        // Node<T> i and we don't care where its next and prev point.
        p->prev = i.iter->prev;
        i.iter->prev->next = p;

        // Decrement count to keep track of list.size() and delete the Node.
        --count;
        delete i.iter;

        // Return a pointer to the Node<T> after the erased Node<T>
        return p;
    }
};
#endif
