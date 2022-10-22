#ifndef LIST_H
#define LIST_H

struct list_node
{
    void* node_val;
    int next_node;
    int prev_node;
};

struct list
{
    list_node* nodes_arr;
    int size_of_list;
    int head_num;
};




#endif