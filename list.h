#ifndef LIST_H
#define LIST_H

enum ERRORS
{
    NO_ERRORS = 0,
    NULL_POINTER = 1,
    ALLOC_MEMORY_ERRORY = 2
};

struct list
{
    void* values_arr;
    int* next_ptr_arr;
    int* prev_ptr_arr;
    int size_of_list;
    int size_of_mem;
    int head_ptr;
    int free_ptr;
    int tail_ptr;
};




#endif