#ifndef AVL_TREE_H
#define AVL_TREE_H


#include "generic.h"
#include "generic_vector.h"
#include "my_string.h"

typedef void* TREE;

typedef struct node Node;

TREE avl_tree_init_default(void);

void avl_tree_destroy(TREE* phTree);

void avl_tree_node_destroy(Node* root);

int avl_tree_height(TREE hTree);

int avl_tree_max(int a, int b);

int avl_tree_get_balance(TREE hTree);

Node* avl_tree_new_node(MY_STRING key, MY_STRING item);

Node* avl_tree_right_rotate(Node* root);

Node* avl_tree_left_rotate(Node* root);

TREE avl_tree_push(TREE phTree, MY_STRING key, MY_STRING item);

GENERIC_VECTOR avl_tree_get_largest_family(TREE hTree);

GENERIC_VECTOR find_max_family(TREE hTree);

Node* avl_tree_find_max_node(TREE word_bin);

MY_STRING avl_tree_node_key(Node* largest_bin_node);

#endif//AVL_TREE_H