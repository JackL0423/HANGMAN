#include <stdio.h>
#include <stdlib.h>

#include "./headers/generic_vector.h"
#include "./headers/generic.h"
#include "./headers/avl_tree.h"

TREE avl_tree_init_default(void) {
    AVL_tree* pMy_tree = (AVL_tree*)malloc(sizeof(AVL_tree));
    if (pMy_tree == NULL) {
        return NULL;
    }

    pMy_tree->root = NULL;

    return pMy_tree;
}

void avl_tree_destroy(TREE* phMy_tree) {
    AVL_tree* pMy_tree = (AVL_tree*)*phMy_tree;

    if (pMy_tree->root != NULL) {
        if ((pMy_tree->root)->left != NULL) {
            avl_tree_destroy_node((pMy_tree->root)->left);
        }

        if ((pMy_tree->root)->right != NULL) {
            avl_tree_destroy_node((pMy_tree->root)->right);
        }

        my_string_destroy(&((pMy_tree->root)->key));
        generic_vector_destroy(&((pMy_tree->root)->data));
        free(pMy_tree->root);
    }

    free(pMy_tree);
    phMy_tree = NULL;
}

void avl_tree_destroy_node(Node* pNode) {
    if (pNode == NULL) {
        return;
    }

    if (pNode->key != NULL) {
        my_string_destroy(&(pNode->key));
    }

    if (pNode->data != NULL) {
        generic_vector_destroy(&(pNode->data));
    }

    avl_tree_destroy_node(pNode->left);
    avl_tree_destroy_node(pNode->right);

    free(pNode);
}

Status avl_tree_push(TREE hMy_tree, MY_STRING key, MY_STRING item) {
    AVL_tree* pMy_tree = (AVL_tree*)hMy_tree;
    int flag;

    if (pMy_tree->root == NULL) {
        pMy_tree->root = (Node*)malloc(sizeof(Node));
        if(pMy_tree->root == NULL) {
            return FAILURE;
        }
        (pMy_tree->root)->left = NULL;
        (pMy_tree->root)->right = NULL;
        (pMy_tree->root)->key = my_string_init_c_string(my_string_c_str(key));

        (pMy_tree->root)->data = generic_vector_init_default(my_string_assignment, my_string_destroy);
        generic_vector_push((pMy_tree->root)->data, item);
    }
    else {
        flag = my_string_compare((pMy_tree->root)->key, key);
        if (flag == 1) {
            avl_tree_push(&((pMy_tree->root)->right), key, item);
        }
        else if (flag == 0) {
            generic_vector_push((pMy_tree->root)->data, item);
        }
        else if (flag == -1) {
            avl_tree_push(&((pMy_tree->root)->left), key, item);
        }
        else {
            return FAILURE;
        }
    }
    return SUCCESS;
}

GENERIC_VECTOR avl_tree_get_largest_family(TREE hMy_tree, int print_val) {
    AVL_tree* pMy_tree = (AVL_tree*)hMy_tree;
    GENERIC_VECTOR return_vector = NULL;
    GENERIC_VECTOR temp;
    int indx;

    temp = find_max_family(pMy_tree->root, print_val);
    return_vector = generic_vector_init_default(my_string_assignment, my_string_destroy);

    for (indx=0; indx<generic_vector_get_size(temp); indx++) {
        generic_vector_push(return_vector, generic_vector_at(temp, indx));
    }
    return return_vector;
}

GENERIC_VECTOR find_max_family(Node* root, int print_val) {
    GENERIC_VECTOR* temp = NULL;

    if (root != NULL) {
        if (root->left != NULL) {
            temp = find_max_family(root->left, print_val);
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(root->data)) {
                temp = root->data;
            }
        }
        if (root->right != NULL) {
            temp = find_max_family(root->right, print_val);
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(root->data)) {
                temp = root->data;
            }

            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(root->data)) {
                temp = root->data;
            }
        }

        if (print_val) {
            my_string_insertion(root->key, stdout);
            printf(" %d\n", generic_vector_get_size(root->data));
        }

        return temp;
    }
}