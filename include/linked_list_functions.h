#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <assert.h>

using namespace std;

template <typename T>
struct node
{
public:
    node(const T item, node<T>* ptr = nullptr);

    friend std::ostream& operator <<(std::ostream& outs,
                                const node<T> &printMe)
    {
        outs << printMe._item;
        return outs;
    }
    T _item;
    node* next;
};

template<typename T>
/**
 * @brief node<T>::node
 *  node constructor, initializes all fields
 * @param item
 * @param ptr
 */
node<T>::node(const T item, node<T>* ptr)
{
    this->next = ptr;
    this->_item = item;
}

template <typename T>
/**
 * @brief PrintList
 *  print the given node list
 * @param head
 */
void _PrintList(node<T>* head)
{
    node<T>* n = head;
    // as long as the walker hasn't reach to the last element (nullptr)
    while(n != nullptr)
    {
        cout << "[" << n->_item << "]->";
        n = n->next;
    }cout << "|||";
}

template <typename T>
/**
 * @brief PrintList_backwards
 *  print given list backward using recursive method
 * @param head
 */
void _PrintList_backwards(node<T> *head)
{
    node<T>* n = head;
    // base case
    if(n->next != nullptr)
        _PrintList_backwards(n->next);
    // print current node
    cout << n->_item <<" ";
}

template <typename T>
/**
 * @brief SearchList
 *  search a key in given list
 * @param head
 * @param key
 * @return pointer to node of the key, return nullptr if not found
 */
node<T>* _SearchList(node<T>* head,
                           T key)
{
    node<T>* n = head;
    // walker thru the list
    while(n != nullptr)
    {
        // check current walker is key
        if(n->_item == key)
            return n;
        n = n->next;
    }
    return nullptr;
}

template <typename T>
/**
 * @brief InsertHead
 *  Insert the given element to the beginning of a list
 * @param head
 * @param insertThis
 * @return node of inserted element
 */
node<T>* _InsertHead(node<T> *&head,
                           T insertThis)
{
    node<T>* newNode = new node<T>(insertThis);

    // insert a newnode to the middle of first and second node
    newNode->next = head;
    head = newNode;
    return newNode;
}

template <typename T>
/**
 * @brief RemoveHead
 *  remove the first element of the given list
 * @param head
 * @return  element that has been removed
 */
T _RemoveHead(node<T> *&head)
{
    assert(head);
    node<T>* n = head;
    T toReturn = n->_item;

    // points head to the second one and delete first one
    head = head->next;
    delete n;

    return toReturn;
}

template <typename T>
/**
 * @brief InsertAfter
 *  Insert an element after a given node in a list
 * @param head
 * @param afterThis
 * @param insertThis
 * @return pointer of node inserted
 */
node<T>* _InsertAfter(node<T>*& head,
                            node<T> *afterThis,
                            T insertThis)
{
    if(head == nullptr || afterThis == nullptr) return _InsertHead(head, insertThis);
    // insert element by calling inserthead
    return _InsertHead(afterThis->next, insertThis);
}

template <typename T>
/**
 * @brief InsertBefore
 *  insert a element before a given node in list
 * @param head
 * @param beforeThis
 * @param insertThis
 * @return  node pointer of element inserted
 */
node<T>* _InsertBefore(node<T>*& head,       //insert before ptr
                             node<T>* beforeThis,
                             T insertThis)
{
    // check if given position is the first element
    if(beforeThis == head)
        return _InsertHead(head, insertThis);
    if(head == nullptr) return _InsertHead(head, insertThis);

    // find previous node and call insert after
    return _InsertAfter(head, _PreviousNode(head, beforeThis), insertThis);
}

template <typename T>
/**
 * @brief PreviousNode
 *  finds the pointer of given node's previous node in a list
 * @param head
 * @param prevToThis
 * @return pointer of previous node, nullptr if not found
 */
node<T>* _PreviousNode(node<T>* head,        //ptr to previous node
                             node<T>* prevToThis)
{
    if(prevToThis == nullptr)
        return _LastNode(head);

    // assert given node is valid
    assert(_SearchList(head, prevToThis->_item) != nullptr);
    node<T>* n = head;

    //  find the node tha has the next pointer points to the given one
    while(n->next != nullptr)
    {
        if(n->next == prevToThis)
            return n;
        n = n->next;
    }
    return nullptr;
}

template <typename T>
/**
 * @brief DeleteNode
 *  delete a given node exist in a list
 * @param head
 * @param deleteThis
 * @return  element of node that has been deleted
 */
T _DeleteNode(node<T>*&head,                 //delete, return item
                    node<T>* deleteThis)
{
    // check if given node is the first element
    if(deleteThis == head)
        return _RemoveHead(head);

    // if not, find its previous in order to find it pointer, and delete it
    return _RemoveHead(_PreviousNode(head, deleteThis)->next);
}

template <typename T>
/**
 * @brief CopyList
 *  make a copy of given list and assign the head of copied list to other
 * @param head
 *  list to make copy of
 * @param copy
 *  list to assign copy's head to
 * @return  last node of copied list
 */
node<T>* _CopyList(node<T>* head, node<T>*& copy)
{
    // check if given list is empty
    if(head == nullptr)
        return _ClearList(copy);
    // Check copy is empty
    if(copy != nullptr)
        _ClearList(copy);

    // insert an element first so that copied list is not empty
    copy = _InsertHead(copy, head->_item);
    node<T>* newHead_counter = copy;

    // copy rest of the element to the copy list
    while(head->next != nullptr){
        head = head->next;
        newHead_counter = _InsertAfter(copy, newHead_counter, head->_item);
    }
    // return walker that walkes to the last element
    return newHead_counter;
}

template <typename T>
/**
 * @brief ClearList
 *  clear all dynamic nodes in a list and points list to a nullptr
 * @param head
 */
node<T>* _ClearList(node<T>*& head)
{
    while(head != nullptr)
    {
        T temp = _RemoveHead(head);
    }
}

template <typename T>
/**
 * @brief At
 *  search the reference of element at given position of given list
 * @param head
 * @param pos
 * @return  reference of desire element
 */
T& _At(node<T>* head, int pos)
{
    int i = 0;
    node<T>* n = head;
    // go thru the list for given number of times an return the element
    while(i != pos)
    {
        n = n->next;
        i++;
    }
    return n->_item;
}

template <typename T>
/**
 * @brief LastNode
 *  find the last node of a given list
 * @param head
 * @return  last node of given list, nullptr if given list is empty
 */
node<T>* _LastNode(node<T>* head)
{

    node<T>* n = head;
    while(n != nullptr)
    {
        // go thru each element and check if its the last element
        if(n->next == nullptr)
            return n;
        n = n->next;
    }
    return nullptr;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending   .
//                              Assume a Sorted List                          .
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
node<T>* _InsertSorted(node<T>* &head,       //insert
                             T item,
                             bool ascending=true)
{
    node<T>* toInsert = _WhereThisGoes(head, item, ascending);
    node<T>* toReturn;
    if(toInsert == nullptr)
        toReturn = _InsertHead(head, item);
    else if(toInsert->_item == item)
    {
        toReturn = _InsertAfter(head, toInsert, item);
        _DeleteNode(head, toInsert);
    }
    else
        toReturn = _InsertAfter(head, toInsert, item);
    return toReturn;
}

template <typename T>
node<T>* _InsertSorted_and_add(node<T>* &head, //insert or add if a dup
                                     T item,
                                     bool ascending=true)
{
    node<T>* toInsert = _SearchList(head, item);
    if(toInsert != nullptr)
    {
        toInsert->_item += item;
    }
    else
    {
        toInsert = _InsertSorted(head, item, ascending);
    }

    return toInsert;
}

template <typename T>
node<T>* _WhereThisGoes(node<T>* head,         //node after which this
                              T item,                //    item goes
                              bool ascending=true)          //order: 0 ascending
{
    if(ascending)
    {
        if(head == nullptr || head->_item > item)
            return nullptr;
        while(head->next != nullptr)
        {
            if(head->next->_item > item)
                return head;
            head = head->next;
        }return head;
    }
    else
    {
        if(head == nullptr || head->_item < item)
            return nullptr;
        while(head->next != nullptr)
        {
            if(head->next->_item < item)
                return head;
            head = head->next;
        }return head;
    }

}


#endif // NODE_H
