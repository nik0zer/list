#include "list.h"
#include <stdlib.h>
#include <string.h>

enum
{
    START_SIZE_OF_MEM =  4,
    START_SIZE_OF_LIST =  1,
    INVALID_PTR = -1,
    VIRT_ELEM = 0,
    START_FREE_PTR = 1,
    LIST_MULTPL_CONSTANT = 2,
    LIST_DIVIDE_CONSTANT = 2,
    LIST_DIVIDE_TRIGGER = 4,
};

int list_init(list* my_list, int elem_size)
{
    if(my_list == NULL)
    {
        return NULL_POINTER;
    }

    my_list->elem_arr = calloc(START_SIZE_OF_MEM, elem_size);
    my_list->next_ptr_arr = (int*)calloc(START_SIZE_OF_MEM, sizeof(int));
    my_list->prev_ptr_arr = (int*)calloc(START_SIZE_OF_MEM, sizeof(int));
    my_list->size_of_list = 0;
    my_list->size_of_mem = 0;
    my_list->elem_size = elem_size;

    if(my_list->elem_arr == NULL || my_list->prev_ptr_arr == NULL || my_list->next_ptr_arr == NULL)
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
        fprintf(out_file, "%8d  %12d  ", i, *((int*)(my_list->elem_arr + offset)));
        fprintf(out_file, "%8d  ", my_list->next_ptr_arr[i]);
        fprintf(out_file, "%8d  ", my_list->prev_ptr_arr[i]);
        fprintf(out_file, "\n");
    }
}

int list_text_dump(list* my_list, FILE* out_file)
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
        fprintf(out_file, "%8d  %X  ", i, *((int*)(my_list->elem_arr + offset)));
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

    if(insert_poz >= my_list->size_of_mem || my_list->prev_ptr_arr[insert_poz] == INVALID_PTR)
    {
        return INVALID_ELEM_POZ;
    }

    if(my_list->size_of_mem - 1 == my_list->size_of_list)
    {
        my_list->elem_arr = realloc(my_list->elem_arr, my_list->elem_size * my_list->size_of_mem * LIST_MULTPL_CONSTANT);
        my_list->next_ptr_arr = (int*)realloc(my_list->next_ptr_arr, my_list->elem_size * my_list->size_of_mem * LIST_MULTPL_CONSTANT);
        my_list->prev_ptr_arr = (int*)realloc(my_list->prev_ptr_arr, my_list->elem_size * my_list->size_of_mem * LIST_MULTPL_CONSTANT);

        if(my_list->elem_arr == NULL || my_list->prev_ptr_arr == NULL || my_list->next_ptr_arr == NULL)
        {
            return ALLOC_MEMORY_ERRORY;
        }

        my_list->size_of_mem *= LIST_MULTPL_CONSTANT;

        my_list->free_ptr = my_list->size_of_list;

        for(int i = my_list->free_ptr; i < my_list->size_of_mem; i++)
        {
            my_list->next_ptr_arr[i] = i + 1;
            my_list->prev_ptr_arr[i] = INVALID_PTR;
        }


    }

    int free_ptr;

    free_ptr = my_list->free_ptr;

    my_list->free_ptr = my_list->next_ptr_arr[my_list->free_ptr];

    int offset = free_ptr * my_list->elem_size;

    memcpy(my_list->elem_arr + offset, elem, my_list->elem_size);

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

int list_return_elem(list* my_list, void* return_elem, int poz_of_elem)
{
    if(poz_of_elem >= my_list->size_of_mem || my_list->prev_ptr_arr[poz_of_elem] == INVALID_PTR)
    {
        return INVALID_ELEM_POZ;
    }

    int offset = poz_of_elem * my_list->elem_size;

    memcpy(return_elem, my_list->elem_arr + offset, my_list->elem_size);


    return NO_ERRORS;
}

int list_delete_elem(list* my_list, void* return_elem, int poz_of_elem)
{
    if(poz_of_elem >= my_list->size_of_mem || my_list->prev_ptr_arr[poz_of_elem] == INVALID_PTR || poz_of_elem == VIRT_ELEM)
    {
        return INVALID_ELEM_POZ;
    }

    int prev_elem = my_list->prev_ptr_arr[poz_of_elem];
    int next_elem = my_list->next_ptr_arr[poz_of_elem];
    int offset = poz_of_elem * my_list->elem_size;

    memcpy(return_elem, my_list->elem_arr + offset, my_list->elem_size);
    my_list->next_ptr_arr[prev_elem] = my_list->next_ptr_arr[poz_of_elem];
    my_list->prev_ptr_arr[next_elem] = my_list->prev_ptr_arr[poz_of_elem];

    my_list->prev_ptr_arr[poz_of_elem] = INVALID_PTR;
    my_list->next_ptr_arr[poz_of_elem] = my_list->free_ptr;
    my_list->free_ptr = poz_of_elem;

    if(poz_of_elem == my_list->tail_ptr)
    {
        my_list->tail_ptr = prev_elem;
    }

    return NO_ERRORS;
}



int list_destroy(list* my_list)
{
    if(my_list == NULL)
    {
        return NULL_POINTER;
    }

    if(my_list->elem_arr != NULL)
    {
        free(my_list->elem_arr);
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
