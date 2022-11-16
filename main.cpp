#include <stdio.h>
#include "list.h"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        return INVALID_NUM_OF_ARGV;
    }
    list my_list;
    list_init(&my_list, sizeof(int));

    FILE* out_file = fopen(argv[1], "w");

    int a = 5;
    int poz = 0;

    list_insert_after(&my_list, my_list.tail_ptr, &poz, &a);
    a = 6;
    list_insert_after(&my_list, my_list.tail_ptr, &poz, &a);
    a++;
    list_insert_after(&my_list, my_list.tail_ptr, &poz, &a);

    list_int_text_dump(&my_list, out_file);

    

    list_destroy(&my_list);

    return NO_ERRORS;
}