#ifndef myvector_H
#define myvector_H

#include <iostream>
#include "../include/one_d_array.h"

using namespace std;

const bool DEBUG = false;

template<class T>
class myvector
{
public:

    // constructors
    myvector();
    myvector(int n);
    myvector(const myvector& vec);
    myvector& operator = (const myvector& vec);

    // destructor
    ~myvector();

    // manipulation
    void push_back(const T&);
    void pop_back();
    void erase_element(const T&);
    void erase(int index);
    void insert(int in_here, const T&);
    myvector& operator += (const T& item);
    myvector& operator += (const myvector& item);


    // size
    int size();
    int capacity();

    // size control
    void resize(int size);
    void reserve(int);
    void clear();
    bool empty();

    // element accessor
    int index_of(const T&);
    T& at(int);
    const T& at(int) const;
    const T& front() const;
    const T& back() const;
    T& operator [] (const int& index);
    const T& operator [] (const int& index) const;

    // friend functions
    /**
     * @brief operator <<
     *  insertion opeartor overloading
     * @param out   :   ostream obj
     * @param vec   :   object to print
     * @return ostream obj by reference
     */
    friend ostream& operator << (ostream &out, const myvector &vec)
    {
        print_list(vec._arr, vec._size);
        return out;
    }
    /**
     * @brief operator +
     *  concatinate to myvectors
     * @param vec1
     * @param vec2
     * @return  result myvector afted concatinated
     */
    friend myvector operator + (const myvector &vec1, const myvector &vec2)
    {
        myvector temp = vec1;

        // create a third myvector same as first one an reserve
        //  its capacity to ensure no overflow
        temp += vec2;

        return temp;
    }
    /**
     * @brief operator +
     *  add an element to myvector
     * @param vec
     * @param item  :   element to add
     * @return myvector after element added
     */
    friend myvector operator + (const myvector &vec, const T& item)
    {
        myvector vec2 = vec;
        vec2.push_back(item);

        return vec2;
    }


private:
    int _size;
    int _capacity;
    T* _arr;
};

// constructor -----------------------------------------------------------------
template<class T>
/**
 * @brief myvector<T>::myvector
 *  Default constructor that initialize capacity as 4
 */
myvector<T>::myvector()
{
    if(DEBUG) cout << "CTOR" << endl;
    this->_arr = allocate<T>(4);
    this->_size = 0;
    this->_capacity = 4;
}

template <class T>
/**
 * @brief myvector<T>::myvector
 *  parametrized constructor
 * @param n :   Initialize capacity as given
 */
myvector<T>::myvector(int n)
{
    this->_arr = allocate<T>(n);
    this->_size = 0;
    this->_capacity = n;
}

template <class T>
/**
 * @brief myvector<T>::myvector
 *  copy constructor
 * @param vec   :   copy all values in given
 *  object and create copy of pointers
 */
myvector<T>::myvector(const myvector& vec)
{
    if(DEBUG) cout << "copy CTOR" << endl;
    this->_size = vec._size;
    this->_capacity = vec._capacity;
    // create a new array then use copy function to copy values
    this->_arr = allocate<T>(_capacity);
    copy(this->_arr, vec._arr, vec._size);

}

template<class T>
/**
 * @brief myvector<T>::~myvector
 *  destructor, this execute when class instance destroyed
 */
myvector<T>::~myvector()
{
    if(DEBUG) cout << "Destructor" << endl;
    deallocate_oned(this->_arr);
}

// manipulation ----------------------------------------------------------------

template <class T>
/**
 * @brief myvector<T>::push_back
 *  push one element to the back of the list
 * @param element   :   element to push
 */
void myvector<T>::push_back(const T& element)
{
    // use add entry, extend capacity if needed
    this->_arr = add_entry(this->_arr, element,
                          this->_size, this->_capacity);
}

template<class T>
/**
 * @brief myvector<T>::pop_back
 *  delete the last element in the list
 */
void myvector<T>::pop_back()
{
    assert(this->_size>0);

    // use remove entry, resize capacity if needed
    this->_arr = remove_entry(this->_arr, back(),
                              this->_size, this->_capacity);
}

template<class T>
/**
 * @brief myvector<T>::erase
 *  erase an element from a certain space
 * @param to_erase  :   element to remove
 */
void myvector<T>::erase_element(const T& to_erase)
{
    // remove entry makes sure elements shift
    //after remove an element from mid
    _arr = remove_entry(_arr, to_erase, _size, _capacity);
}

template<class T>
/**
 * @brief myvector<T>::erase
 *  erase an element by index from a certain space
 * @param index  :   index of element to remove
 */
void myvector<T>::erase(int index)
{
    // remove entry makes sure elements shift
    //after remove an element from mid
    _arr = remove_entry(_arr, at(index), _size, _capacity);
}

template<class T>
/**
 * @brief myvector<T>::insert
 *  insert an element in to the given position
 * @param here      :   position to insert
 * @param to_insert :   element to insert
 */
void myvector<T>::insert(int here, const T& to_insert)
{
    _arr = insert_entry(_arr, to_insert, here, _size, _capacity);
}

template<class T>
/**
 * @brief myvector<T>::operator +=
 *  push an item to myvector
 * @param item  :   element to push
 * @return myvector after item pushed
 */
myvector<T>& myvector<T>::operator+=(const T& item)
{
    push_back(item);
    return *this;
}

template<class T>
/**
 * @brief myvector<T>::operator +=
 *  concatinate the given myvector
 * @param vec  :   given myvector to concatinate
 * @return  myvector after concatinated
 */
myvector<T>& myvector<T>::operator+=(const myvector& vec)
{
    //  reserve capacity to enture have enough space to add second myvector
    reserve(_capacity + vec._capacity);
    _arr = concat(_arr, _size, vec._arr, vec._size);
    return *this;
}

// size/capacity control -------------------------------------------------------

template<class T>
/**
 * @brief myvector<T>::size
 * @return size of list
 */
int myvector<T>::size()
{
    return this->_size;
}

template<class T>
/**
 * @brief myvector<T>::capacity
 * @return capacity of list
 */
int myvector<T>::capacity()
{
    return this->_capacity;
}

template<class T>
/**
 * @brief myvector<T>::resize
 *  adjust the size of list
 * @param n :   size to adjust
 */
void myvector<T>::resize(int n)
{
    if(n > capacity())
        reserve(n*2);
    _size = n;
}

template<class T>
/**
 * @brief myvector<T>::reserve
 *  adjust the capacity of list
 * @param n :   capacity to adjust
 */
void myvector<T>::reserve(int n)
{
    // try to adjust capacity smaller or equal to
    //original, nothin changes
    if(n > capacity())
    {
        _capacity = n;

        //  create a new array with given capacity the
        //copy values to new one
        T* temp = _arr;
        _arr = allocate<T>(n);
        copy(_arr, temp, _size);
        deallocate_oned(temp);
    }
}

template<class T>
/**
 * @brief myvector<T>::clear
 *  clear the array
 */
void myvector<T>::clear()
{
    // set size to zero and clear all the contents
    deallocate_oned(_arr);
    this->_arr = allocate<T>(4);
    this->_size = 0;
    this->_capacity = 4;
}

template<class T>
/**
 * @brief myvector<T>::empty
 *  check of collection is empty
 * @return true of collection is empty false otherwise
 */
bool myvector<T>::empty()
{
    return _size == 0;
}

// element accessor ------------------------------------------------------------

template<class T>
/**
 * @brief myvector<T>::at
 *  access value at a given position
 * @param n :   index of value to access
 * @return  value at the given index
 */
T& myvector<T>::at(int n)
{
    assert(n < _size);
    return *get(_arr, n, _size);
}

template<class T>
/**
 * @brief myvector<T>::at
 *  access value at a given position
 * @param n :   index of value to access
 * @return  value at the given index
 */
const T& myvector<T>::at(int n) const
{
    assert(n < _size);
    return *get(_arr, n, _size);
}

template<class T>
/**
 * @brief myvector<T>::index_of
 *  Find the index of a value within the list
 * @param to_find   :   value to find
 * @return  index of the value to find,
 *  if value does not exist, return -1
 */
int myvector<T>::index_of(const T& to_find)
{
    return search(_arr, to_find, _size);
}

template <class T>
/**
 * @brief myvector<T>::front
 *  access the first element of the list
 * @return first element
 */
const T& myvector<T>::front() const
{
    return at(0);
}

template <class T>
/**
 * @brief myvector<T>::back
 *  access last element of the list
 * @return last element
 */
const T& myvector<T>::back() const
{
    return at(_size-1);
}

template<class T>
/**
 * @brief myvector<T>::operator =
 *  assignment operator overloading
 * @param vec   :   right side of the operator
 * @return new myvector that contains same content as given one
 */
myvector<T>& myvector<T>::operator =(const myvector& vec)
{
    // check self-reference
    if(_arr != nullptr) deallocate_oned(_arr);
    _size = vec._size;
    _capacity = vec._capacity;
    _arr = allocate<T>(_capacity);
    copy(_arr, vec._arr, _size);
    return *this;

}

template<class T>
/**
 * @brief myvector<T>::operator []
 *  braket operator overloading
 * @param index :   index of value trying to access
 * @return value at the given index
 */
T& myvector<T>::operator [] (const int& index)
{
    assert(index < _size);
    return at(index);
}

template<class T>
/**
 * @brief myvector<T>::operator []
 *  braket operator overloading
 * @param index :   index of value trying to access
 * @return value at the given index
 */
const T& myvector<T>::operator [] (const int& index) const
{
    assert(index < _size);
    return at(index);
}



#endif // myvector_H
