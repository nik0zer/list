#include <stdio.h>
#include "list.h"

int main()
{
    list my_list;
    list_init(&my_list, sizeof(int));

    list_destroy(&my_list);

    return NO_ERRORS;
}