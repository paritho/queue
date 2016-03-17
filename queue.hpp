/********************************************************************
* HW6 -- Maze solver
*
* Author: Paul Thompson
*         prt@uakron.edu
*
* Purpose: Using a linked list, implements a queue where objects are
* FIFO. Dependent upon my implementation in List.hpp. Of note is that
* the list's head and tail are empty nodes. To get the value from
* the front of the queue, use head->next->value.
*
********************************************************************/

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

template<typename T>
struct Queue
{
    List<T> q;
public:

    Queue():
        q(List<T>())
    {}

    ~Queue(){ q.clear(); };

    // Needs head->next->value because head is an empty node
    // in the List.
    T const& front() const { return q.head->next->value; }
    T& front() { return q.head->next->value; }

    void push(T const& x) { q.push_back(x); }

    void pop() { q.pop_front(); }

    bool is_empty() { return q.is_empty(); }
};


#endif
