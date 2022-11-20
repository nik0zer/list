#ifndef LIST_H
#define LIST_H
#include <stdio.h>

enum ERRORS
{
    NO_ERRORS = 0,
    NULL_POINTER = 1,
    ALLOC_MEMORY_ERRORY = 2,
    INVALID_INSERT_POZ = 3,
    INVALID_NUM_OF_ARGV = 4
    
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
    int elem_size;
};

int list_init(list* my_list, int elem_size);

int list_destroy(list* my_list);

int list_int_text_dump(list* my_list, FILE* out_file);

int list_insert_after(list* my_list, int insert_poz, int* elem_poz, void* elem);

int list_text_dump(list* my_list, FILE* out_file);




#endif