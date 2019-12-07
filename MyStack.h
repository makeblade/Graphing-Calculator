#ifndef MYSTACK_H
#define MYSTACK_H
#include "../include/linked_list_functions.h"

template<class T>
class Stack
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
    Stack();
    Stack(const Stack& st);
    ~Stack();
    Stack& operator =(const Stack& RHS);

    T pop();
    Iterator push(const T&);
    Iterator top() const;
    Iterator bottom() const;
    bool empty();
    friend ostream& operator <<(ostream& outs, const Stack& st)
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
 * @brief Stack<T>::Stack
 *  default constructor
 */
Stack<T>::Stack()
{
    _head_ptr = nullptr;
    _last_ptr = nullptr;
}

template<class T>
/**
 * @brief Stack<T>::Stack
 *  parametrized constructor
 * @param st
 */
Stack<T>::Stack(const Stack& st)
{
    _last_ptr = _CopyList(st._head_ptr, _head_ptr);
}

template<class T>
/**
 * @brief Stack<T>::~Stack
 *  destructor
 */
Stack<T>::~Stack()
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
Stack<T>& Stack<T>::operator=(const Stack& RHS)
{
    // self-reference
    if(&RHS == this) return *this;
    _last_ptr = _CopyList(RHS._head_ptr, _head_ptr);
    return *this;
}

template<class T>
/**
 * @brief Stack<T>::pop
 *  remove the node at top of the list
 * @return T removed
 */
T Stack<T>::pop()
{
    // update _last_ptr to nullptr if list is empty
    if(_head_ptr == _last_ptr) _last_ptr = nullptr;
    return _RemoveHead(_head_ptr);
}

template<class T>
/**
 * @brief Stack<T>::push
 *  push a given element into the top of the list
 * @param i
 * @return Iterator of pushed node
 */
typename Stack<T>::Iterator Stack<T>::push(const T& i)
{
    // update _last_ptr
    if(_head_ptr == nullptr)
    {
        _last_ptr = _InsertHead(_head_ptr, i);
        return Iterator(_last_ptr);
    }
    return Iterator(_InsertHead(_head_ptr, i));
}

template<class T>
/**
 * @brief Stack<T>::top
 *  get the iterator of list'top node
 * @return Iterator of first node in list
 */
typename Stack<T>::Iterator Stack<T>::top() const
{
    return Iterator(_head_ptr);
}

template<class T>
/**
 * @brief Stack<T>::empty
 *  check if list is currently empty
 * @return true of empty, false otherwises
 */
bool Stack<T>::empty()
{
    return _head_ptr == nullptr;
}

template<class T>
/**
 * @brief Stack<T>::bottom
 *  get the iterator of bottom of the stack
 * @return  Iterator of last node in last
 */
typename Stack<T>::Iterator Stack<T>::bottom() const
{
    return Iterator(_last_ptr);
}

#endif // STACK_H
