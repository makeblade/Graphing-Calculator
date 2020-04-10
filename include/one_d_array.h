#ifndef ONE_D_ARRAY_H
#define ONE_D_ARRAY_H

#include <iostream>
#include <iomanip>
#include <assert.h>

using namespace std;

template <typename T>
T* allocate(int size);
template <typename T>
void swap(T* fist, T* second);
template <typename T>
void copy(T* result, T* source, int source_size);
template<typename T>
void append(T* to_append, T key, int& size);
template<typename T>
void print_list(T* source, const int &size);
template<typename T>
T* find(T* to_check, T key, int size);
template<typename T>
T* add_entry(T* list, const T& new_entry,
             int& size, int& capacity);
template<typename T>
T* remove_entry(T* list, const T& delete_me,
                     int& size, int& capacity);
template<typename T>
void init_oned(T* oned, int sizes, T value = T());
template<typename T>
T* get(T* to_check, int index, int size);
template<typename T>
int search(T* source, T key, int size);
template<typename T>
void shift_left(T* source, T* shift, int& size);
template<typename T>
T* shift_right(T* source, const int& index, int& size, int& capacity);
template<typename T>
T* insert_entry(T* source,T element,  int index, int& size, int& capacity);
template<typename T>
T* concat(T* s1, int& s1_size, T* s2, int s2_size);
template<typename T>
T* resize(T* source, int& old_size, int new_size);
template<typename T>
bool compare(T* source1, int source1_size, T* source2, int source2_size);


template<typename T>
bool compare(T* source1, int source1_size, T* source2, int source2_size)
{
    if(source1_size != source2_size) return false;
    T* walker1 = source1;
    T* walker2 = source2;
    for(int i=0; i<source1_size; i++)
    {
        if(*walker1 != * walker2) return false;
        walker1++;
        walker2++;
    }
    return true;
}
// This function only for polynomial
template<typename T>
T* resize(T* source, int& old_size, int new_size)
{
    T* result = allocate<T>(new_size+1);
    copy(result, source, old_size < new_size ? old_size+1:new_size+1);
    old_size = new_size;
    delete[] source;
    return result;
}
template<typename T>
T* concat(T* s1, int& s1_size, T* s2, int s2_size)
{
    T* walker1 = s1 + s1_size;
    T* walker2 = s2;


    while(walker2-s2 < s2_size)
    {
        *walker1 = *walker2;
        walker1++;
        walker2++;
        s1_size++;
    }

    return s1;
}

template<typename T>
T* insert_entry(T* source,T element,  int index, int& size, int& capacity)
{
    // shift right then insert
    source = shift_right(source, index, size, capacity);
    *get(source, index, size) = element;

    return source;
}

template<typename T>
void shift_left(T* source, T* shift, int& size)
{
    if(shift == nullptr)
        return;

    T* walker1 = shift;
    T* walker2 = shift+1;

    while(walker2-source <= size)
    {
        *walker1 = *walker2;
        walker1++;
        walker2++;
    }
    size --;
}

template<typename T>
T* shift_right(T* source, const int& index, int& size, int& capacity)
{
    T* last = source+size-1;
    source = add_entry(source, *last, size, capacity);

    T* walker2 = source + size -1;
    T* walker1 = source + size -2;

    while(walker1-source >= index)
    {
        *walker2 = *walker1;
        walker1--;
        walker2--;
    }

    return source;
}

template<typename T>
int search(T* source, T key, int size)
{
    T* walker = source;
    int index = 0;
    while(walker-source < size)
    {
        if(*walker == key)
            return index;
        index ++;
        walker++;
    }return -1;
}
template<typename T>
T* get(T* to_check, int index, int size)
{
    if(index < size){
        T* result = to_check+index;
        return result;
    }return nullptr;
}
template<typename T>
/**
 * @brief deacllocate a array pointer
 * @param oned  :   to deallocate
 */
void deallocate_oned(T* oned)
{
    delete[] oned;
}

template<typename T>
/**
 * @brief This function initializes the given oned array
 * @param oned  :   given array to initialize
 * @param sizes :   size of given array
 * @param value :   value to initialize with
 */
void init_oned(T* oned, int sizes, T value)
{
    T* walker = oned;
    while(walker - oned < sizes)
    {
        *walker = value;
        walker++;
    }
}

template<typename T>
/**
 * @brief allocates a new array with given capacity
 * @param capacity
 * @return a newly allocated array
 */
T* allocate(int capacity){
    const bool debug = false;
    if (debug) cout<<"allocate: capacity: "<<capacity<<endl;
    // This dynamic array will be deleted by the caller
    T* result = new T[capacity];
    init_oned(result, capacity);
    return result;
}
// Adds a element into an array, if size reaches max capacity, the array expands
// Output: New array after added
template<typename T>
T* add_entry(T* list, const T& new_entry,
             int& size, int& capacity)
{
    // add one element at the end
    append(list, new_entry, size);
    // check first if size reach to capacity yet
    if(size == capacity)
    {
        // if size reaches capacity, create a new array with doubled capacity
        T* temp = list;
        capacity *= 2;
        list = allocate<T>(capacity);
        // copy contents to the new array and free up the spaces of old one
        copy(list, temp, size);
        delete [] temp;
    }
    return list;
}

// This function searches an element in an array and delete, if size is less
//  than 1/4 of capacity, capacity shrink half
// Output: New array after removed an element
template<typename T>
T* remove_entry(T* list, const T& delete_me,
                     int& size, int& capacity)
{
    // Search of deleting element if it exists in the array
    T* found = find(list, delete_me, size);
    if(found != nullptr)
    {
        // if deleting element is found, replace it with the last element in
        //  the array, then shrink size by one, essentially deleting the last
        //  element
        shift_left(list, found, size);

        // Check if size is less then 1/4 of capcacity, if it does, shrink the
        //  maximum capacity by twice
        if(size < (capacity/4) && size != 0)
        {
            T* temp = list;
            capacity /= 4;
            // Copy the cotents to a new array then delete the old one
            list = allocate<T>(capacity);
            copy(list, temp, size);
            delete [] temp;
        }
    }
    return list;
}
// Swaps the contents of two given arguments
template<typename T>
void swap(T* first, T* second)
{
    T temp = *second;
    *second = *first;
    *first = temp;
}
// Copy all values of a array to another array
template <typename T>
void copy(T* dest, T* src, int size)
{
    // Create two pointers point to each of the given arrays
    T* walker = src;
    T* walker2 = dest;

    // Copy the current value of src array to dest array then goto next element
    for(int i=0; i<size; i++){
        *walker2 = *walker;
        walker++;
        walker2++;
    }
}
// Append a item to the end of an array
// Output: None
template<typename T>
void append(T* to_append, T key, int& size)
{
    // Create a pointer points to the end of the array, and assign the given
    //  item to it.
    T* walker = to_append+size;

    *walker = key;
    size++; // size increases after
}
// Prints out all values in a given array
// Output: None
template<typename T>
void print_list(T* source, const int &size)
{
    T* walker = source;

    cout << "[ ";

    while(walker-source < size)
    {
        cout << *walker << " ";
        walker ++;
    }

    cout << "]";
}
// Check if the given item exist in the given array
// Output: A pointer points to the postion of given key in the array or nullptr
//          if it is not found in the array
template<typename T>
T* find(T* to_check, T key, int size)
{
    T* walker = to_check;       // pointer walks along the given array
    // Check array item one by one, if a similer item is found, return the
    //  pointer that points to it
    while(walker-to_check < size)
    {
        if(*walker == key)
            return walker;
        walker++;
    }
    // return nullptr of no similer item is found
    return nullptr;
}

#endif // ONE_D_ARRAY_H
