#include "list.h"
#include <stdlib.h>
#include <string.h>

enum
{
    START_SIZE_OF_MEM =  512,
    START_SIZE_OF_LIST =  1,
    INVALID_PTR = -1,
    VIRT_ELEM = 0,
    START_FREE_PTR = 1,
};

int list_init(list* my_list, int elem_size)
{
    if(my_list == NULL)
    {
        return NULL_POINTER;
    }

    my_list->values_arr = calloc(START_SIZE_OF_MEM, elem_size);
    my_list->next_ptr_arr = (int*)calloc(START_SIZE_OF_MEM, sizeof(int));
    my_list->prev_ptr_arr = (int*)calloc(START_SIZE_OF_MEM, sizeof(int));
    my_list->size_of_list = 0;
    my_list->size_of_mem = 0;
    my_list->elem_size = elem_size;

    if(my_list->values_arr == NULL || my_list->prev_ptr_arr == NULL || my_list->next_ptr_arr == NULL)
    {
        return ALLOC_MEMORY_ERRORY;
    }

    my_list->size_of_mem = START_SIZE_OF_MEM;

    my_list->head_ptr = VIRT_ELEM;
    my_list->free_ptr = START_FREE_PTR;
    my_list->tail_ptr = VIRT_ELEM;
    
    for(int i = my_list->free_ptr; i < START_SIZE_OF_MEM; i++)
    {
        my_list->next_ptr_arr[i] = i + 1;
        my_list->prev_ptr_arr[i] = INVALID_PTR;
    }

    my_list->next_ptr_arr[START_SIZE_OF_MEM - 1] = INVALID_PTR;

    my_list->next_ptr_arr[my_list->head_ptr] = my_list->head_ptr;
    my_list->prev_ptr_arr[my_list->head_ptr] = my_list->head_ptr;

    my_list->size_of_list = START_SIZE_OF_LIST;

    return NO_ERRORS;
}

int list_int_text_dump(list* my_list, FILE* out_file)
{
    int offset = 0;

    fprintf(out_file, "head_ptr: %d\n", my_list->head_ptr);
    fprintf(out_file, "tail_ptr: %d\n", my_list->tail_ptr);
    fprintf(out_file, "free_ptr: %d\n", my_list->free_ptr);
    fprintf(out_file, "number of elements in list: %d\n", my_list->size_of_list);
    fprintf(out_file, "number of alloc memory in list: %d\n", my_list->size_of_mem);

    for(int i = 0; i < my_list->size_of_mem; i++)
    {
        offset = i * my_list->elem_size;
        fprintf(out_file, "%8d  %8d  ", i, *((int*)(my_list->values_arr + offset)));
        fprintf(out_file, "%8d  ", my_list->next_ptr_arr[i]);
        fprintf(out_file, "%8d  ", my_list->prev_ptr_arr[i]);
        fprintf(out_file, "\n");
    }
}

int list_insert_after(list* my_list, int insert_poz, int* elem_poz, void* elem)
{
    if(my_list == NULL)
    {
        return NULL_POINTER;
    }

    if(my_list->prev_ptr_arr[insert_poz] == INVALID_PTR)
    {
        return INVALID_INSERT_POZ;
    }

    int free_ptr;
    free_ptr = my_list->free_ptr;
    my_list->free_ptr = my_list->next_ptr_arr[my_list->free_ptr];

    int offset = free_ptr * my_list->elem_size;

    memcpy(my_list->values_arr + offset, elem, my_list->elem_size);

    my_list->prev_ptr_arr[free_ptr] = insert_poz;
    my_list->next_ptr_arr[free_ptr] = my_list->next_ptr_arr[insert_poz];
    my_list->next_ptr_arr[insert_poz] = free_ptr;
    my_list->prev_ptr_arr[my_list->next_ptr_arr[free_ptr]] = free_ptr;

    if(insert_poz == my_list->tail_ptr)
    {
        my_list->tail_ptr = free_ptr;
    }

    *elem_poz = free_ptr;
    my_list->size_of_list++;

    return NO_ERRORS;



}



int list_destroy(list* my_list)
{
    if(my_list == NULL)
    {
        return NULL_POINTER;
    }

    if(my_list->values_arr != NULL)
    {
        free(my_list->values_arr);
    }

    if(my_list->next_ptr_arr != NULL)
    {
        free(my_list->next_ptr_arr);
    }

    if(my_list->prev_ptr_arr != NULL)
    {
        free(my_list->prev_ptr_arr);
    }

    return NO_ERRORS;
}
