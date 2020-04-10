#ifndef TWO_D_ARRAY_H
#define TWO_D_ARRAY_H
#include <iostream>
#include <assert.h>
#include "one_d_array.h"

using namespace std;


int array_size(int* sizes);
bool index_is_valid(int* sizes, int row, int col);
void print_array(int* a);


//To call: int** p = allocate_twod<int>(sizes_array)   -Thank you Travis!
template <class T>
T** allocate_twod(int* sizes);

template <class T>
T read_twod(T** twod, int row, int col);

template <class T>
void write_twod(T** twod, int row, int col, const T& item);

template <class T>
T& get_twod(T** twod, int row, int col);

template<class T>
void init_twod(T** twod, int* sizes, T init_item = T());

template<class T>
bool search_twod(T** twod, int* sizes, const T& key, int& row, int& col);

//return a pointer to the item if found, nullptr if not found:
// (Ms. Barskhian)
template<class T>
T* search_twod(T** twod, int* sizes, const T& key);

template <class T>
ostream& print_twod(T** twod, int* sizes, ostream& outs = cout);

template <typename T>
void deallocate_twod(T** twod, int* sizes);

template<typename T>
/**
 * @brief deallocate a given twod pointer
 * @param twod  :   to deallocate
 * @param sizes :   size of given twod
 */
void deallocate_twod(T** twod, int* sizes)
{
    int size = array_size(sizes);
    T** twod_walker = twod;

    // go thru every pointer in twod and deallocate by calling deallocate from
    //  one_d_h
    while(twod_walker-twod < size)
    {
        deallocate_oned(*twod_walker);
        twod_walker++;
    }
    delete[] sizes;
}

template <class T>
/**
 * @brief create a two d array pointer by reserve a space dynamically
 * @param sizes :   size of two day array
 * @return a two day array pointer
 */
T** allocate_twod(int* sizes)
{
    // find length of given size array as row, and initialize the size of every
    //  row as value stored in sizes array
    int row = array_size(sizes);
    T** result = new T*[row];
    T** result_walker = result;
    int* size_walker = sizes;

    for(int i=0; i< row; i++)
    {
        // call allocate from one_d_array to allocate a one d array
        *result_walker = allocate<T>(*size_walker);
        result_walker++;
        size_walker++;
    }
    return result;
}

template<class T>
/**
 * @brief initialize given 2d array pointer with it's types initial value
 * @param twod      :   two d array pointer for initialize
 * @param sizes     :   size for 2d array pointer
 * @param init_item :   initial value for initialization
 */
void init_twod(T** twod, int* sizes, T init_item)
{
    // find size of given siezs array as row, walk thru twod and initialize
    //  all its item to the init_item
    int row = array_size(sizes);
    int* sizes_walker = sizes;
    T** twod_walker = twod;

    for(int i=0; i<row; i++)
    {
        init_oned(*twod_walker, *sizes_walker, init_item);
        twod_walker++;
        sizes_walker++;
    }
}

template<class T>
/**
 * @brief search the given 2d array for given key, then record its row and col.
 * @param twod  :   2d array pointer to search
 * @param sizes :   sizes of given 2d array pointer
 * @param key   :   key to search for
 * @param row   :   variable to record given key's row if found
 * @param col   :   variable to record given key's col if found
 * @return  return true of key is found, false otherwise
 */
bool search_twod(T** twod, int* sizes, const T& key, int& row, int& col)
{
    // Using same way go thru twod as before, then check one by one if it is
    // equals to the given key
    int row_twod = array_size(sizes);
    int* sizes_walker = sizes;
    T** twod_walker = twod;
    T* result_location;

    for(int i=0; i<row_twod; i++)
    {
        // call find function from oned to find key
        result_location = find(*twod_walker, key, *sizes_walker);
        if(result_location != nullptr)
        {
            // set current i as row, different between found key and pointer
            //  as column
            row = i;
            col = result_location - *twod_walker;
            return true;
        }
        twod_walker++;
        sizes_walker++;
    }
    return false;
}

template<class T>
/**
 * @brief search for the given key within the given 2d array pointer
 * @param twod  :   2d array pointer
 * @param sizes :   size of the given 2d array pointer
 * @param key   :   key to search for
 * @return  the pointer that points to the key within the given 2d array
 */
T* search_twod(T** twod, int* sizes, const T& key)
{
    int row_twod = array_size(sizes);
    int* sizes_walker = sizes;
    T** twod_walker = twod;
    T* result_location;

    // go thru every element in twod, find given key and return its pointer
    for(int i=0; i<row_twod; i++)
    {
        // call find function from oned to find key
        result_location = find(*twod_walker, key, *sizes_walker);
        if(result_location != nullptr)
            return result_location;
    }
    return nullptr;
}

template <class T>
/**
 * @brief get the content in 2d array for given row and col
 * @param twod to search for
 * @param row of the key
 * @param col of the key
 * @return  the reference of the key that is in the given 2d array
 */
T& get_twod(T** twod, int row, int col)
{

    T** twod_walker = twod+row;
    T* twod_walker2 = *twod_walker+col;
    return *twod_walker2;
}

template <class T>
/**
 * @brief this function reads the content of given row and col in 2d array
 * @param twod for read
 * @param row of the key for read
 * @param col of the key for read
 * @return  content of the given row and col in twod
 */
T read_twod(T** twod, int row, int col)
{
    // read the given position in twod
    T** twod_walker = twod+row;
    T* twod_walker2 = *twod_walker+col;
    return *twod_walker2;
}

template <class T>
/**
 * @brief writes given value in to twod in given position
 * @param twod to write
 * @param row of the position to write
 * @param col of the position to write
 * @param item to write into the given position
 */
void write_twod(T** twod, int row, int col, const T& item)
{
    // call get_twod to write
    get_twod(twod, row, col) = item;
}

template <class T>
/**
 * @brief printes the given twod array
 * @param twod for print
 * @param sizes of twod
 * @param outs
 * @return  ostream
 */
ostream& print_twod(T** twod, int* sizes, ostream& outs)
{
    // use size of given sizes array as row, and its content as column
    int row = array_size(sizes);
    int* sizes_walker = sizes;
    T** twod_walker = twod;

    // go thru every element of  twod and print them out one by one
    for(int i=0; i<row; i++)
    {
        cout << i << " ";
        print_list(*twod_walker, *sizes_walker);
        cout << endl;
        twod_walker++;
        sizes_walker++;
    }
    outs << endl << endl;
    return outs;
}


#endif // TWO_D_ARRAY_H
