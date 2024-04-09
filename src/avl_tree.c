#include <stdio.h>
#include <stdlib.h>

#include "./headers/generic_vector.h"
#include "./headers/generic.h"
#include "./headers/avl_tree.h"


struct node {
    Node* left;
    Node* right;
    MY_STRING key;
    GENERIC_VECTOR data;
    int height;
};

//  Fix init funciton.
TREE avl_tree_init_default(void) {
    Node* pRoot = (Node*)malloc(sizeof(Node));
    if (pRoot == NULL) {
        return NULL;
    }
    pRoot->left = NULL;
    pRoot->right = NULL;
    pRoot->key = my_string_init_default();
    pRoot->data = generic_vector_init_default(my_string_init_copy, my_string_destroy);
    pRoot->height = 0;

    return (TREE)pRoot;
}

void avl_tree_destroy(TREE* phTree) {
    Node* pRoot = (Node*)*phTree;
    if (pRoot != NULL) {
        avl_tree_node_destroy(pRoot->left);
        avl_tree_node_destroy(pRoot->right);

        my_string_destroy(&(pRoot->key));
        generic_vector_destroy(&(pRoot->data));

        //free(pRoot);
    }
    phTree = NULL;
}

void avl_tree_node_destroy(Node* root) {
    if (root != NULL) {
        avl_tree_node_destroy(root->left);
        avl_tree_node_destroy(root->right);
        my_string_destroy(&(root->key));
        generic_vector_destroy(&(root->data));

        free(root);
    }
}

int avl_tree_height(TREE hTree) {
    Node* pRoot = (Node*)hTree;
    if (pRoot == NULL) {
        return 0;
    }
    return pRoot->height;
}

int avl_tree_max(int a, int b) {
    return (a > b) ? a : b;
}

int avl_tree_get_balance(TREE hTree) {
    Node* pRoot = (Node*)hTree;
    if (pRoot == NULL) {
        return 0;
    }
    return avl_tree_height(pRoot->left) - avl_tree_height(pRoot->right);
}

Node* avl_tree_new_node(MY_STRING key, MY_STRING item) {
    Node* pRoot = (Node*)malloc(sizeof(Node));
    if (pRoot == NULL) {
        return NULL;
    }
    pRoot->left = NULL;
    pRoot->right = NULL;
    pRoot->key = my_string_init_c_string(my_string_c_str(key));
    pRoot->data = generic_vector_init_default((ITEM)my_string_init_copy, my_string_destroy);
    generic_vector_push_back(pRoot->data, item);
    pRoot->height = 1;

    return pRoot;
}

Node* avl_tree_right_rotate(Node* root) {
    Node* tmp1 = root->left;
    Node* tmp2 = tmp1->right;

    tmp1->right = root;
    root->left = tmp2;

    root->height = 1 + avl_tree_max(avl_tree_height(root->left), avl_tree_height(root->right));
    tmp1->height = 1 + avl_tree_max(avl_tree_height(tmp1->left), avl_tree_height(tmp1->right));

    return tmp1;
}

Node* avl_tree_left_rotate(Node* root) {
    Node* tmp1 = root->right;
    Node* tmp2 = tmp1->left;

    tmp1->left = root;
    root->right = tmp2;

    root->height = 1 + avl_tree_max(avl_tree_height(root->left), avl_tree_height(root->right));
    tmp1->height = 1 + avl_tree_max(avl_tree_height(tmp1->left), avl_tree_height(tmp1->right));

    return tmp1;
}

//  Fix the push function and correct to use the right values.
TREE avl_tree_push(TREE phTree, MY_STRING key, MY_STRING item) {
    Node* pRoot = (Node*)phTree;
    int balance;

    if (pRoot == NULL) {
        return avl_tree_new_node(key, item);
    }

    if (my_string_compare(key, pRoot->key) < 0) {
        pRoot->left = avl_tree_push((pRoot->left), key, item);
    }
    else if (my_string_compare(key, pRoot->key) > 0) {
        pRoot->right = avl_tree_push((pRoot->right), key, item);
    }

    pRoot->height = 1 + avl_tree_max(avl_tree_height(pRoot->left), avl_tree_height(pRoot->right));

    balance = avl_tree_get_balance(pRoot);

    if (balance > 1 && my_string_compare(key, pRoot->left->key) < 0) {
        return avl_tree_right_rotate(pRoot);
    }

    if (balance < -1 && my_string_compare(key, pRoot->right->key) > 0) {
        return avl_tree_left_rotate(pRoot);
    }

    if (balance > 1 && my_string_compare(key, pRoot->left->key) > 0) {
        pRoot->left = avl_tree_left_rotate(pRoot->left);
        return avl_tree_right_rotate(pRoot);
    }

    if (balance < -1 && my_string_compare(key, pRoot->right->key) < 0) {
        pRoot->right = avl_tree_right_rotate(pRoot->right);
        return avl_tree_left_rotate(pRoot);
        //status = SUCCESS;
    }

    return pRoot;
}

GENERIC_VECTOR avl_tree_get_largest_family(TREE hTree) {
    Node* pRoot = (Node*)hTree;
    GENERIC_VECTOR return_vector = NULL;
    GENERIC_VECTOR temp;
    int indx;

    temp = find_max_family(pRoot);
    return_vector = generic_vector_init_default((ITEM)my_string_init_copy, my_string_destroy);

    for (indx=0; indx<generic_vector_get_size(temp); indx++) {
        generic_vector_push_back(return_vector, generic_vector_at(temp, indx));
    }
    return return_vector;
}

//  Might delete.
GENERIC_VECTOR find_max_family(TREE hTree) {
    Node* pRoot = (Node*)hTree;
    GENERIC_VECTOR* temp = NULL;
    //  S L R
    if (pRoot != NULL) {
        if (pRoot->left != NULL) {
            temp = find_max_family(pRoot->left);
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->data)) {
                temp = pRoot->data;
            }
        }
        if (pRoot->right != NULL) {
            temp = find_max_family(pRoot->right);
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->data)) {
                temp = pRoot->data;
            }

            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->data)) {
                temp = pRoot->data;
            }
        }

        return temp;
    }

    return NULL;
}

Node* avl_tree_find_max_node(TREE word_bin) {
    Node* pRoot = (Node*)word_bin;
    while (pRoot->right != NULL) {
        pRoot = pRoot->right;
    }

    return pRoot;
}

MY_STRING avl_tree_node_key(Node* largest_bin_node) {
    return largest_bin_node->key;
}
