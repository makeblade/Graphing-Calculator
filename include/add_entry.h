#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H

#include <iostream>

using namespace std;

template <typename T>
T* allocate(int size);
template<typename T>
T* add_entry(T* list, const T& new_entry,
             int& size, int& capacity);
template<typename T>
void print_list(T* source, int size);
template<typename T>
void append(T* to_append, T key, int& size);
template <typename T>
void copy(T* result, T* source, T* source_size);
template <typename T>
T search(int index, T* source, T* source_size);
template<typename T>
T* remove_entry(T* list, const T& delete_me,
                     int& size, int& capacity);


template<typename T>
T* remove_entry(T* list, const T& delete_me,
                     int& size, int& capacity)
{
    T* found = find(list, delete_me, size);
    if(found != nullptr)
    {
        T* end_of_list = list+size-1;
        swap(found, end_of_list);
        size--;

        if(size < (capacity/4))
        {
            T* temp = list;
            capacity /= 4;
            list = allocate<T>(capacity);
            copy(list, temp, size);
            delete [] temp;
        }
    }
    return list;
}
template <typename T>
T search(int index, T* source, T* source_size)
{
    if(index >= source_size)
        return nullptr;
    T* result = source+index;

    return *result;
}

template<typename T>
void deallocate(T* to_d)
{
    delete[] to_d;
}

template<typename T>
T* add_entry(T* list, const T& new_entry,
             int& size, int& capacity)
{
    if(size == capacity)
    {
        T* temp = list;
        capacity *= 2;
        list = allocate<T>(capacity);
        copy(list, temp, size);
        delete [] temp;
    }
    append(list, new_entry, size);
    return list;
}

template<typename T>
T* allocate(int capacity){
    const bool debug = false;
    if (debug) cout<<"allocate: capacity: "<<capacity<<endl;
    return new T[capacity];
}
template<typename T>
void print_list(T* source, int size)
{
    T* walker = source;
    while(walker-source < size)
    {
        cout << *walker << " ";
        walker ++;
    }
    cout << endl << endl;
}

template<typename T>
void append(T* to_append, T key, int& size)
{
    // Create a pointer points to the end of the array, and assign the given
    //  item to it.
    T* walker = to_append+size;
    *walker = key;
    size++; // size increases after
}

template <typename T>
void copy(T* result, T* source, T* source_size)
{
    T* source_walker = source;
    T* result_walker = result;
    while(source_walker-source < source_size)
    {
        *result_walker = *source_walker;
        result_walker++;
        source_walker++;
    }
}



#endif // ADD_ENTRY_H
