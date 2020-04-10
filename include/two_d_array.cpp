#include "two_d_array.h"

/**
 * @brief get the size of given array that ends with -1
 * @param sizes array pointer
 * @return sizes of given pointer
 */
int array_size(int* sizes)
{
    // create a walker pointes to given array then look for -1 while
    //  record the length
    int result = 0;
    int* walker = sizes;
    while(*walker != -1)
    {
        result++;
        walker++;
    }
    return result;
}

/**
 * @brief check if given position in given sizes is valid
 * @param sizes :   size to check
 * @param row   :   row to check
 * @param col   :   col to check
 * @return  true of given postion is valid, false otherwise
 */
bool index_is_valid(int* sizes, int row, int col)
{
    // check if the given row and col are out of bounce
    return (row<=array_size(sizes) && col<=*(sizes+row)
            && row >= 0 && col >= 0);
}

/**
 * @brief print the given 1d array
 * @param 1d array to print
 */
void print_array(int* a)
{
    // use a walker to walk thru the given array, then print them one by one
    int* walker = a;
    int size = array_size(a);
    while(walker-a < size)
    {
        cout << *walker << " ";
        walker++;
    }
    cout << endl;
}
