#include <stdio.h>
#include <stdlib.h>

#include "./headers/generic_vector.h"
#include "./headers/generic.h"
#include "./headers/avl_tree.h"

typedef struct node Node;

struct node {
    Node* left;
    Node* right;
    MY_STRING key;
    GENERIC_VECTOR data;
};

typedef struct node AVL_tree;

//  Fix init funciton.
TREE avl_tree_init_default(void) {
    AVL_tree* pRoot = (AVL_tree*)malloc(sizeof(AVL_tree));
    if (pRoot == NULL) {
        return NULL;
    }
    pRoot->left = NULL;
    pRoot->right = NULL;

    return (TREE)pRoot;
}

void avl_tree_destroy(TREE* phRoot) {
    AVL_tree* pRoot = (AVL_tree*)*phRoot;
    if (pRoot != NULL) {
        my_string_destroy(&(pRoot->key));
        generic_vector_destroy(&(pRoot->data));
        avl_tree_destroy(pRoot->left);
        avl_tree_destroy(pRoot->right);
        free(pRoot);
    }
    phRoot = NULL;
}

//  Fix the push function and correct to use the right values.
Status avl_tree_push(TREE hTree, MY_STRING key, MY_STRING item) {
    AVL_tree* pRoot = (AVL_tree*)hTree;
    int flag;

    if (pRoot == NULL) {
        pRoot = (Node*)malloc(sizeof(Node));
        if (pRoot == NULL) {
            return FAILURE;
        }
        pRoot->left = NULL;
        pRoot->right = NULL;
        pRoot->key = my_string_init_c_string(my_string_c_str(key));

        pRoot->data = generic_vector_init_default((ITEM)my_string_assignment, my_string_destroy);
        generic_vector_push_back(pRoot->data, item);
    }

    //  Need to come up with recursive solution.
    //  Need to also add way for tree to reorginize itself if magnitute >2
   flag = my_string_compare(pRoot->key, key);
    if (flag == 1) {
        avl_tree_push(&(pRoot->right), key, item);
    }
    else if (flag == 0) {
        generic_vector_push_back(pRoot->data, item);
    }
    else if (flag == -1) {
        avl_tree_push(&(pRoot->left), key, item);
    }
    else {
        return FAILURE;
    }
    return SUCCESS;
}

GENERIC_VECTOR avl_tree_get_largest_family(TREE hTree, int print_val) {
    AVL_tree* pRoot = (AVL_tree*)hTree;
    GENERIC_VECTOR return_vector = NULL;
    GENERIC_VECTOR temp;
    int indx;

    temp = find_max_family(pRoot, print_val);
    return_vector = generic_vector_init_default((ITEM)my_string_assignment, my_string_destroy);

    for (indx=0; indx<generic_vector_get_size(temp); indx++) {
        generic_vector_push_back(return_vector, generic_vector_at(temp, indx));
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


//  Make function for balancing factor. 
int avl_find_tree_magnitude(TREE hTree) {
    AVL_tree* pRoot = (AVL_tree*)hTree;
    if (pRoot != NULL) {
        return 1 + ((avl_find_tree_magnitude(pRoot->left) > avl_find_tree_magnitude(pRoot->right)) ? avl_find_tree_magnitude(pRoot->left):avl_find_tree_magnitude(pRoot->right));
    }

    return 0;
}