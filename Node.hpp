
#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node {
    T value;
    Node *next, *prev;

    Node():
            next(nullptr),
            prev(nullptr),
            value(T())
    {}

    Node<T>(T data):
            next(nullptr),
            prev(nullptr),
            value(data)
    {}

};

#endif