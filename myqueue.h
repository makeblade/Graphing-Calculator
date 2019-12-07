#ifndef MYQUEUE_H
#define MYQUEUE_H
#include "../include/linked_list_functions.h"

template<class T>
class Queue
{
public:
    class Iterator{
    public:
        friend class List;
        Iterator(){_ptr = NULL;}
        Iterator(node<T>* p)
        {
            _ptr = p;
        }
        T operator *()
        {
            return _ptr->_item;
        }
        //T* operator ->();
        operator bool()
        {
            return _ptr != nullptr;
        }

        bool is_null()
        {
            return _ptr == nullptr;
        }
        friend bool operator !=(const Iterator& left,
                                const Iterator& right)
        {
            return left._ptr != right._ptr;
        }

        friend bool operator ==(const Iterator& left,
                                const Iterator& right)
        {
            return left._ptr == right._ptr;
        }

        Iterator& operator++()
        {
            if(this->_ptr != nullptr)   _ptr = _ptr->next;
            return *this;
        }

        friend Iterator operator++(Iterator& it,
                                   int unused)
        {
            Iterator result = it;
            ++it;
            return result;
        }

    private:
        node<T>* _ptr;
    };
    Queue();
    Queue(const Queue& st);
    ~Queue();
    Queue& operator =(const Queue& RHS);

    T pop();
    Iterator push(const T&);
    Iterator front() const;
    Iterator back() const ;
    bool empty();
    friend ostream& operator <<(ostream& outs, const Queue& st)
    {
        _PrintList(st._head_ptr);
        return outs;
    }
private:
    node<T>* _head_ptr;
    node<T>* _last_ptr;
};

template<class T>
/**
 * @brief Stack<T>::Queue
 *  default constructor
 */
Queue<T>::Queue()
{
    _head_ptr = nullptr;
    _last_ptr = nullptr;
}

template<class T>
/**
 * @brief Stack<T>::Queue
 *  parametrized constructor
 * @param st
 */
Queue<T>::Queue(const Queue& st)
{
    _head_ptr = nullptr;
    _last_ptr = _CopyList(st._head_ptr, _head_ptr);
}

template<class T>
/**
 * @brief Stack<T>::~Queue
 *  destructor
 */
Queue<T>::~Queue()
{
    _ClearList(_head_ptr);
}

template<class T>
/**
 * @brief Stack<T>::operator =
 *  Assignment operator overload
 * @param RHS
 * @return  this class
 */
Queue<T>& Queue<T>::operator=(const Queue& RHS)
{
    if(&RHS == this) return *this;
    _last_ptr = _CopyList(RHS._head_ptr, _head_ptr);
    return *this;
}

template<class T>
/**
 * @brief Stack<T>::pop
 *  remove the node at front of the list
 * @return T removed
 */
T Queue<T>::pop()
{
    return _RemoveHead(_head_ptr);
}

template<class T>
/**
 * @brief Stack<T>::push
 *  push a given element into the front of the list
 * @param i
 * @return Iterator of pushed node
 */
typename Queue<T>::Iterator Queue<T>::push(const T& i)
{
    _last_ptr = _InsertAfter(_head_ptr, _last_ptr, i);
    return _last_ptr;
}

template<class T>
/**
 * @brief Stack<T>::front
 *  get the iterator of list'front node
 * @return Iterator of first node in list
 */
typename Queue<T>::Iterator Queue<T>::front() const
{
    return Iterator(_head_ptr);
}

template<class T>
/**
 * @brief Stack<T>::empty
 *  check if list is currently empty
 * @return true of empty, false otherwises
 */
bool Queue<T>::empty()
{
    return _head_ptr == nullptr;
}

template<class T>
/**
 * @brief Stack<T>::back
 *  get the iterator of back of the queue
 * @return  Iterator of last node in last
 */
typename Queue<T>::Iterator Queue<T>::back() const
{
    return Iterator(_last_ptr);
}
#endif // MYQUEUE_H
