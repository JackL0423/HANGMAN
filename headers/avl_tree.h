#ifndef AVL_TREE_H
#define AVL_TREE_H


#include "generic.h"
#include "generic_vector.h"
#include "my_string.h"

typedef void* TREE;

TREE avl_tree_init_default(void);

void avl_tree_destroy(TREE* phMy_tree);

Status avl_tree_push(TREE hMy_tree, MY_STRING key, MY_STRING item);

GENERIC_VECTOR avl_tree_get_largest_family(TREE hMy_tree, int print_val);

GENERIC_VECTOR find_max_family(Node* root, int print_val);

int avl_find_tree_magnitude(TREE hTree); 

#endif//AVL_TREE_H