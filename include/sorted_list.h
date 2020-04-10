#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include "../../../include/linked_list_functions.h"
template <class T>
class List
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
            assert(_ptr);
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

    List(bool order=true, bool unique=false);

    ~List();
    List(const List<T> &copyThis);
    List& operator =(const List& RHS);

    Iterator Insert(const T& i);

    T Delete(List<T>::Iterator iMarker);
    void Print() const;
    void ClearList();
    Iterator Search(const T &key) const;
    Iterator Prev(Iterator iMarker);

    const T& operator[](int index) const;
    T& operator[](int index);
    Iterator Begin() const;
    Iterator End() const;
    Iterator LastNode() const;
    template <class U>
    friend ostream& operator <<(ostream& outs, const List<U>& l)
    {
        _PrintList(l._head_ptr);
        return outs;
    }
private:
    node<T>* _head_ptr;
    bool _order;
    bool _unique;

};
template <class T>
/**
 * @brief List<T>::List
 *  default constructor, initializes head
 */
List<T>::List(bool order, bool unique)
{
    _head_ptr = nullptr;
    _order = order;
    _unique = unique;
}

template<class T>
/**
 * @brief List<T>::~List
 *  destructor, delete all dynamic nodes in list
 */
List<T>::~List<T>()
{
    _ClearList(_head_ptr);
}

template <class T>
/**
 * @brief List<T>::List
 *  copy constructor
 * @param list
 */
List<T>::List(const List<T> &list)
{
    _head_ptr = nullptr;
    cout << list << endl;
    _CopyList(list._head_ptr, _head_ptr);
    _order = list._order;
    _unique = list._unique;
}

template <class T>
/**
 * @brief List<T>::operator =
 *  Assignment operator overload, copy RHS content to this class
 * @param RHS
 * @return
 */
List<T>& List<T>::operator =(const List& RHS)
{
    // check self reference
    if(RHS._head_ptr == _head_ptr) return *this;
    _CopyList(RHS._head_ptr, _head_ptr);
    _order = RHS._order;
    _unique = RHS._unique;
}

template<class T>
/**
 * @brief List<T>::Insert
 *  Insert a given T into the list, sort/unique accordingly
 * @param i
 * @return  Inserted node
 */
typename List<T>::Iterator List<T>::Insert(const T& i)
{
    return !_unique ? Iterator(_InsertSorted_and_add(_head_ptr, i, _order)) :
                     Iterator(_InsertSorted(_head_ptr, i, _order));

}

template<class T>
/**
 * @brief List<T>::Delete
 *  delete a given node
 * @param iMarker
 * @return deleted T
 */
T List<T>::Delete(List<T>::Iterator iMarker)
{
    return _DeleteNode(_head_ptr, iMarker._ptr);
}

template<class T>
/**
 * @brief List<T>::Print
 */
void List<T>::Print() const
{
    _PrintList(_head_ptr);
}

template<class T>
/**
 * @brief List<T>::ClearList
 *  clears the list
 */
void List<T>::ClearList()
{
    _ClearList(_head_ptr);
}

template<class T>
/**
 * @brief List<T>::Search
 *  search a node in list by using given key
 * @param key
 * @return Iterator pointes to desire node
 */
typename List<T>::Iterator List<T>::Search(const T &key) const
{
    return Iterator(_SearchList(_head_ptr, key));
}

template<class T>
/**
 * @brief List<T>::Prev
 *  get the previous node of a given node in list
 * @param iMarker
 * @return  Iterator points to previous node of iMaker in list
 */
typename List<T>::Iterator List<T>::Prev(Iterator iMarker)
{
    return Iterator(_PreviousNode(_head_ptr, iMarker._ptr));
}

template<class T>
/**
 * @brief List<T>::operator []
 *  bracket operator overload
 * @param index :   index to check
 * @return content of given index
 */
const T& List<T>::operator[](int index) const
{
   return _At(_head_ptr, index);
}

template<class T>
/**
 * @brief List<T>::operator []
 *  bracket operator overload
 * @param index :   index to check
 * @return content of given index
 */
T& List<T>::operator[](int index)
{
    return _At(_head_ptr, index);
}

template<class T>
/**
 * @brief List<T>::Begin
 *  get the first node of the list
 * @return Iterator of head of the list
 */
typename List<T>::Iterator List<T>::Begin() const
{
    return Iterator(_head_ptr);
}

template<class T>
/**
 * @brief List<T>::End
 *  return what the end of the list is
 * @return nullptr
 */
typename List<T>::Iterator List<T>::End() const
{
    return Iterator();
}

template<class T>
/**
 * @brief List<T>::LastNode
 *  get the last node of list
 * @return Iterator of last node
 */
typename List<T>::Iterator List<T>::LastNode() const
{
    return Iterator(_LastNode(_head_ptr));
}
#endif // SORTED_LIST_H
