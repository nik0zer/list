#include "list.h"
#include <stdlib.h>

#define START_SIZE_OF_LIST 512

int list_init(list* my_list, int elem_size)
{
    if(my_list == NULL)
    {
        return NULL_POINTER;
    }

    my_list->values_arr = calloc(START_SIZE_OF_LIST, elem_size);
    my_list->next_ptr_arr = (int*)calloc(START_SIZE_OF_LIST, sizeof(int));
    my_list->prev_ptr_arr = (int*)calloc(START_SIZE_OF_LIST, sizeof(int));
    my_list->size_of_list = 0;
    my_list->size_of_mem = 0;

    if(my_list->values_arr == NULL || my_list->prev_ptr_arr == NULL || my_list->next_ptr_arr == NULL)
    {
        return ALLOC_MEMORY_ERRORY;
    }

    my_list->size_of_mem = START_SIZE_OF_LIST;

    my_list->head_ptr = 0;
    my_list->free_ptr = 1;
    my_list->tail_ptr = 0;
    
    for(int i = my_list->free_ptr; i < START_SIZE_OF_LIST; i++)
    {
        my_list->next_ptr_arr[i] = i + 1;
        my_list->prev_ptr_arr[i] = -1;
    }

    my_list->next_ptr_arr[START_SIZE_OF_LIST - 1] = -1;

    my_list->next_ptr_arr[my_list->head_ptr] = my_list->head_ptr;
    my_list->prev_ptr_arr[my_list->head_ptr] = my_list->head_ptr;

    return NO_ERRORS;
}

